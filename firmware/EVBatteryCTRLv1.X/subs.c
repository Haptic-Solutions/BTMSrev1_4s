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
        float S_V[4];
        for(int i=0;i<4;i++){
            BavgVolt[i] /= analog_const;
            if(CONDbits.V_Cal) S_V[i] = BavgVolt[i] / resistor_divide_const;
            else S_V[i] = (BavgVolt[i] / resistor_divide_const) + sets.S_vlt_adjst[i];    //Use resistor divider values to covert to actual voltage.
        }
        
        if(CONDbits.V_Cal){
            for(int i=0;i<4;i++)dsky.Cell_Voltage[i] = S_V[i];
        }
        else {
            dsky.Cell_Voltage[0] = 0.05 + S_V[0]; //Safer to have the voltages read a little high than a little low.
            dsky.Cell_Voltage[1] = 0.05 + (S_V[1] - S_V[0]);
            dsky.Cell_Voltage[2] = 0.05 + (S_V[2] - S_V[1]);
            dsky.Cell_Voltage[3] = 0.05 + (S_V[3] - S_V[2]);
        }
        
        for(int i=0;i<4;i++){
            BavgVolt[i] = 0;       //Clear average.
        }
        //Calculate pack voltage. Why not just use S4 input? Because
        //S4 may not be used in smaller packs.
        //Recalculating based on calibrated and calculated values should
        //reduce that error amount.
        float PackVolts=0;
        for(int i=0;i<Cell_Count;i++){
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
    while(!STINGbits.adc_valid_data || !STINGbits.adc_sample_burn){
        Idle();
    }
    char anyCal=0;
    for(int i=0;i<4;i++){
        //float Fi = i;
        //float testV = 2*(Fi+1);  //Calculate a test value. 2V for S1, S2, S3, and S4.
        //Calibrate the voltage only if it's within +-1V. We may be doing one at a time.
        if((dsky.Cell_Voltage[i]>1) && (dsky.Cell_Voltage[i]<3)){
            sets.S_vlt_adjst[i] = 2-dsky.Cell_Voltage[i];
            if(i==0)load_string("S1: ", serial_port);
            if(i==1)load_string("S2: ", serial_port);
            if(i==2)load_string("S3: ", serial_port);
            if(i==3)load_string("S4: ", serial_port);
            anyCal = 1;
        }
    }
    //Now do charger input voltage
    if((dsky.Cin_voltage>4.0) && (dsky.Cin_voltage<6.0)){
            sets.Ch_vlt_adjst = 5-dsky.Cin_voltage;
            load_string("CH: ", serial_port);
            anyCal = 1;
    }
    save_sets();
    if(Run_Level != Crit_Err)Run_Level = RL_Temp; //Return back to whatever run level we were in before.
    CONDbits.V_Cal = 0;
    if(anyCal)send_string("voltage input(s) cal.\n\r", serial_port);
    else send_string("Nothing cal! Voltages out of range.\n\r", serial_port);
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

    // Enough time should have passed by now that the open circuit voltage should be stabilized enough to get an accurate reading.
    save_vars();      //Save variables before power off.
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
    for(int i=0;i<Cell_Count;i++){
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
    if (absFloat(dsky.battery_current) < 0.05 && STINGbits.adc_sample_burn){
        dsky.open_voltage = dsky.pack_voltage;
        float VoltsFromDead = sets.battery_rated_voltage - sets.dischrg_voltage;
        for(int i=0;i<Cell_Count;i++){
            float NX = dsky.Cell_Voltage[i] - sets.dischrg_voltage;
            if(NX<0)NX=0;
            float BX = (NX / VoltsFromDead);
            voltage_percentage[i] = 100 * ((2*simpleCube(BX-0.5))+(0.5*(BX-0.5))+0.5); //Battery SOC curve approximation.
        }
        CONDbits.got_open_voltage = yes;
    }
}

//Find current compensation value.
//Gets called at the end of 0.125s IRQ's average current routine in file sysIRQs.c
inline void current_cal(void){
    //do the current cal.
    if(Bcurnt_cal_stage == 2){
        Bcurrent_compensate = dsky.battery_crnt_average * -1;
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

#endif
