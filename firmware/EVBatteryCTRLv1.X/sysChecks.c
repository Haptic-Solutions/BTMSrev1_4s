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

inline void chargeDetect(void){
    if(dsky.Cin_voltage>4.8 && vars.heat_cal_stage != calibrating && !D_Flag_Check() && charge_mode > Stop && first_cal == fCalReady){
        slowINHIBIT_Timer = 10;
        //Check for various charging standards.
        if(charge_mode == Assignment_Ready){
            if(dsky.Cin_voltage<6){
                if(Set_PD_Option(Get_Highest_PD())==1){
                    Max_Charger_Current=PD_Last_Current*char_Max_Level;   //Don't run charger more than this capacity.
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
                charge_mode = Stop;
                fault_log(0x38, 0x00);
                ALL_shutdown();
            }
            if(STINGbits.Force_Max_Cnt_Limit)Max_Charger_Current=0.2;
        }
        else if(CHwaitTimer < 2 && charge_mode == Wait)CHwaitTimer++;
        else if(charge_mode == Wait){
            charge_mode = Assignment_Ready;
            U1MODEbits.UARTEN = 1;  //enable UART1
            U1STAbits.UTXEN = 1;    //enable UART1 TX
        }
        //Check if settings are locked and we can go-ahead with the charging process
        STINGbits.CH_Voltage_Present = set;     //Charger is detected
    }
    //Wait for voltage to stabilize, or reset from a stop condition unless the charging system has cycled too many times.
    else if(dsky.Cin_voltage<3){
        U1MODEbits.UARTEN = 0;  //enable UART1
        U1STAbits.UTXEN = 0;    //enable UART1 TX
        STINGbits.CH_Voltage_Present = clear;
        //if((charge_mode == CHError || Run_Level == Heartbeat) && ch_cycle>0)ch_cycle--; //Cool down the timer when power is disconnected.
        if(ch_cycle > cycleLimit){
            charge_mode = CHError;
            fault_log(0x3C, 0x00);
        }
        else if(charge_mode == Stop){
            ch_cycle++;
            charge_mode = Wait;
            CHwaitTimer=0;
            if(ch_cycle>3)STINGbits.Force_Max_Cnt_Limit=set;    //If the charger cycles 3 times, try a low current.
        }
        else if (charge_mode == CHError && ch_cycle == 0)charge_mode = Wait;
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
            ram_chksum_update();     //Update the checksum after a write.
            fault_log(0x1C, 0x00);         // Log Partial charge was set higher than 100% event.
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
        if(!CONDbits.Power_Out_EN){
            vars.battery_usage = 0;
        }
        CONDbits.charger_detected = 1;  //Set this variable to 1 so that we only run this routine once per charger plugin.
        power_session = UnknownStart; //Reset ;capacity meter routine if a charge is plugged in.
    }
    else if(!STINGbits.CH_Voltage_Present){
        CONDbits.charger_detected = 0;  //If charger has been unplugged, clear this.
    }
    //Calculate PWM Boost hard limit. Helps prevent current spikes that would otherwise trip the charger into shutting down.
    float C_of_B=0;
    if(charge_mode==USB2||charge_mode==USB3)C_of_B = (dsky.pack_vltg_average-Charger_Target_Voltage)/11.8;  //Get percent of charger voltage vs battery voltage.
    else C_of_B = (dsky.pack_vltg_average-CavgVolt)/11.8;  //Get percent of charger voltage vs battery voltage.
    float PBoost = PWM_MaxBoost_HI-((PWM_MaxBoost_HI-PWM_MaxBoost_LO)*C_of_B);  //Convert that percent to a PWM limit withing a range.
    float MaxBoost = (PWM_Period*2)*PBoost;
    if(avg_rdy>4)PWM_MaxBoost=MaxBoost;
    else PWM_MaxBoost=PWM_MaxBoost_LN;
}

//Initiate current calibration, heater calibration, and try to get battery capacity from NVmem upon cold and dead startup.
//Gets run by heartbeat IRQ
inline void initialCal(void){
    //Calibrate the current sense and calculate remaining capacity on first power up based on voltage percentage and rated capacity of battery.
    if(first_cal == 0 && (Flags&syslock)){
        Run_Level = Cal_Mode;
        Bcurnt_cal_stage = 1;   //Initiate current calibration routine.
        first_cal = 1;
    }
    //Wait until current calibration is complete
    else if(Bcurnt_cal_stage == 3 && first_cal < fCalTimer)first_cal++; //delay, wait about 1 second for other services to complete.
    //Once current calibration is done, check battery current and get open circuit voltage for inital soc
    else if (first_cal == 2 && CONDbits.got_open_voltage){

        if (eeprom_read((cfg_space) + 1) != 0x7654)
        CapacityCalc(); //Calculate approximate battery soc based on open circuit voltage.
        first_cal = 3;      //Signal that we are done with power up sequence.
        //When current cal is done, set runlevel to heartbeat unless the heater is working.
        //Otherwise let the heater routine change the runlevel when it's done.
        if(vars.heat_cal_stage == disabled) Run_Level = Heartbeat;
    }
}

//System debug safemode
inline void death_loop(void){
    ALL_shutdown();     //Turn everything off.
    init_sys_debug();    //Disable everything that is not needed. Only Serial Ports and Timer 1 Active.
    LED_Mult(Debug);  //Turn debug lights solid on to show fatal error.
    fault_log(0x3D, 0x00);
    for(;;){
        //CPUact = 0;      //Turn CPU ACT light off.
        Exception_Check();
        Idle();
    }
}

//Main Power Check.
//Gets run once per second from Heartbeat IRQ.
inline void main_power_check(void){
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

inline void analog_sanity(void){
    //Charger input Voltage
    if(ChargeVoltage > 0xFFFD){
        fault_log(0x1D, 0x00);
        ALL_shutdown();
    }
    //charger voltage is expected to go to 0v
    //if(ChargeVoltage < 0x0002){
    //    fault_log(0x1E);
    //    ALL_shutdown();
    //}
    //Charger Current
    if(CCsense > 0xFFFD){
        fault_log(0x1F, 0x00);
        ALL_shutdown();
    }
    if(CCsense < 0x0002){
        fault_log(0x20, 0x00);
        ALL_shutdown();
    }
    //Cell 1 Voltage
    if(LithCell_V1 > 0xFFFD){
        fault_log(0x30, 0x00);
        ALL_shutdown();
    }
    if(LithCell_V1 < 0x0002){
        fault_log(0x31, 0x00);
        ALL_shutdown();
    }
    //Cell 2 Voltage
    if(LithCell_V2 > 0xFFFD){
        fault_log(0x32, 0x00);
        ALL_shutdown();
    }
    if(LithCell_V2 < 0x0002){
        fault_log(0x33, 0x00);
        ALL_shutdown();
    }
    //Cell 3 Voltage
    if(LithCell_V3 > 0xFFFD){
        fault_log(0x34, 0x00);
        ALL_shutdown();
    }
    if(LithCell_V3 < 0x0002){
        fault_log(0x35, 0x00);
        ALL_shutdown();
    }
    //Cell 4 Voltage
    if(LithCell_V4 > 0xFFFD){
        fault_log(0x36, 0x00);
        ALL_shutdown();
    }
    if(LithCell_V4 < 0x0002){
        fault_log(0x37, 0x00);
        ALL_shutdown();
    }
    //Battery Current
    if(BCsense > 0xFFFD){
        fault_log(0x23, 0x00);
        ALL_shutdown();
    }
    if(BCsense < 0x0002){
        fault_log(0x24, 0x00);
        ALL_shutdown();
    }
    //Battery temperature.
    if(Btemp > 0xFFFD){
        fault_log(0x21, 0x00);
        ALL_shutdown();
        vars.heat_cal_stage = disabled;     //Disable Heater if we can't get battery temperature.
    }
    if(Btemp < 0x0002){
        fault_log(0x22, 0x00);
        ALL_shutdown();
        vars.heat_cal_stage = disabled;     //Disable Heater if we can't get battery temperature.
    }
    //Snowman's temperature.
    if(Mtemp > 0xFFFD){
        fault_log(0x25, 0x00);
        ALL_shutdown();
    }
    if(Mtemp < 0x0002){
        fault_log(0x26, 0x00);
        ALL_shutdown();
    }
}
//Reset flag reset
void rst_flag_rst(void){
    RCONbits.BOR = 0;
    RCONbits.WDTO = 0;
    RCONbits.TRAPR = 0;
    RCONbits.IOPUWR = 0;
    RCONbits.EXTR = 0;
    RCONbits.SWR = 0;
}
//Warm start and reset check.
inline void first_check(void){
    //Do not check why we reset on initial power up. No reason to. We don't want a reset error on first power up.
    if(reset_chk == 0xAA55){
        reset_check();              //Check for reset events from a warm restart.
    }
    reset_chk = 0xAA55;         //Set to Warm start.
    Tfaults=0;
    rst_flag_rst();
}
//Check reset conditions and log them.
inline void reset_check(void){
    //if(RCONbits.BOR)fault_log(0x13);        //Brown Out Event.
    if(RCONbits.WDTO)fault_log(0x14, 0x00);        //WDT Reset Event.
    if(RCONbits.TRAPR)fault_log(0x15, 0x00);        //TRAP Conflict Event. Multiple TRAPs at the same time.
    if(RCONbits.IOPUWR)fault_log(0x16, 0x00);        //Illegal opcode or uninitialized W register access Event.
    //if(RCONbits.EXTR)fault_log(0x17);        //External Reset Event.
    //if(RCONbits.SWR)fault_log(0x19);        //Reset Instruction Event.
    rst_flag_rst();
}

void Exception_Check(void){
    if(Tfaultsbits.OSC || INTCON1bits.OSCFAIL)fault_log(0x0D, 0x00);
    if(Tfaultsbits.STACK || INTCON1bits.STKERR)fault_log(0x0F, 0x00);
    if(Tfaultsbits.ADDRESS || INTCON1bits.ADDRERR)fault_log(0x0E, 0x00);
    if(Tfaultsbits.MATH || INTCON1bits.MATHERR)fault_log(0x10, 0x00);
    if(Tfaultsbits.FLTA || IFS2bits.FLTAIF)fault_log(0x0C, 0x00);        //PWM fault. External.
    if(Tfaultsbits.RESRVD)fault_log(0x11, 0x00);
    if(Tfaults)Run_Level = Crit_Err;
    Tfaults=0;
    INTCON1 &= 0xFF00;  ///Clear all flags after checking them.
    IFS2bits.FLTAIF=0;
}
//Used to log fault codes. Simple eh? Just call it with the code you want to log.
void fault_log(int f_code, int f_attribute){
    //Turn on fault light.
    STINGbits.errLight = 1;
    //Check fault pointer to make sure it is sane.
    if(vars.fault_count<0)vars.fault_count = 0;
    if(vars.fault_count>=maxFCodes)vars.fault_count = 0;
    //Check for redundant faults.
    char F_redun = 0;
    for(int i=0;i<vars.fault_count;i++){
        if(f_code==vars.fault_codes[0][i]){
            F_redun = 1;
        }
    }
    //Only log a fault if it's not redundant and the log isn't full and it's a valid fault.
    if (vars.fault_count < maxFCodes && !F_redun && f_code <= sizeof(errArray)){
        vars.fault_codes[0][vars.fault_count] = f_code;
        vars.fault_codes[1][vars.fault_count] = f_attribute;
        vars.fault_count++;
    }
    else if(!F_redun && f_code <= sizeof(errArray)){
        vars.fault_count = maxFCodes+1;       //Fault log full.
    }
    //CONDbits.failSave = 1;
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
inline void heater_calibration(void){
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

//Check battery status for faults and dangerous conditions.
inline void explody_preventy_check(void){
    //Check hardware fault pins. Manually trigger IRQ if there is a fault.
    if(BV_Fault)IFS0bits.INT0IF = 1;
    if(C_Fault)IFS1bits.INT1IF = 1;
    //Battery over voltage check
    for(int i=0;i<sets.Cell_Count;i++){
        if(Cell_Voltage_Average[i] > sets.max_battery_voltage){
            if(OV_Timer[i]<100)OV_Timer[i]++;
            else {
                fault_log(0x07, i+1);    //Log a high battery voltage shutdown event.
                Flags |= HighVLT;
                ALL_shutdown();
            }
        }
        else if(OV_Timer[i]>0)OV_Timer[i]-=2;
    }
    //Battery under voltage check.
    for(int i=0;i<sets.Cell_Count;i++){
        if(dsky.Cell_Voltage[i] < sets.low_voltage_shutdown && !STINGbits.CH_Voltage_Present){
            fault_log(0x3B, i+1);    //Log a low battery shutdown event.
            Flags |= LowVLT;
            low_battery_shutdown();
        }
    }
    //Battery temp shutdown check
    if(dsky.battery_temp > sets.battery_shutdown_temp){
        fault_log(0x08, 0x00);    //Log a battery over temp shutdown event.
        Flags |= BattOverheated;
        ALL_shutdown();
    }
    //My temp shutdown check
    if(dsky.my_temp > sets.ctrlr_shutdown_temp){
        fault_log(0x0A, 0x00);    //Log a My Temp over temp shutdown event.
        Flags |= SysOverheated;
        ALL_shutdown();
    }
    if(D_Flag_Check()){
        fault_log(0x09, 0x00);    //Log a compromised flag error.
        Run_Level = Crit_Err;
    }
}

//Gets ran from analog calc in file 'subs.c'
//Ran every 8th analog input IRQ
inline void currentCheck(void){
    //Battery over current check.
    float dischr_current = 0;
    if(dsky.battery_current < 0){
        dischr_current = dsky.battery_current * -1;
    }
    else {
        dischr_current = 0;
    }
    if(dischr_current > sets.over_current_shutdown){
        if(oc_shutdown_timer > 5){
            fault_log(0x05, 0x00);    //Log a discharge over current shutdown event.
            ALL_shutdown();
            oc_shutdown_timer = 0;
        }
        oc_shutdown_timer++;
    }
    else if(oc_shutdown_timer > 0) oc_shutdown_timer--;
    //Battery charge over current check.
    if(dsky.battery_current > sets.chrg_C_rating * sets.amp_hour_rating){
        fault_log(0x06, 0x00);    //Log a charge over current shutdown event.
        ALL_shutdown();
    }
}

//Turns off all outputs and logs a general shutdown event.
inline void ALL_shutdown(void){
    Batt_IO_OFF();               //Shutdown except Serial Comms.
    STINGbits.fault_shutdown = 1; //Tells other stuff that we had a fault so they know not to run.
    fault_log(0x0B, 0x00);            //Log a general Shutdown Event.
}

//Turns off all battery related inputs and outputs.
inline void Batt_IO_OFF(void){
    CH_Boost = off;           //set charge boost control off.
    CHctrl = off;             //set charge control off.
    PowerOutEnable = off;     //Output off.
    heat_power = off;         //set heater routine control off.
    power_session = UnknownStart; //If a discharge evaluation is disrupted then reset the meter routine.
    if(Run_Level != Cal_Mode)Heat_CTRL = off;          //set heater control off.
}

//Check un-resettable flags.
inline int D_Flag_Check(){
  if(Flags&0xFE) return yes; //Don't test first bit.
  return no;
}

#endif
