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
        avgCurnt /= 8;      //Sample average.
        avgCurnt -= 32768;    //Set zero point.
        avgCurnt /= 32768;    //Convert to signed fractional. -1 to 1
        avgCurnt *= 2.5;      //Convert to +-2.5'volts'. It's still a 0 - 5 volt signal on the analog input. The zero point is at 2.5v
        dsky.battery_current = (avgCurnt / 0.04) + current_compensate; //Offset for ACS780LLRTR-050B-T Current Sensor.
        currentCheck();     //Check for over current condition.
        avgCurnt = 0;       //Clear average.

        //Battery voltage.
        //avgVolt /= x;      //Sample average.
        //avgVolt /= 65535;  //Convert to unsigned fractional
        //avgVolt *= 5;      //Converted to 0 - 5V voltage.
        //Do it all at once to save time.
        avgVolt /= 104856;   //(13107 * 8)Average and Convert to unsigned fractional, 0v - 5v
        dsky.battery_voltage = (avgVolt / vltg_dvid) + sets.bt_vlt_adjst;    //Use resistor divider values to covert to actual voltage.
        avgVolt = 0;       //Clear average.

        //Battery temperature.
        //avgBTemp /= x;      //Sample average.
        //avgBTemp /= 65535;  //Convert to unsigned fractional
        //avgBTemp *= 5;      //Converted to 0 - 5V voltage.
        //Do it all at once to save time.
        avgBTemp /= 104856;   //(13107 * 8)Average and Convert to unsigned fractional, 0v - 5v
        avgBTemp -= 0.48;   //Offset for LM62 temp sensor.
        dsky.battery_temp = avgBTemp / 0.0156;    //Convert to Degrees C
        avgBTemp = 0;       //Clear average.

        //motor controller temperature.
        //avgMTemp /= x;      //Sample average.
        //avgMTemp /= 65535;  //Convert to unsigned fractional
        //avgMTemp *= 5;      //Converted to 0 - 5V voltage.
        //Do it all at once to save time.
        avgMTemp /= 104856;   //(13107 * 8)Average and Convert to unsigned fractional, 0v - 5v
        avgMTemp -= 0.48;   //Offset for LM62 temp sensor.
        dsky.motor_ctrl_temp = avgMTemp / 0.0156;    //Convert to Degrees C
        avgMTemp = 0;       //Clear average.
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
                    PWMCON1bits.PEN3L = 1;  //Set PWM3 Low side to PWM output.
                    heatPWM = heat_power;               //set heater control
                    chrgPWM = charge_power;             //set charge control
                    outPWM = output_power;             //set output control
                }
            }
            else if (!CONDbits.main_power)io_off();
        }
        else io_off();
}

//System power off for power saving.
void power_off(void){
    vars.voltage_percentage_old = voltage_percentage;    //Save a copy of voltage percentage before we shut down.
    // Enough time should have passed by now that the open circuit voltage should be stabilized enough to get an accurate reading.
    save_vars();      //Save variables before power off.
    keepAlive = 0; //Disable Keep Alive signal.
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
        dsky.open_voltage = dsky.battery_voltage;
        voltage_percentage = 100 * ((dsky.open_voltage - sets.dischrg_voltage) / (sets.battery_rated_voltage - sets.dischrg_voltage));
        CONDbits.got_open_voltage = yes;
    }
    else if(dsky.battery_voltage <= (sets.dischrg_voltage + 0.05)){
        voltage_percentage = 0;
        dsky.open_voltage = sets.dischrg_voltage + 0.05;
        CONDbits.got_open_voltage = yes;
    }
}

//Find current compensation value.
void current_cal(void){
    float signswpd_avg_cnt = dsky.battery_crnt_average * -1;
    //do the current cal.
    if(curnt_cal_stage == 4){
        current_compensate = (signswpd_avg_cnt - sets.circuit_draw);
        curnt_cal_stage = 5;        //Current Cal Complete
        //Do a heater cal after we have done current cal unless it is disabled.
        if(vars.heat_cal_stage != disabled) vars.heat_cal_stage = initialize;
        CONDbits.soft_power = off;
        //Done with current cal.
    }
    //Initialize current cal.
    if(curnt_cal_stage == 1){
        current_compensate = 0;
        io_off();    //Turn off all inputs and outputs.
        curnt_cal_stage = 4;
        CONDbits.soft_power = on;         //Turn soft power on to run 0.125s IRQ.
    }
}

#endif
