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

#ifndef SUBSYS_C
#define SUBSYS_C

#include "common.h"
#include "Init.h"
/* Fun fact, you can comment out these includes and it still compiles even though they are needed!
 * Probably because they are included in main.c IDK mplab is weird.
 */
inline void calcAnalog(void){
    /* I have left commented out code in this section for showing the process
        * of converting analog inputs into voltages, currents, and temps.
        */
        //Battery current.
        BavgCurnt /= 8;      //Sample average.
        BavgCurnt -= 32768;    //Set zero point.
        BavgCurnt /= 32768;    //Convert to signed fractional. -1 to 1
        BavgCurnt *= Half_ref;      //Convert to +-1.65 'volts'. It's still a 0 - 3.3 volt signal on the analog input. The zero point is at 1.65v
        dsky.battery_current = (BavgCurnt * 12.5) + Bcurrent_compensate; //Offset for ACS711ELCTR-25AB-T Current Sensor.
        BavgCurnt = 0;       //Clear average.
        
        //Charger current.
        CavgCurnt /= 8;      //Sample average.
        CavgCurnt -= 32768;    //Set zero point.
        CavgCurnt /= 32768;    //Convert to signed fractional. -1 to 1
        CavgCurnt *= Half_ref;      //Convert to +-1.65 'volts'. It's still a 0 - 3.3 volt signal on the analog input. The zero point is at 1.65v
        dsky.Cin_current = (CavgCurnt * 12.5) + Ccurrent_compensate; //Offset for ACS711ELCTR-25AB-T Current Sensor.
        CavgCurnt = 0;       //Clear average.

        if((Flags&syslock))currentCheck();     //Check for over current condition.
        //Battery voltage.
        //avgVolt /= 8;      //Sample average.
        //avgVolt /= 65535;  //Convert to unsigned fractional
        //avgVolt *= 3.3;      //Converted to 0 - 3.3V voltage.
        //analog_cost = (8*65535)/3.3
        //Do it all at once to save time.
        float S_V[Max_Cell_Count];
        for(int i=0;i<Max_Cell_Count;i++){
            BavgVolt[i] /= analog_const;
            if(CONDbits.V_Cal) S_V[i] = BavgVolt[i] / resistor_divide_const;
            else S_V[i] = (BavgVolt[i] / resistor_divide_const) + sets.S_vlt_adjst[i];    //Use resistor divider values to covert to actual voltage.
            BavgVolt[i] = 0;       //Clear average.
        }
        
        if(CONDbits.V_Cal){
            for(int i=0;i<Max_Cell_Count;i++)dsky.Cell_Voltage[i] = S_V[i];
        }
        else {
            dsky.Cell_Voltage[0] = S_V[0];
            dsky.Cell_Voltage[1] = (S_V[1] - S_V[0]);
            dsky.Cell_Voltage[2] = (S_V[2] - S_V[1]);
            dsky.Cell_Voltage[3] = (S_V[3] - S_V[2]);
        }

        //Calculate pack voltage. Why not just use S4 input? Because
        //S4 may not be used in smaller packs.
        float PackVolts=0;
        for(int i=0;i<sets.Cell_Count;i++){
            PackVolts+=dsky.Cell_Voltage[i];
        }
        dsky.pack_voltage=PackVolts;
        
        
        //Charger Voltage
        CavgVolt /= analog_const;
        if(CONDbits.V_Cal)dsky.Cin_voltage = CavgVolt / resistor_divide_const;    //Use resistor divider values to covert to actual voltage.
        else dsky.Cin_voltage = (CavgVolt / resistor_divide_const) + sets.Ch_vlt_adjst;
        CavgVolt = 0;       //Clear average.

        //Battery temperature.
        //avgBTemp /= x;      //Sample average.
        //avgBTemp /= 65535;  //Convert to unsigned fractional
        //avgBTemp *= 3.3;      //Converted to 0 - 5V voltage.
        //Do it all at once to save time.
        avgBTemp /= analog_const;
        avgBTemp -= 0.48;   //Offset for LM62 temp sensor.
        dsky.battery_temp = avgBTemp / 0.0156;    //Convert to Degrees C
        avgBTemp = 0;       //Clear average.


        //Snowman's temperature.
        //avgSTemp /= x;      //Sample average.
        //avgSTemp /= 65535;  //Convert to unsigned fractional
        //avgSTemp *= 3.3;      //Converted to 0 - 5V voltage.
        //Do it all at once to save time.
        avgSTemp /= analog_const;
        avgSTemp -= 0.48;   //Offset for LM62 temp sensor.
        dsky.my_temp = avgSTemp / 0.0156;    //Convert to Degrees C
        avgSTemp = 0;       //Clear average.
        STINGbits.adc_valid_data = 1;
}

