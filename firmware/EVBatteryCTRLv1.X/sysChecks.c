/*  Electric Vehicle Battery Monitoring System.>
    Copyright (C) <2020>  <Jarrett R. Cigainero>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>*/

#ifndef SYSCHKS_C
#define SYSCHKS_C

#include "sysChecks.h"
#include "common.h"
#include "eeprom.h"

void chargeDetect(void){
    //Check to see if charger has been plugged in, if this routine has been run already, and that initial calibration is done.
    if(!CONDbits.charger_detected && chrgSwitch && first_cal == fCalReady){
        //reset peak power when we plug in a charger.
        dsky.peak_power = 0;
        //Check for partial charge status to see if we need to do a full charge to ballance the cells.
        //If partial_charge is greater than 100%, set to 100% and write the new value.
        if(sets.partial_charge > 1){
            TMR4 = 0;   //Reset timer 4 to prevent a check between writes.
            sets.partial_charge = 1;
            ram_chksum_update();     //Update the checksum after a write.
            fault_log(0x1C);         // Log Partial charge was set higher than 100% event.
        }
        //If parial_charge is set to 0% then we disable and charge the battery up to full every time.
        if(sets.partial_charge == 0){
            dsky.chrg_voltage = sets.battery_rated_voltage;
            p_charge = 0;
        }
        //Do a full charge every 10 cycles so that we can ballance the cells.
        //Need to make this configure-able by the user at runtime.
        if(vars.partial_chrg_cnt < 10){
            vars.partial_chrg_cnt++;
            p_charge = 1;
            dsky.chrg_voltage = ((sets.battery_rated_voltage - sets.dischrg_voltage) * sets.partial_charge) + sets.dischrg_voltage;
            //If partial charge is less than the open circuit voltage of the battery
            //then set partial charge voltage to just above the open circuit voltage
            //so that we don't discharge the battery any while a charger is plugged in.
            if(dsky.chrg_voltage < open_voltage && CONDbits.got_open_voltage) dsky.chrg_voltage = open_voltage + 0.01;
            //If it ends up being higher than battery max charge voltage then clamp it.
            if(dsky.chrg_voltage > sets.battery_rated_voltage) dsky.chrg_voltage = sets.battery_rated_voltage;
        }
        else if(vars.partial_chrg_cnt >= 10){
            vars.partial_chrg_cnt = 0;
            p_charge = 0;
            dsky.chrg_voltage = sets.battery_rated_voltage;
        }

        //Reset battery usage session when charger is plugged in and power is turned off.
        if(!keySwitch && !CONDbits.cmd_power){
            vars.battery_usage = 0;
        }
        CONDbits.charger_detected = 1;  //Set this variable to 1 so that we only run this routine once per charger plugin.
    }
    else if(!chrgSwitch) {
        CONDbits.charger_detected = 0;  //If charger has been unplugged, clear this.
    }
}

//Initiate current calibration, heater calibration, and try to get battery capacity from NVmem upon cold and dead startup.
void initialCal(void){
    //Calibrate the current sense and calculate remaining capacity on first power up based on voltage percentage and rated capacity of battery.
    if(first_cal == 0 && curnt_cal_stage == 0){
        curnt_cal_stage = 1;
        CONDbits.soft_power = 1;
        first_cal = 1;
    }
    else if(curnt_cal_stage == 5 && first_cal < fCalTimer)first_cal++; //delay, wait about 1 second for other services to complete.

    else if (first_cal == 2 && CONDbits.got_open_voltage){
        //Check to see if we have valid data in EEPROM that we can start with.
        if (eeprom_read((cfg_space) + 1) == 0x7654 && vars.battery_capacity > 1){
            //Calculate how much power was used while the power was off. This is not exact, but should be close enough.
            int power_diff = (vars.battery_capacity * ((vars.voltage_percentage_old - voltage_percentage) / 100));
            vars.battery_remaining -= power_diff;        //Subtract the power difference
            vars.absolute_battery_usage -= power_diff;
            vars.battery_usage -= power_diff;
        }
        //Get a first startup value for amp hours and battery remaining.
        else{
            CONDbits.gotBatteryAmps = 1;
            vars.battery_capacity = sets.amp_hour_rating; //Just use the amp hour rating on first start.
            vars.battery_remaining = sets.amp_hour_rating * (voltage_percentage / 100);   //Rough estimation of how much power is left.
        }
        first_cal = fCalReady;      //Signal that we are done with power up.
        CONDbits.soft_power = 0;
    }
}

//System debug safemode
void death_loop(void){
    general_shutdown();     //Turn everything off.
    sys_debug();    //Disable everything that is not needed. Only Serial Ports and Timer 1 Active. 
    errLight = 1;  //Turn Error light solid on to show fatal error.
    for(;;){
        CPUact = 0;      //Turn CPU ACT light off.
        Idle();
    }
}

