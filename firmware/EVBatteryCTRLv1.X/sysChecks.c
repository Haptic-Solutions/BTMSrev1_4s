/*Copyright (c) <2024> <Jarrett Cigainero>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

#ifndef SYSCHKS_C
#define SYSCHKS_C

#include "sysChecks.h"
#include "common.h"
#include "eeprom.h"

void chargeDetect(void){
    if(dsky.Cin_voltage>4.8 && vars.heat_cal_stage > calibrating){
        //Check for various charging standards.
        if(charge_mode == Ready){
            if(dsky.Cin_voltage<5.2){
                if(V_Bus_Stat){
                    //Mom! Can we get USB 3.1 charging?
                    //No sweetie, we have USB 3.1 charging at home.
                    //*USB 3.1 charging at home*
                    Max_Charger_Current=2.5; //USB_3.1 up to 25v. Probably a cheap wimpy charger if it can only do 5v, don't overload it.
                    Charger_Target_Voltage = 4.8; //Don't pull so much current that the charger voltage goes below this.
                    charge_mode = USB3_Wimp;
                }
                else{ 
                    Max_Charger_Current=1.4; //USB_2.0 and down. Likely USB_2.0 charger.
                    Charger_Target_Voltage = 4.8; //Don't pull so much current that the charger voltage goes below this. Could be a cheap charger or bad cable.
                    charge_mode = USB2;
                }
            }
            else if(dsky.Cin_voltage<19){
                if(V_Bus_Stat){
                    Max_Charger_Current=3; //USB_3.1 up to 25v.
                    Charger_Target_Voltage = dsky.Cin_voltage-0.5; //Don't pull so much current that the charger voltage goes below this. Could be a cheap charger or bad cable.
                    charge_mode = USB3;
                }
                else {
                    Max_Charger_Current=AuxFuse; //Assume solar or some other input. Target voltage will be determined by MPPT.
                    charge_mode = Solar;
                }
            }
            else if(dsky.Cin_voltage<21){
                if(V_Bus_Stat){
                    Max_Charger_Current=5; //USB_3.1 up to 25v.
                    Charger_Target_Voltage = 19.5; //Don't pull so much current that the charger voltage goes below this. Could be a cheap charger or bad cable.
                    charge_mode = USB3_Fast;
                }
                else {
                    Max_Charger_Current=AuxFuse; //Assume solar or some other input. Target voltage will be determined by MPPT.
                    charge_mode = Solar;
                }
            }
            else if(dsky.Cin_voltage<26){
                if(V_Bus_Stat){
                    Max_Charger_Current=0; //USB_3.1 error? Voltage should not be this high from any supported USB chargers.
                    charge_mode = Stop;
                    fault_log(0x1B);
                    general_shutdown();
                }
                else {
                    Max_Charger_Current=AuxFuse; //Assume solar or some other input. Target voltage will be determined by MPPT.
                    charge_mode = Solar;
                }
            }
            else {
                //Overvoltage condition.
                charge_mode = Stop;
                fault_log(0x38);
                general_shutdown();
            }
            STINGbits.charge_GO=1;
        }
        if(CHwaitTimer < 2)CHwaitTimer++;
        else charge_mode = Ready;
    }
    if(dsky.Cin_voltage<3 && charge_mode != Wait){
        charge_mode = Wait;
        CHwaitTimer=0;
    }
    
    //Check to see if we got set to USB2 mode during sunrise while plugged into solar.
    //if(charge_mode == USB2 && dsky.Cin_voltage>5.2){
    //    charge_mode = Solar;
    //}

    //Check to see if charger has been plugged in, if this routine has been run already, and that initial calibration is done.
    if(!CONDbits.charger_detected && STINGbits.charge_GO && first_cal == fCalReady){
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
        //If partial_charge is set to 0% then we disable and charge the battery up to full every time.
        if(sets.partial_charge == 0){
            dsky.chrg_voltage = sets.battery_rated_voltage;
            STINGbits.p_charge = 0;
        }
        //Do a full charge every 10 cycles so that we can ballance the cells.
        //Need to make this configure-able by the user at runtime.
        if(vars.partial_chrg_cnt < 10){
            vars.partial_chrg_cnt++;
            STINGbits.p_charge = 1;
            dsky.chrg_voltage = ((sets.battery_rated_voltage - sets.dischrg_voltage) * sets.partial_charge) + sets.dischrg_voltage;
            //If partial charge is less than the open circuit voltage of the battery
            //then set partial charge voltage to just above the open circuit voltage
            //so that we don't discharge the battery any while a charger is plugged in.
            if(dsky.chrg_voltage < dsky.open_voltage && CONDbits.got_open_voltage) dsky.chrg_voltage = dsky.open_voltage + 0.01;
            //If it ends up being higher than battery rated voltage then clamp it.
            if(dsky.chrg_voltage > sets.battery_rated_voltage) dsky.chrg_voltage = sets.battery_rated_voltage;
        }
        //Do full charge.
        else if(vars.partial_chrg_cnt >= 10){
            vars.partial_chrg_cnt = 0;
            STINGbits.p_charge = 0;
            dsky.chrg_voltage = sets.battery_rated_voltage;
        }

        //Reset battery usage session when charger is plugged in and power is turned off.
        if(!__PwrKey && !CONDbits.cmd_power){
            vars.battery_usage = 0;
        }
        CONDbits.charger_detected = 1;  //Set this variable to 1 so that we only run this routine once per charger plugin.
    }
    else if(!BV_Fault) {
        CONDbits.charger_detected = 0;  //If charger has been unplugged, clear this.
    }
}

//Initiate current calibration, heater calibration, and try to get battery capacity from NVmem upon cold and dead startup.
void initialCal(void){
    //Calibrate the current sense and calculate remaining capacity on first power up based on voltage percentage and rated capacity of battery.
    if(first_cal == 0 && Bcurnt_cal_stage == 0){
        Bcurnt_cal_stage = 1;
        CONDbits.soft_power = 1;
        first_cal = 1;
    }
    else if(Bcurnt_cal_stage == 5 && first_cal < fCalTimer)first_cal++; //delay, wait about 1 second for other services to complete.

    else if (first_cal == 2 && CONDbits.got_open_voltage){
        //Check to see if we have valid data in EEPROM that we can start with.
        int lowestCell = 4;
        if (eeprom_read((cfg_space) + 1) == 0x7654 && vars.battery_capacity > 1){
            //Calculate how much power was used while the power was off. This is not exact, but should be close enough.
            //Use lowest cell.
            float previousCell = 100;
            for(int i=0;i<4;i++){
                if(voltage_percentage[i]<previousCell){
                    lowestCell = i;
                    previousCell=voltage_percentage[i];
                }
            }
            int power_diff = (vars.battery_capacity * ((vars.voltage_percentage_old[lowestCell] - voltage_percentage[lowestCell]) / 100));
            vars.battery_remaining -= power_diff;        //Subtract the power difference
            vars.absolute_battery_usage -= power_diff;
            vars.battery_usage -= power_diff;
        }
        //Get a first startup value for amp hours and battery remaining.
        else{
            CONDbits.gotBatteryAmps = 1;
            vars.battery_capacity = sets.amp_hour_rating; //Just use the amp hour rating on first start.
            vars.battery_remaining = sets.amp_hour_rating * (voltage_percentage[lowestCell] / 100);   //Rough estimation of how much power is left.
        }
        first_cal = fCalReady;      //Signal that we are done with power up.
        CONDbits.soft_power = 0;
    }
}

//System debug safemode
void death_loop(void){
    general_shutdown();     //Turn everything off.
    sys_debug();    //Disable everything that is not needed. Only Serial Ports and Timer 1 Active.
    STINGbits.errLight = 1;  //Turn Error light solid on to show fatal error.
    for(;;){
        //CPUact = 0;      //Turn CPU ACT light off.
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
    if((STINGbits.charge_GO || __PwrKey || CONDbits.soft_power || CONDbits.cmd_power)){
        CONDbits.pwr_detect = 1;         //Used for blinking error light when in a fault shutdown.
        //Reset Overcurrent shutdown timers.
        if(shutdown_timer){
            STINGbits.fault_shutdown = 0;
            STINGbits.osc_fail_event = 0;
            shutdown_timer = 0;
        }
        soft_OVC_Timer = SOC_Cycles;
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
    //Charger input Voltage
    if(ChargeVoltage > 0xFFFD){
        fault_log(0x1D);
        general_shutdown();
    }
    if(ChargeVoltage < 0x0002){
        fault_log(0x1E);
        general_shutdown();
    }
    //Charger Current
    if(CCsense > 0xFFFD){
        fault_log(0x1F);
        general_shutdown();
    }
    if(CCsense < 0x0002){
        fault_log(0x20);
        general_shutdown();
    }
    //Cell 1 Voltage
    if(LithCell_V1 > 0xFFFD){
        fault_log(0x30);
        general_shutdown();
    }
    if(LithCell_V1 < 0x0002){
        fault_log(0x31);
        general_shutdown();
    }
    //Cell 2 Voltage
    if(LithCell_V2 > 0xFFFD){
        fault_log(0x32);
        general_shutdown();
    }
    if(LithCell_V2 < 0x0002){
        fault_log(0x33);
        general_shutdown();
    }
    //Cell 3 Voltage
    if(LithCell_V3 > 0xFFFD){
        fault_log(0x34);
        general_shutdown();
    }
    if(LithCell_V3 < 0x0002){
        fault_log(0x35);
        general_shutdown();
    }
    //Cell 4 Voltage
    if(LithCell_V4 > 0xFFFD){
        fault_log(0x36);
        general_shutdown();
    }
    if(LithCell_V4 < 0x0002){
        fault_log(0x37);
        general_shutdown();
    }
    //Battery Current
    if(BCsense > 0xFFFD){
        fault_log(0x23);
        general_shutdown();
    }
    if(BCsense < 0x0002){
        fault_log(0x24);
        general_shutdown();
    }
    //Battery temperature.
    if(Btemp > 0xFFFD){
        fault_log(0x21);
        vars.heat_cal_stage = disabled;     //Disable Heater if we can't get battery temperature.
    }
    if(Btemp < 0x0002){
        fault_log(0x22);
        vars.heat_cal_stage = disabled;     //Disable Heater if we can't get battery temperature.
    }
    //We can live with these temps in error so don't bother disabling or shutting anything down here. Just log the error.
    //Snowman's temperature.
    if(Mtemp > 0xFFFD){
        fault_log(0x25);
    }
    if(Mtemp < 0x0002){
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
    Heat_CTRL = off;
    heat_power = off;
    heat_rly_timer = 3;     //Reset heat relay timer
    heat_set = off;
    if(vars.heat_cal_stage != disabled)vars.heat_cal_stage = error;
    CONDbits.soft_power = off; //Go back to normal operation.
    PowerOutEnable = off;     //Heat Relay Off
}
//Check and calibrate heater to the wattage chosen by the user.
void heater_calibration(void){
    if (vars.heat_cal_stage == calibrating && CONDbits.main_power){
        float watts = (dsky.pack_voltage * dsky.battery_current) * -1;
        if (watts < sets.max_heat){
        PowerOutEnable = on;     //Heat Relay On
            if(heat_rly_timer == 0){
                heat_set++;
                Heat_CTRL = heat_set;
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
            Heat_CTRL = off;        //Heater PWM output off.
            CONDbits.soft_power = off; //Go back to normal operation.
            PowerOutEnable = off;     //Heat Relay Off
            heat_rly_timer = 3;     //Reset heat relay timer
        }
    }
    if (vars.heat_cal_stage == initialize){
        Heat_CTRL = off;    //Heater PWM output off.
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
    if(dsky.pack_voltage >= sets.max_battery_voltage){
        fault_log(0x07);    //Log a high battery voltage shutdown event.
        general_shutdown();
    }
    //Battery under voltage check.
    if(dsky.pack_voltage < sets.low_voltage_shutdown && !STINGbits.charge_GO){
        fault_log(0x04);    //Log a low battery shutdown event.
        low_battery_shutdown();
    }
    //Battery temp shutdown check
    if(dsky.battery_temp > sets.battery_shutdown_temp){
        fault_log(0x08);    //Log a battery over temp shutdown event.
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
    CH_Boost = off;           //set charge boost control off.
    CHctrl = off;             //set charge control off.
    Heat_CTRL = off;          //set heater control off.
    PreCharge = off;          //Turn off pre-charge circuit.
    PowerOutEnable = off;     //Output off.
    heat_power = off;         //set heater routine control off.
}

#endif