//Voltage calibration routine
//Gets run by command only.
inline void Volt_Cal(int serial_port){
    Batt_IO_OFF();
    int RL_Temp = Run_Level;
    Run_Level = Cal_Mode;
    CONDbits.V_Cal = 1;
    //Wait here until analog inputs are ready.
    STINGbits.adc_sample_burn = 0;
    STINGbits.adc_valid_data = 0;//Get fresh analog data
    ADCON1bits.ADON = on;    // turn ADC on to get a sample.
    avg_rdy=0;
    while(avg_rdy<2){
        Idle();
    }
    int param = Get_Float(2, serial_port) - 1;
    float tollarance = param + 2;
    float set_Volt = Get_Float(4, serial_port);
    char anyCal=0;
    load_string("Checking: ",serial_port);
    load_float(param+1, serial_port);
    load_string("\n\r", serial_port);
    if(param>=0 && param<=3){
        //float Fi = i;
        //float testV = 2*(Fi+1);  //Calculate a test value. 2V for S1, S2, S3, and S4.
        //Calibrate the voltage only if it's within +-1V. We may be doing one at a time.
        if((Cell_Voltage_Average[param]>set_Volt-tollarance) && (Cell_Voltage_Average[param]<set_Volt+tollarance)){
            sets.S_vlt_adjst[param] = set_Volt-Cell_Voltage_Average[param];
            if(param==0)load_string("S1: ", serial_port);
            else if(param==1)load_string("S2: ", serial_port);
            else if(param==2)load_string("S3: ", serial_port);
            else if(param==3)load_string("S4: ", serial_port);
            anyCal = 1;
        }
    }
    //Now do charger input voltage
    if(param==4 && (dsky.Cin_voltage>set_Volt-2) && (dsky.Cin_voltage<set_Volt+2)){
            sets.Ch_vlt_adjst = set_Volt-dsky.Cin_voltage;
            load_string("CH: ", serial_port);
            anyCal = 1;
    }
    save_sets();
    if(Run_Level != Crit_Err)Run_Level = RL_Temp; //Return back to whatever run level we were in before.
    CONDbits.V_Cal = 0;
    if(anyCal)send_string("voltage input(s) cal.\n\r", serial_port);
    else if(param>=0 || param<=4) send_string("Nothing cal! Voltage out of range.\n\r", serial_port);
    else send_string("Nothing cal! Input number out of range. \n\r", serial_port);
}
//Gets ran by analog IRQ in sysIRQs.cBatt_IO_OFF();
//Runs on every 8th IRQ.
inline void IsSysReady(void){
        if(STINGbits.adc_sample_burn && !STINGbits.deep_sleep && !STINGbits.fault_shutdown){
            //do heater calibration
            if(vars.heat_cal_stage != disabled)heater_calibration();
            //Do power regulation and heater control.
            if((vars.heat_cal_stage > calibrating || !vars.heat_cal_stage) && Run_Level == All_Sys_Go && first_cal == fCalReady){
                outputReg();    //Output regulation routine
                chargeReg();    //Charge input regulation routine
                //Check for fault shutdown.
                //If there was a fault, shut everything down as fast as possible.
                //This seems redundant, but it isn't.
                //Shuts down a detected fault just after the regulation routine.
                if(STINGbits.fault_shutdown)Batt_IO_OFF();
                else {
                    //Clamp outputs to within PWM ranges.
                    if(heat_power<0)heat_power=0;
                    else if(heat_power>PWM_MaxHeat)heat_power=PWM_MaxHeat;
                    
                    if(ch_boost_power<0)ch_boost_power=0;
                    else if(ch_boost_power>PWM_MaxBoost_HN)ch_boost_power=PWM_MaxBoost_HN;
                    
                    if(charge_power<0)charge_power=0;
                    else if(charge_power>PWM_MaxChrg)charge_power=PWM_MaxChrg;
                    
                    //Set the PWM output to what the variables are during normal operation.
                    Heat_CTRL = heat_power;               //set heater control
                    CHctrl = charge_power;             //set charge control
                    CH_Boost = ch_boost_power;         //set charge boost control
                }
            }
            else if (!Run_Level <= Heartbeat)Batt_IO_OFF();
        }
        else Batt_IO_OFF();
}

