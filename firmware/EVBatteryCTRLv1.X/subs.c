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
void calcAnalog(void){
    /* I have left commented out code in this section for showing the process
        * of converting analog inputs into voltages, currents, and temps.
        */
        //Battery current.
        BavgCurnt /= 8;      //Sample average.
        BavgCurnt -= 32768;    //Set zero point.
        BavgCurnt /= 32768;    //Convert to signed fractional. -1 to 1
        BavgCurnt *= 1.65;      //Convert to +-1.65 'volts'. It's still a 0 - 3.3 volt signal on the analog input. The zero point is at 1.65v
        dsky.battery_current = (BavgCurnt * 12.5) + Bcurrent_compensate; //Offset for ACS711ELCTR-25AB-T Current Sensor.
        currentCheck();     //Check for over current condition.
        BavgCurnt = 0;       //Clear average.
        
        //Charger current.
        CavgCurnt /= 8;      //Sample average.
        CavgCurnt -= 32768;    //Set zero point.
        CavgCurnt /= 32768;    //Convert to signed fractional. -1 to 1
        CavgCurnt *= 1.65;      //Convert to +-1.65 'volts'. It's still a 0 - 3.3 volt signal on the analog input. The zero point is at 1.65v
        dsky.Cin_current = (CavgCurnt * 12.5) + Ccurrent_compensate; //Offset for ACS711ELCTR-25AB-T Current Sensor.
        currentCheck();     //Check for over current condition.
        CavgCurnt = 0;       //Clear average.

        //Battery voltage.
        //avgVolt /= x;      //Sample average.
        //avgVolt /= 65535;  //Convert to unsigned fractional
        //avgVolt *= 5;      //Converted to 0 - 5V voltage.
        //Do it all at once to save time.
        BavgVolt[0] /= 104856;   //(13107 * 8)Average and Convert to unsigned fractional, 0v - 5v
        float S1_V = (BavgVolt[0] / vltg_dvid);    //Use resistor divider values to covert to actual voltage.
        BavgVolt[0] = 0;       //Clear average.

        BavgVolt[1] /= 104856;   //(13107 * 8)Average and Convert to unsigned fractional, 0v - 5v
        float S2_V = (BavgVolt[1] / vltg_dvid);    //Use resistor divider values to covert to actual voltage.
        BavgVolt[1] = 0;       //Clear average.
        
        BavgVolt[2] /= 104856;   //(13107 * 8)Average and Convert to unsigned fractional, 0v - 5v
        float S3_V = (BavgVolt[2] / vltg_dvid);    //Use resistor divider values to covert to actual voltage.
        BavgVolt[2] = 0;       //Clear average.
        
        BavgVolt[3] /= 104856;   //(13107 * 8)Average and Convert to unsigned fractional, 0v - 5v
        float S4_V = (BavgVolt[3] / vltg_dvid);    //Use resistor divider values to covert to actual voltage.
        BavgVolt[3] = 0;       //Clear average.
        
        dsky.Cell_Voltage[0] = (S4_V - (S3_V+S2_V+S1_V))+ sets.S1_vlt_adjst;
        dsky.Cell_Voltage[1] = (S3_V - (S2_V+S1_V))+ sets.S2_vlt_adjst;
        dsky.Cell_Voltage[2] = (S2_V - S1_V)+ sets.S3_vlt_adjst;
        dsky.Cell_Voltage[3] = (S1_V + sets.S4_vlt_adjst);
        
        //Calculate pack voltage. Why not just use S4 input? Because
        //S4 input includes all errors of the resistor dividers combined.
        //Recalculating based on calibrated and calculated values should
        //reduce that error amount.
        float PackVolts=0;
        for(int i=0;i<4;i++){
            PackVolts+=dsky.Cell_Voltage[i];
        }
        dsky.pack_voltage=PackVolts;
        //Charger Voltage
        CavgVolt /= 104856;   //(13107 * 8)Average and Convert to unsigned fractional, 0v - 5v
        dsky.Cin_voltage = (CavgVolt / vltg_dvid);    //Use resistor divider values to covert to actual voltage.
        CavgVolt = 0;       //Clear average.

        //Battery temperature.
        //avgBTemp /= x;      //Sample average.
        //avgBTemp /= 65535;  //Convert to unsigned fractional
        //avgBTemp *= 5;      //Converted to 0 - 5V voltage.
        //Do it all at once to save time.
        avgBTemp /= 104856;   //(13107 * 8)Average and Convert to unsigned fractional, 0v - 5v
        avgBTemp -= 0.48;   //Offset for LM62 temp sensor.
        dsky.battery_temp = avgBTemp / 0.0156;    //Convert to Degrees C
        avgBTemp = 0;       //Clear average.


        //Snowman's temperature.
        //avgSTemp /= x;      //Sample average.
        //avgSTemp /= 65535;  //Convert to unsigned fractional
        //avgSTemp *= 5;      //Converted to 0 - 5V voltage.
        //Do it all at once to save time.
        avgSTemp /= 104856;   //(13107 * 8)Average and Convert to unsigned fractional, 0v - 5v
        avgSTemp -= 0.48;   //Offset for LM62 temp sensor.
        dsky.my_temp = avgSTemp / 0.0156;    //Convert to Degrees C
        avgSTemp = 0;       //Clear average.
}
void sysReady(void){
        if(STINGbits.adc_sample_burn && !STINGbits.deep_sleep && !STINGbits.fault_shutdown){
            //do heater calibration
            if(vars.heat_cal_stage != disabled)heater_calibration();
            //Do power regulation and heater control.
            if((vars.heat_cal_stage > calibrating || !vars.heat_cal_stage) && CONDbits.main_power && first_cal == fCalReady){
                outputReg();    //Output regulation routine
                chargeReg();    //Charge input regulation routine
                //Check for fault shutdown.
                //If there was a fault, shut everything down as fast as possible.
                //This seems redundant, but it isn't.
                //Shuts down a detected fault just after the regulation routine.
                if(STINGbits.fault_shutdown)io_off();
                else {
                    //Set the PWM output to what the variables are during normal operation.
                    Heat_CTRL = heat_power;               //set heater control
                    CHctrl = charge_power;             //set charge control
                    CH_Boost = ch_boost_power;         //set charge boost control
                }
            }
            else if (!CONDbits.main_power)io_off();
        }
        else io_off();
}