//Warm start and reset check.
void first_check(void){
    static int reset_chk;              //Do not initialize this var. Needs to stay the same on a reset.
    //Do not check why we reset on initial power up. No reason to. We don't want a reset error on first power up.
    if(reset_chk == 0xAA55){
        reset_check();              //Check for reset events from a warm restart.
    }
    reset_chk = 0xAA55;         //Warm start.
}
//Main Power Check.
void main_power_check(void){
    /* Check for charger, key, or software power up. */
    if((chrgSwitch || keySwitch || CONDbits.soft_power || CONDbits.cmd_power)){
        CONDbits.pwr_detect = 1;         //Used for blinking error light when in a fault shutdown.
        //Reset Overcurrent shutdown timer.
        if(shutdown_timer){
            STINGbits.fault_shutdown = 0;
            STINGbits.osc_fail_event = 0;
            shutdown_timer = 0;
        }
        //Check for fault shutdown. Turn off non-critical systems if it is a 1.
        if(!STINGbits.fault_shutdown){
            CONDbits.main_power = 1;     //Main power is ON.
            //Reinit if we haven't already.
            if (!STINGbits.init_done){
                Init();
            }
        }
        else{
            io_off();
            CONDbits.main_power = 0;
            //Deinit if we haven't already.
            if (!STINGbits.lw_pwr){
                low_power_mode();   //Go into idle mode with heart beat running.
            }
        }
    }
    else{
        io_off();
        CONDbits.pwr_detect = 0;     //Used for blinking error light when in a fault shutdown.
        CONDbits.main_power = 0;     //Main power is OFF.
        //Deinit if we haven't already.
        if (!STINGbits.lw_pwr){
            low_power_mode();   //Go into idle mode with heart beat running.
        }
    }
}

void analog_sanity(void){
    //Battery Voltage
    if(adcVoltage > 0xFFFD){
        fault_log(0x1D);
        general_shutdown();     //If we can't get battery voltage then what's the point of living?
    }
    if(adcVoltage < 0x0002){
        fault_log(0x1E);
        general_shutdown();     //If we can't get battery voltage then what's the point of living?
    }
    //Battery Current
    if(adcCurrent > 0xFFFD){
        fault_log(0x1F);
        general_shutdown();
    }
    if(adcCurrent < 0x0002){
        fault_log(0x20);
        general_shutdown();
    }
    //Battery temperature.
    if(adcBTemp > 0xFFFD){
        fault_log(0x21);
        vars.heat_cal_stage = disabled;     //Disable Heater if we can't get battery temperature.
    }
    if(adcBTemp < 0x0002){
        fault_log(0x22);
        vars.heat_cal_stage = disabled;     //Disable Heater if we can't get battery temperature.
    }
    //motor controller temperature.
    //We can live with these temps in error so don't bother disabling or shutting anything down here. Just log the error.
    if(adcMTemp > 0xFFFD){
        fault_log(0x23);
    }
    if(adcMTemp < 0x0002){
        fault_log(0x24);
    }
    //Snowman's temperature.
    if(adcSTemp > 0xFFFD){
        fault_log(0x25);
    }
    if(adcSTemp < 0x0002){
        fault_log(0x26);
    }
    if(CONDbits.failSave)save_vars();
}

//Check reset conditions and log them.
void reset_check(void){
    if(RCONbits.BOR){
        RCONbits.BOR = 0;
        fault_log(0x13);        //Brown Out Event.
    }
    if(RCONbits.WDTO){
        RCONbits.WDTO = 0;
        fault_log(0x14);        //WDT Reset Event.
    }
    if(RCONbits.TRAPR){
        RCONbits.TRAPR = 0;
        fault_log(0x15);        //TRAP Conflict Event. Multiple TRAPs at the same time.
    }
    if(RCONbits.IOPUWR){
        RCONbits.IOPUWR = 0;
        fault_log(0x16);        //Illegal opcode or uninitialized W register access Event.
    }
    if(RCONbits.EXTR){
        RCONbits.EXTR = 0;
        fault_log(0x17);        //External Reset Event.
    }
    if(RCONbits.SWR){
        RCONbits.SWR = 0;
        fault_log(0x18);        //Reset Instruction Event.
    }
    fault_log(0x19);        //General Reset Check. Did we start from cold? If not then log that we had a reset.
    if(CONDbits.failSave)save_vars();
}

//Used to log fault codes. Simple eh? Just call it with the code you want to log.
void fault_log(int f_code){
    if (vars.fault_count < 10){
        vars.fault_codes[vars.fault_count] = f_code;
        vars.fault_count++;
    }
    else{
        vars.fault_count = 11;       //Fault log full.
    }
    CONDbits.failSave = 1;
}