//System power off for power saving.
inline void Deep_Sleep(void){
    LED_Mult(off);      //Make sure LEDs get turned off.
    for(int i=0;i<4;i++)vars.voltage_percentage_old[i] = voltage_percentage[i];    //Save a copy of voltage percentage before we shut down.
    save_vars();      //Save variables before power off.
    dsky.Cin_voltage=0; //Cheating but okay.
    USB_Power_Present_Check();  //Make sure IO lines get pulled low.
    KeepAlive = 0; //Disable Keep Alive signal.
}

//Get absolute value of a variable
inline float absFloat(float number){
    if(number < 0){
        number *= -1;
        return number;
    }
    else return number;
}

float simpleCube(float NumInput){
    return NumInput*NumInput*NumInput;
}

//Gets called from initialCal routine in sysChecks.c
void CapacityCalc(void){
//Use lowest cell.
    int lowestCell = 0;
    float previousCell = 100;
    for(int i=0;i<sets.Cell_Count;i++){
        if(voltage_percentage[i]<previousCell){
            lowestCell = i;
            previousCell=voltage_percentage[i];
        }
    }
    if(voltage_percentage[lowestCell]>100)voltage_percentage[lowestCell]=100;
    else if(voltage_percentage[lowestCell]<0)voltage_percentage[lowestCell]=0;
    vars.battery_remaining = vars.battery_capacity * (voltage_percentage[lowestCell] / 100);   //Rough estimation of how much power is left.
}

//Battery SOC Percentage Calculation. y=2(X-0.5)^3+0.5(X-0.5)+0.5 <- Equation used as an approximate SOC
//Gets called by analog IRQ in file sysIRQs.c
inline void open_volt_percent(void){
    //Use open circuit voltage only.
    if (absFloat(dsky.battery_current) < 0.05 && STINGbits.adc_sample_burn && !CONDbits.got_open_voltage){
        dsky.open_voltage = dsky.pack_voltage;
        float VoltsFromDead = sets.battery_rated_voltage - sets.dischrg_voltage;
        if(VoltsFromDead==0)VoltsFromDead=1;    //Prevent divide by zero.
        for(int i=0;i<sets.Cell_Count;i++){
            float NX = dsky.Cell_Voltage[i] - sets.dischrg_voltage;
            if(NX<0)NX=0;
            float BX = (NX / VoltsFromDead);
            voltage_percentage[i] = 100 * ((2*simpleCube(BX-0.5))+(0.5*(BX-0.5))+0.5); //Battery SOC curve approximation.
        }
        CONDbits.got_open_voltage = set;
    }
}

