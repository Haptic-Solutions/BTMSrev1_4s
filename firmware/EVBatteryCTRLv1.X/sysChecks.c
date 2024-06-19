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
#include "safetyChecks.h"
#include "common.h"
#include "eeprom.h"

void chargeInhibit(char inhibit){
    ch_cycle=0;
    charge_mode = Wait;
    CONDbits.charger_detected = no;
    STINGbits.CH_Voltage_Present = no;
    CH_Boost = off;           //set charge boost control off.
    CHctrl = off;             //set charge control off.
    if(inhibit){
        CONDbits.Chrg_Inhibit = 1;
    }
    else CONDbits.Chrg_Inhibit = 0;
}

void chargeDetect(void){
    if(dsky.Cin_voltage>4.8 && vars.heat_cal_stage != calibrating && !D_Flag_Check() && charge_mode > Stop && first_cal == fCalReady && !CONDbits.Chrg_Inhibit){
        //Check for various charging standards.
        if(charge_mode == Assignment_Ready){
            if(dsky.Cin_voltage<6){
                if(Set_PD_Option(Get_Highest_PD())==1){
                    Max_Charger_Current=PD_Last_Current*charge_Max_Level;   //Don't run charger more than this capacity.
                    Charger_Target_Voltage = PD_Last_Voltage-(10/PD_Last_Current);  //Calculate max heat loss allowed through cable and connections.
                    charge_mode = USB3;
                }
                else{ 
                    Max_Charger_Current=1.4; //USB_2.0 and down. Likely USB_2.0 charger.
                    Charger_Target_Voltage = 5-(0.5/Max_Charger_Current); //Don't pull so much current that the charger voltage goes below this. Could be a cheap charger or bad cable.
                    charge_mode = USB2;
                }
            }
            else if(dsky.Cin_voltage<25.1){
                Max_Charger_Current=AuxFuse; //Assume solar or some other input. Target voltage will be determined by MPPT.
                charge_mode = Solar;
            }
            else {
                //Overvoltage condition.
                charge_mode = CHError;
                fault_log(0x38, 0x00);
                ALL_shutdown();
            }
            if(STINGbits.Force_Max_Cnt_Limit)Max_Charger_Current=0.2;
        }
        else if(CHwaitTimer < 4 && charge_mode == Wait)CHwaitTimer++;
        else if(charge_mode == Wait && CHwaitTimer>=4){
            charge_mode = Assignment_Ready;
            CHwaitTimer=0;
        }
        //Check if settings are locked and we can go-ahead with the charging process
        STINGbits.CH_Voltage_Present = set;     //Charger is detected
    }
    //Wait for voltage to stabilize, or reset from a stop condition unless the charging system has cycled too many times.
    else if(dsky.Cin_voltage<C_Min_Voltage){
        STINGbits.CH_Voltage_Present = clear;
        if((charge_mode == CHError && Run_Level == Heartbeat) && ch_cycle>0)ch_cycle--; //Cool down the timer when power is disconnected.
        else if (charge_mode == CHError && ch_cycle == 0)charge_mode = Wait;
    }
    if(charge_mode == Stop && ch_cycle > cycleLimit){
        charge_mode = CHError;
        fault_log(0x3C, Ch_Err_Attrib);
    }
    else if(charge_mode == Stop){
        ch_cycle++;
        charge_mode = Wait;
        CHwaitTimer=0;
        if(ch_cycle>cycleLimit-2)STINGbits.Force_Max_Cnt_Limit=set;    //If the charger cycles 3 times, try forcing a low current limit.
    }
    
    //Check to see if we got set to USB2 mode during sunrise while plugged into solar.
    //if(charge_mode == USB2 && dsky.Cin_voltage>5.2){
    //    charge_mode = Solar;
    //}

    //Check to see if charger has been plugged in, or if this routine has been run already.
    if(!CONDbits.charger_detected && STINGbits.CH_Voltage_Present && charge_mode > Assignment_Ready && (Flags&syslock)){
        //reset peak power when we plug in a charger.
        dsky.peak_power = 0;
        //Check for partial charge status to see if we need to do a full charge to ballance the cells.
        //If partial_charge is greater than 100%, set to 100% and write the new value.
        if(sets.partial_charge > 1){
            TMR4 = 0;   //Reset timer 4 to prevent a check between writes.
            sets.partial_charge = 1;
            save_sets();
            fault_log(0x1C, 0x00);         // Log Partial charge was set higher than 100% event.
        }
        //If partial_charge is set to 0% then we disable and charge the battery up to full every time.
        float packChargeVoltage = sets.cell_rated_voltage * sets.Cell_Count;
        float packDischrgVoltage = sets.dischrg_voltage * sets.Cell_Count;
        if(sets.partial_charge == 0){
            dsky.chrg_voltage = packChargeVoltage;
            STINGbits.p_charge = 0;
        }
        //Do a full charge every 10 cycles so that we can ballance the cells.
        if(vars.partial_chrg_cnt < 10){
            vars.partial_chrg_cnt++;
            STINGbits.p_charge = 1;
            dsky.chrg_voltage = ((packChargeVoltage - packDischrgVoltage) * Vcurve_calc(sets.partial_charge)) + packDischrgVoltage;
            //If partial charge is less than the open circuit voltage of the battery
            //then set partial charge voltage to just above the open circuit voltage
            //so that we don't discharge the battery any while a charger is plugged in.
            if(dsky.chrg_voltage < dsky.open_voltage) dsky.chrg_voltage = dsky.open_voltage + 0.01;
            //If it ends up being higher than battery rated voltage then clamp it.
            if(dsky.chrg_voltage > packChargeVoltage) dsky.chrg_voltage = packChargeVoltage;
        }
        //Do full charge.
        else if(vars.partial_chrg_cnt >= 10){
            vars.partial_chrg_cnt = 0;
            STINGbits.p_charge = 0;
            dsky.chrg_voltage = packChargeVoltage;
        }

        //Reset battery usage session when charger is plugged in and power is turned off.
        if(!CONDbits.Power_Out_EN){
            vars.battery_usage = 0;        //Need to make this configure-able by the user at runtime.
        }
        CONDbits.charger_detected = 1;  //Set this variable to 1 so that we only run this routine once per charger plugin.
        power_session = UnknownStart; //Reset capacity meter routine if a charger is plugged in.
    }
    else if(!STINGbits.CH_Voltage_Present){
        CONDbits.charger_detected = 0;  //If charger has been unplugged, clear this.
    }
    //Calculate PWM Boost hard limit. Helps prevent current spikes that would otherwise trip the charger into shutting down.
    float C_of_B=0;
    if(charge_mode>=USB2&&charge_mode<=USB3_Fast)C_of_B = (dsky.pack_vltg_average-Charger_Target_Voltage)/11.8;  //Get percent of charger voltage vs battery voltage.
    else C_of_B = (dsky.pack_vltg_average-input_CavgVolt)/11.8;  //Get percent of charger voltage vs battery voltage.
    if(C_of_B<0)C_of_B=0;
    float PBoost = PWM_MaxBoost_LO+((PWM_MaxBoost_HI-PWM_MaxBoost_LO)*C_of_B);  //Convert that percent to a PWM limit withing a range.
    float MaxBoost = (PWM_Period*2)*PBoost;
    if(avg_rdy>0)PWM_MaxBoost=MaxBoost;
    else PWM_MaxBoost=PWM_MaxBoost_LN;
}