//System power off for power saving.
void power_off(void){
    for(int i=0;i<4;i++)vars.voltage_percentage_old[i] = voltage_percentage[i];    //Save a copy of voltage percentage before we shut down.

    // Enough time should have passed by now that the open circuit voltage should be stabilized enough to get an accurate reading.
    save_vars();      //Save variables before power off.
    KeepAlive = 0; //Disable Keep Alive signal.
}

//Get absolute value of a variable
float absFloat(float number){
    if(number < 0){
        number *= -1;
        return number;
    }
    else return number;
}

//Battery Percentage Calculation. This does NOT calculate the % total charge of battery, only the total voltage percentage.
void volt_percent(void){
    if (absFloat(dsky.battery_current) < 0.08 && !CONDbits.charger_detected && STINGbits.adc_sample_burn){
        dsky.open_voltage = dsky.pack_voltage;
        for(int i=0;i<4;i++)voltage_percentage[i] = 100 * ((dsky.Cell_Voltage[i] - sets.dischrg_voltage) / (sets.battery_rated_voltage - sets.dischrg_voltage));

        CONDbits.got_open_voltage = yes;
    }
    else if(dsky.pack_voltage <= (sets.dischrg_voltage + 0.01)){
        for(int i=0;i<4;i++)voltage_percentage[i] = 0;
        dsky.open_voltage = (sets.dischrg_voltage*4) + 0.01;
        CONDbits.got_open_voltage = yes;
    }
}

//Find current compensation value.
void current_cal(void){
    float signswpd_avg_cnt = dsky.battery_crnt_average * -1;
    //do the current cal.
    if(Bcurnt_cal_stage == 4){
        Bcurrent_compensate = signswpd_avg_cnt;
        Bcurnt_cal_stage = 5;        //Current Cal Complete
        //Do a heater cal after we have done current cal unless it is disabled.
        if(vars.heat_cal_stage != disabled) vars.heat_cal_stage = initialize;
        CONDbits.soft_power = off;
        //Done with current cal.
    }
    //Initialize current cal.
    if(Bcurnt_cal_stage == 1){
        Bcurrent_compensate = 0;
        io_off();    //Turn off all inputs and outputs.
        Bcurnt_cal_stage = 4;
        CONDbits.soft_power = on;         //Turn soft power on to run 0.125s IRQ.
    }
}

#endif