//Find current compensation value.
//Gets called at the end of 0.125s IRQ's average current routine in file sysIRQs.c
inline void current_cal(void){
    //do the current cal.
    if(Bcurnt_cal_stage == 2){
        Bcurrent_compensate = dsky.battery_crnt_average * -1;
        Ccurrent_compensate = CavgCurnt * -1;
        Bcurnt_cal_stage = 3;        //Current Cal Complete
        //Do a heater cal after we have done current cal unless it is disabled.
        if(vars.heat_cal_stage != disabled) vars.heat_cal_stage = initialize;
        //Done with current cal.
    }
    //Initialize current cal.
    if(Bcurnt_cal_stage == 1){
        Bcurrent_compensate = 0;
        Batt_IO_OFF();    //Turn off all inputs and outputs.
        Bcurnt_cal_stage = 2;
    }
}

int PORTS_DONE(void){
    if(!U2STAbits.RIDLE ||
            !U1STAbits.RIDLE ||
            !U2STAbits.TRMT ||
            !U1STAbits.TRMT ||
            U2STAbits.URXDA ||
            U1STAbits.URXDA) return no;
    else return yes;
}
void OSC_Switch(int speed){
    int new_Clock = 0;
    if(!CONDbits.slowINHIBIT && !slowINHIBIT_Timer && !CONDbits.charger_detected &&
    speed == slow && CONDbits.clockSpeed == fast && PORTS_DONE()){
        __asm__ volatile ("DISI #0x3FFF");
        __builtin_write_OSCCONH(0x78);
        __builtin_write_OSCCONH(0x9A);
        __builtin_write_OSCCONH(0x07);
        __builtin_write_OSCCONL(0x46);
        __builtin_write_OSCCONL(0x57);
        __builtin_write_OSCCONL(0x81); //Postscale 64
        CONDbits.clockSpeed = slow;
        new_Clock = 1;
            T1CONbits.TCKPS = 0x02;           //1:64 prescale HS is 1:256
            PR1 = 0x383A;                     //1/4 Count for a total scale down of 1:64
            TMR1 = 0x0000;
            
            T2CONbits.TCKPS = 0x01;           //1:1 prescale HS is 1:64
            PR2 = 0x7074;                     //Double count
            TMR2 = 0x0000;
            
            //T3CONbits.TCKPS = 0x02;           //1:64 prescale HS is 1:256
            //TMR3 = 0x0000;
            //PR3 = 0x383A;                     //1/4 Count for a total scale down of 1:64
            
            T4CONbits.TCKPS = 0x02;           //1:64 prescale HS is 1:256
            TMR4 = 0x0000;
            PR4 = 0x383A;                     //1/4 Count for a total scale down of 1:64
            
            T5CONbits.TCKPS = 0x01;           //1:1 prescale HS is 1:64
            PR5 = 0x7074;                     //Double count
            TMR5 = 0x0000;
    }
    else if(speed == fast && CONDbits.clockSpeed == slow){
        CONDbits.clockSpeed = fast;
        __asm__ volatile ("DISI #0x3FFF");
        T1CONbits.TCKPS = 0x03;          //1:256 prescale
        PR1 = 0xE0EA;                    //Full Count
        T2CONbits.TCKPS = 0x02;          //1:64 prescale
        PR2 = 0x383A;
        //T3CONbits.TCKPS = 3;             //1:256 prescale
        //PR3 = 0xE0EA;                    //Half Count
        T4CONbits.TCKPS = 0x03;          //1:256 prescale
        PR4 = 0xE0EA;                    //Half Count
        T5CONbits.TCKPS = 0x02;          //1:64 prescale
        PR5 = 0x383A;
        __builtin_write_OSCCONH(0x78);
        __builtin_write_OSCCONH(0x9A);
        __builtin_write_OSCCONH(0x07);
        __builtin_write_OSCCONL(0x46);
        __builtin_write_OSCCONL(0x57);
        __builtin_write_OSCCONL(0x01); //No postscale
        new_Clock = 1;
    }
    if(new_Clock){
        while(OSCCONbits.OSWEN){
        __asm__ volatile ("NOP");
        __asm__ volatile ("NOP");
        } //Wait for clock switch to finish.
        if(CONDbits.IRQ_RESTART)DISICNT = 0;
    }
}

#endif