//Force a full charge.
void Full_Charge(void){
    STINGbits.p_charge = no;
    dsky.chrg_voltage = sets.cell_rated_voltage*sets.Cell_Count;
    if(CONDbits.charger_detected)vars.partial_chrg_cnt = clear;
    else vars.partial_chrg_cnt = 10;
}

//Initiate current calibration, heater calibration, and try to get battery capacity from NVmem upon cold startup.
//Gets run by 0.125s IRQ
void initialCal(void){
    //Calibrate the current sense and calculate remaining capacity on first power up based on voltage percentage and rated capacity of battery.
    if(first_cal == 0 && (Flags&syslock)){
        Run_Level = Cal_Mode;
        curnt_cal_stage = 1;   //Initiate current calibration routine.
        first_cal = 1;
    }
    //Wait until current calibration is complete
    else if(curnt_cal_stage == 3 && first_cal < fCalTimer)first_cal++;
    //Once current calibration is done, check battery current and get open circuit voltage for inital soc
    else if (first_cal == 2){
        first_cal = 3;      //Signal that we are done with power up sequence.
        //When current cal is done, set runlevel to heartbeat unless the heater is working.
        //Otherwise let the heater routine change the runlevel when it's done.
        if(vars.heat_cal_stage == disabled) Run_Level = Heartbeat;
    }
}

