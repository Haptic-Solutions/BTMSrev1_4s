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

#ifndef SAFECHKS_C
#define SAFECHKS_C

#include "safetyChecks.h"
#include "common.h"
#include "eeprom.h"

//System debug safemode
inline void death_loop(void){
    ALL_shutdown();     //Turn everything off.
    init_sys_debug();    //Disable everything that is not needed. Only Serial Ports and some system timers active.
    LED_Mult(Debug);  //Turn debug lights solid on to show fatal error.
    fault_log(0x3D, 0x00);
    for(;;){
        //CPUact = 0;      //Turn CPU ACT light off.
        Exception_Check();
        Idle();
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

//Check battery status for faults and dangerous conditions.
inline void explody_preventy_check(void){
    //Check hardware fault pins. Manually trigger IRQ if there is a fault.
    if(BV_Fault)IFS0bits.INT0IF = 1;
    if(C_Fault)IFS1bits.INT1IF = 1;
    //Battery over voltage check
    for(int i=0;i<sets.Cell_Count;i++){
        if(Cell_Voltage_Average[i] > sets.max_battery_voltage){
            if(OV_Timer[i]<4)OV_Timer[i]++;
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

//Gets ran from 0.125s IRQ in sysIRQs.c
//Ran every Nth analog input IRQ
inline void currentCheck(void){
    //Battery over current check.
    float dischCrnt_temp = 0;
    if(dsky.battery_current < 0)dischCrnt_temp = dsky.battery_current * -1;
    else dischCrnt_temp = 0;

    if(dischCrnt_temp > sets.over_current_shutdown){
        if(oc_shutdown_timer > 5){
            fault_log(0x05, 0x00);    //Log a discharge over current shutdown event.
            ALL_shutdown();
            oc_shutdown_timer = 0;
        }
        oc_shutdown_timer++;
    }
    //Battery charge over current check.
    else if(dsky.battery_current > sets.chrg_C_rating * sets.amp_hour_rating){
        if(oc_shutdown_timer > 5){
            fault_log(0x06, 0x00);    //Log a discharge over current shutdown event.
            ALL_shutdown();
            oc_shutdown_timer = 0;
        }
        oc_shutdown_timer++;
    }
    else if(oc_shutdown_timer > 0) oc_shutdown_timer--;
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