//Heater failed to initialize.
void heatStuffOff(void){
    heatPWM = off;
    heat_power = off;
    heat_rly_timer = 3;     //Reset heat relay timer
    heat_set = off;
    if(vars.heat_cal_stage != disabled)vars.heat_cal_stage = error;
    CONDbits.soft_power = off; //Go back to normal operation.
    heatRelay = off;     //Heat Relay Off
}
//Check and calibrate heater to the wattage chosen by the user.
void heater_calibration(void){
    if (vars.heat_cal_stage == calibrating && CONDbits.main_power){
        float watts = (dsky.battery_voltage * dsky.battery_current) * -1;
        if (watts < sets.max_heat){
        heatRelay = on;     //Heat Relay On
            if(heat_rly_timer == 0){
                heat_set++;
                heatPWM = heat_set;
                if (heat_set > 95){
                    fault_log(0x01);      //Log fault, heater is too small for the watts you want.
                    heatStuffOff();
                }
                if (heat_set > 50 && watts < 2){
                    fault_log(0x02);      //Log fault, no heater detected.
                    heatStuffOff();
                }
                if (heat_set < 5 && watts > 10){
                    fault_log(0x03);      //Log fault, short circuit on heater.
                    heatStuffOff();
                }
                if(CONDbits.failSave)save_vars();
            }
            if(heat_rly_timer == 3)
                heat_rly_timer = 2; //wait two 0.125ms cycles before allowing heat regulation to start.
        }
        else{
            vars.heat_cal_stage = ready; // Heater calibration completed.
            heatPWM = off;        //Heater PWM output off.
            CONDbits.soft_power = off; //Go back to normal operation.
            heatRelay = off;     //Heat Relay Off
            heat_rly_timer = 3;     //Reset heat relay timer
        }
    }
    if (vars.heat_cal_stage == initialize){
        heatPWM = off;    //Heater PWM output off.
        Init();         //Re-init.
        io_off();    //Turn off all inputs and outputs.
        CONDbits.soft_power = 1; //Force device to run in soft power mode.
        heat_set = off;
        heat_power = off;
        vars.heat_cal_stage = calibrating; //If heat_cal_stage is 2 then a calibration is in progress.
        heat_rly_timer = 3;     //Reset heat relay timer
    }
}

//Check battery status for faults and dangerous conditions.
void explody_preventy_check(void){
    //Battery over voltage check
    if(dsky.battery_voltage >= sets.max_battery_voltage){
        fault_log(0x07);    //Log a high battery voltage shutdown event.
        general_shutdown();
    }
    //Battery under voltage check.
    if(dsky.battery_voltage < sets.low_voltage_shutdown && chrgSwitch == 0){
        fault_log(0x04);    //Log a low battery shutdown event.
        low_battery_shutdown();
    }
    //Battery temp shutdown check
    if(dsky.battery_temp > sets.battery_shutdown_temp){
        fault_log(0x08);    //Log a battery over temp shutdown event.
        general_shutdown();
    }
    //Controller temp shutdown check
    if(dsky.motor_ctrl_temp > sets.ctrlr_shutdown_temp){
        fault_log(0x09);    //Log a motor controller over temp shutdown event.
        general_shutdown();
    }
    //My temp shutdown check
    if(dsky.my_temp > sets.ctrlr_shutdown_temp){
        fault_log(0x0A);    //Log a My Temp over temp shutdown event.
        general_shutdown();
    }
    if(CONDbits.failSave)save_vars();
}


void currentCheck(void){
        //Battery over current check.
    if(dsky.battery_current < 0){
        dischr_current = dsky.battery_current * -1;
    }
    else {
        dischr_current = 0;
    }
    if(dischr_current > sets.over_current_shutdown){
        if(oc_shutdown_timer > 5){
            general_shutdown();
            oc_shutdown_timer = 0;
            fault_log(0x05);    //Log a discharge over current shutdown event.
        }
        oc_shutdown_timer++;
    }
    //Battery charge over current check.
    if(dsky.battery_current > max_chrg_current){
        general_shutdown();
        fault_log(0x06);    //Log a charge over current shutdown event.
    }
    if(CONDbits.failSave)save_vars();
}

//Turns off all outputs and logs a general shutdown event.
void general_shutdown(void){
    io_off();               //Shutdown all IO except Serial Comms.
    STINGbits.fault_shutdown = 1;       //Tells other stuff that we had a general shutdown.
    CONDbits.cmd_power = 0;
    CONDbits.soft_power = 0;
    fault_log(0x0B);            //Log a general Shutdown Event.
}

//Turns off all outputs.
void io_off(void){
//    PORTDbits.RD3 = 0;      //output shutdown. Not Used In current Schematic.
    outPWM = off;            //set output control
    LATE = off;               //Insure all PORTE outputs are off.
    PWMCON1bits.PEN3L = off;  //Set PWM3 Low side to standard output so that it can be set to 0
    heatPWM = off;            //set heater control
    chrgPWM = off;            //set charge control
    ctRelay = off;      //Main Contactor Relay Off
    contact_rly_timer = 3;  //reset contactor relay timer
    fanRelay = off;      //Fan Relay Off
    chrgRelay = off;      //Charger Relay Off
    chrg_rly_timer = 3;     //reset charge relay timer
    heatRelay = off;     //Heat Relay Off
    heat_rly_timer = 3;     //reset heat relay timer
    AUXrelay = off;      //Aux Power Relay Off
    heat_power = off;         //set heater control to 0
    charge_power = off;       //set charge control to 0
    output_power = off;       //set output control to 0
    current_output = off;
    crnt_integral = off;
}

#endif