//Main Power Check.
//Gets run once per second from Heartbeat IRQ.
void main_power_check(void){
    /* Check for charger, or software power up. */
    if((CONDbits.charger_detected || CONDbits.Power_Out_EN) && (Run_Level != Cal_Mode)){
        //Reset Overcurrent shutdown timer and various fault shutdowns.
        if(shutdown_timer){
            STINGbits.errLight = clear;     //Even though we may still have errors logged, the user is trying again and needs to know their battery charge level.
            STINGbits.fault_shutdown = 0;   //Reset the software fuse.
            STINGbits.osc_fail_event = 0;
            shutdown_timer = 0;
        }
        soft_OVC_Timer = SOC_Cycles;
        //Check for fault shutdown. Turn off non-critical systems if it is a 1.
        if(STINGbits.fault_shutdown){
            Run_Level = On_W_Err;
            //Deinit if we haven't already.
            if (!STINGbits.lw_pwr_init_done){
                low_power_mode();   //Go into idle mode with heart beat running.
            }
        }
        else{
            Run_Level = All_Sys_Go;     //Main power is ON.
            //Reinit if we haven't already.
            if (!STINGbits.init_done){
                Init();
            }
        }
    }
    else if(Run_Level != Cal_Mode && Run_Level > Heartbeat){
        Run_Level = Heartbeat;     //System is idling in Heartbeat mode.
        //Deinit if we haven't already.
        if (!STINGbits.lw_pwr_init_done){
            low_power_mode();   //Go into idle mode with heart beat running.
        }
    }
}

//Warm start and reset check.
void first_check(void){
    //Do not check why we reset on initial power up. No reason to. We don't want a reset error on first power up.
    if(reset_chk == 0xAA55){
        reset_check();              //Check for reset events from a warm restart.
    }
    reset_chk = 0xAA55;         //Set to Warm start.
    Tfaults=0;
    rst_flag_rst();
}

//Heater failed to initialize.
void heatStuffOff(int RLtemp){
    Heat_CTRL = off;
    heat_power = off;
    heat_set = off;
    if(vars.heat_cal_stage != disabled)vars.heat_cal_stage = error;
    Run_Level = RLtemp; //Go back to whatever runlevel was running before.
    PowerOutEnable = off;     //Heat Relay Off
}
//Check and calibrate heater to the wattage chosen by the user.
void heater_calibration(void){
    int RLtemp = 0;
    if (vars.heat_cal_stage == calibrating && Run_Level == Cal_Mode){
        float watts = (dsky.pack_voltage * dsky.battery_current) * -1;
        if (watts < sets.max_heat){
            heat_set++;
            Heat_CTRL = heat_set;
            if (heat_set > PWM_MaxHeat){
                fault_log(0x01, 0x00);      //Log fault, heater is too small for the watts you want.
                heatStuffOff(RLtemp);
            }
            if (heat_set > (PWM_Period*2)*0.5 && watts < 0.5){
                fault_log(0x02, 0x00);      //Log fault, no heater detected.
                heatStuffOff(RLtemp);
            }
            if (heat_set < (PWM_Period*2)*0.1 && watts > 10){
                fault_log(0x03, 0x00);      //Log fault, short circuit on heater.
                heatStuffOff(RLtemp);
            }
        }
        else{
            vars.heat_cal_stage = ready; // Heater calibration completed.
            Heat_CTRL = off;        //Heater PWM output off.
            Run_Level = RLtemp; //Go back to whatever runlevel was running before.
            PowerOutEnable = off;     //Heat Relay Off
        }
    }
    if (vars.heat_cal_stage == initialize){
        //If we are already in cal_mode, then it's a first start and we need to go back to heartbeat when we are done.
        //Otherwise, go back to whatever runlevel mode we were already in when we are finished.
        if(Run_Level == Cal_Mode)RLtemp = Heartbeat; //Since this is the last thing that gets done during initial startup, go to RL heartbeat.
        else RLtemp = Run_Level;
        Run_Level = Cal_Mode;
        Heat_CTRL = off;    //Heater PWM output off.
        Init();         //Re-init.
        Batt_IO_OFF();    //Turn off all inputs and outputs.
        heat_set = off;
        heat_power = off;
        vars.heat_cal_stage = calibrating; //If heat_cal_stage is 2 then a calibration is in progress.
    }
}


#endif
