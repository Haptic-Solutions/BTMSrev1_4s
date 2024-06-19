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

#ifndef SysCalc_C
#define SysCalc_C

#include "SysCalculations.h"
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
        input_BavgCurnt /= sample_Average;      //Sample average.
        input_BavgCurnt -= 32768;    //Set zero point.
        input_BavgCurnt /= 32768;    //Convert to signed fractional. -1 to 1
        input_BavgCurnt *= Half_ref;      //Convert to +-1.65 'volts'. It's still a 0 - 3.3 volt signal on the analog input. The zero point is at 1.65v
        dsky.battery_current = (input_BavgCurnt * 12.5) + Bcurrent_compensate; //Offset for ACS711ELCTR-25AB-T Current Sensor.
        input_BavgCurnt = 0;       //Clear average.
        
        //Charger current.
        input_CavgCurnt /= sample_Average;      //Sample average.
        input_CavgCurnt -= 32768;    //Set zero point.
        input_CavgCurnt /= 32768;    //Convert to signed fractional. -1 to 1
        input_CavgCurnt *= Half_ref;      //Convert to +-1.65 'volts'. It's still a 0 - 3.3 volt signal on the analog input. The zero point is at 1.65v
        dsky.Cin_current = (input_CavgCurnt * 12.5) + Ccurrent_compensate; //Offset for ACS711ELCTR-25AB-T Current Sensor.
        input_CavgCurnt = 0;       //Clear average.

        //Battery voltage.
        //avgVolt /= 8;      //Sample average.
        //avgVolt /= 65535;  //Convert to unsigned fractional
        //avgVolt *= 3.3;      //Converted to 0 - 3.3V voltage.
        //analog_cost = (8*65535)/3.3
        //Do it all at once to save time.
        float S_V[Max_Cell_Count];
        for(int i=0;i<Max_Cell_Count;i++){
            input_BavgVolt[i] /= analog_const;
            if(CONDbits.V_Cal) S_V[i] = input_BavgVolt[i] / resistor_divide_const;
            else S_V[i] = (input_BavgVolt[i] / resistor_divide_const) + sets.S_vlt_adjst[i];    //Use resistor divider values to covert to actual voltage.
            input_BavgVolt[i] = 0;       //Clear average.
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
        input_CavgVolt /= analog_const;
        if(CONDbits.V_Cal)dsky.Cin_voltage = input_CavgVolt / resistor_divide_const;    //Use resistor divider values to covert to actual voltage.
        else dsky.Cin_voltage = (input_CavgVolt / resistor_divide_const) + sets.Ch_vlt_adjst;
        input_CavgVolt = 0;       //Clear average.

        //Snowman's temperature.
        //avgSTemp /= x;      //Sample average.
        //avgSTemp /= 65535;  //Convert to unsigned fractional
        //avgSTemp *= 3.3;      //Converted to 0 - 3.3V voltage.
        //Do it all at once to save time.
        input_avgSTemp /= analog_const;
        input_avgSTemp -= 0.48;   //Offset for LM62 temp sensor.
        dsky.my_temp = input_avgSTemp / 0.0156;    //Convert to Degrees C
        input_avgSTemp = 0;       //Clear average.
        STINGbits.adc_valid_data = 1;
        
        //Battery temperature.
        //avgBTemp /= x;      //Sample average.
        //avgBTemp /= 65535;  //Convert to unsigned fractional
        //avgBTemp *= 3.3;      //Converted to 0 - 3.3V voltage.
        //Do it all at once to save time.
        input_avgBTemp /= analog_const;     //Convert to 0 - 3.3v
        //Now find resistance from ohms law. R1 is 10K and R2 is NTC/PTC
        input_avgBTemp = input_avgBTemp/((3.3-input_avgBTemp)/10);
        //Now find deviation % from NTC/PTC at 25C
        input_avgBTemp = ((input_avgBTemp/sets.res_at_25)-1)*100;
        //Now find deg deviation from 25C based on coefficient
        input_avgBTemp = input_avgBTemp/sets.temp_coefficient;
        //Now add deg deviation to 25C
        //Check if we actually have a sensor connected. If not then use board temperature in place of battery temperature.
        Btemp_sensor_chk();
        if(STINGbits.No_Batt_TSensor)dsky.battery_temp = dsky.my_temp;
        else dsky.battery_temp = input_avgBTemp+25;    //Convert to Degrees C
        input_avgBTemp = 0;       //Clear average.
}

//Voltage calibration routine
//Gets run by command only.
void Volt_Cal(int serial_port){
    Batt_IO_OFF();
    int RL_Temp = Run_Level;
    Run_Level = Cal_Mode;
    CONDbits.V_Cal = 1;
    //Wait here until analog inputs are ready.
    STINGbits.adc_sample_burn = 0;
    STINGbits.adc_valid_data = 0;//Get fresh analog data
    ADCON1bits.ADON = on;    // turn ADC on to get a sample.
    avg_rdy=0;  //reset the averaging system.
    while(avg_rdy<1){
        Idle();
    }
    int param = Get_Float(2, serial_port) - 1;
    float tollarance = param + 2;
    float set_Volt = Get_Float(4, serial_port);
    char anyCal=0;
    load_string(I_Auto, "Checking: ",serial_port);
    load_float(I_Auto, param+1, serial_port);
    load_string(I_Auto, "\n\r", serial_port);
    if(param>=0 && param<=3){
        //float Fi = i;
        //float testV = 2*(Fi+1);  //Calculate a test value. 2V for S1, S2, S3, and S4.
        //Calibrate the voltage only if it's within +-1V. We may be doing one at a time.
        if((Cell_Voltage_Average[param]>set_Volt-tollarance) && (Cell_Voltage_Average[param]<set_Volt+tollarance)){
            sets.S_vlt_adjst[param] = set_Volt-Cell_Voltage_Average[param];
            if(param==0)load_string(I_Auto, "S1: ", serial_port);
            else if(param==1)load_string(I_Auto, "S2: ", serial_port);
            else if(param==2)load_string(I_Auto, "S3: ", serial_port);
            else if(param==3)load_string(I_Auto, "S4: ", serial_port);
            anyCal = 1;
        }
    }
    //Now do charger input voltage
    if(param==4 && (dsky.Cin_voltage>set_Volt-2) && (dsky.Cin_voltage<set_Volt+2)){
            sets.Ch_vlt_adjst = set_Volt-dsky.Cin_voltage;
            load_string(I_Auto, "CH: ", serial_port);
            anyCal = 1;
    }
    save_sets();
    if(Run_Level != Crit_Err)Run_Level = RL_Temp; //Return back to whatever run level we were in before.
    CONDbits.V_Cal = 0;
    if(anyCal)send_string(I_Auto, "voltage input(s) cal.\n\r", serial_port);
    else if(param>=0 || param<=4) send_string(I_Auto, "Nothing cal! Voltage out of range.\n\r", serial_port);
    else send_string(I_Auto, "Nothing cal! Input number out of range. \n\r", serial_port);
}
//Gets ran by analog IRQ in sysIRQs.cBatt_IO_OFF();
//Runs on every 8th IRQ.
void IsSysReady(void){
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
void Deep_Sleep(void){
    LED_Mult(off);      //Make sure LEDs get turned off.
    save_vars();      //Save variables before power off.
    dsky.Cin_voltage=0; //Cheating but okay.
    USB_Power_Present_Check();  //Make sure IO lines get pulled low.
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

float simpleCube(float NumInput){
    return NumInput*NumInput*NumInput;
}

//Battery SOC Curve Calculation. y=2(X-0.5)^3+0.5(X-0.5)+0.5 <- Equation used as an approximate SOC
//V_ratio is a 0-1 value based on discharge to charge voltages of cell type. Function returns a 0-1 value;
float Vcurve_calc(float V_level){
    return (2*simpleCube(V_level-0.5))+(0.5*(V_level-0.5))+0.5;
}
void get_volt_percent(void){
    dsky.open_voltage = dsky.pack_vltg_average;
    float VoltsFromDead = sets.cell_rated_voltage - sets.dischrg_voltage;
    if(VoltsFromDead==0)VoltsFromDead=0.00001;    //Prevent divide by zero.
    for(int i=0;i<sets.Cell_Count;i++){
        float V_level = Cell_Voltage_Average[i] - sets.dischrg_voltage;
        if(V_level<0)V_level=0;
        V_level /= VoltsFromDead;
        open_voltage_percentage[i] = 100 * Vcurve_calc(V_level);
    }
}

void Get_lowest_cell_percent(void){
    //Use lowest cell.
    int lowestCell = 0;
    float previousCell = 200;
    for(int i=0;i<sets.Cell_Count;i++){
        if(open_voltage_percentage[i]<previousCell){
            lowestCell = i; 
            previousCell=open_voltage_percentage[i];
        }
    }
    float ovp_temp = vars.battery_capacity * (open_voltage_percentage[lowestCell] / 100);   //Rough estimation of how much power is left based on voltage.
    //If open circuit voltage calculation would cause the battery remaining to be higher than what was last recorded, don't use it.
    if(ovp_temp<vars.battery_remaining)vars.battery_remaining = ovp_temp;
    else if(ovp_temp<0)vars.battery_remaining=0;
}

//Find current compensation value.
//Gets called at the end of 0.125s IRQ's average current routine in file sysIRQs.c
void initial_comp(void){
    //do the current cal.
    if(curnt_cal_stage == 2 && avg_rdy > 0){
        Bcurrent_compensate = (dsky.battery_crnt_average * -1)-0.015;   //Account for circuit draw when on.
        Ccurrent_compensate = ch_crnt_avg * -1;
        curnt_cal_stage = 3;        //Current Cal Complete
        //Do a heater cal after we have done current cal unless it is disabled.
        if(vars.heat_cal_stage != disabled) vars.heat_cal_stage = initialize;
        //Done with current cal.
        //Do pack charge state estimation.
        get_volt_percent();
        Get_lowest_cell_percent();
    }
    //Initialize current cal.
    if(curnt_cal_stage == 1){
        Bcurrent_compensate = 0;
        Ccurrent_compensate = 0;
        Batt_IO_OFF();    //Turn off all inputs and outputs.
        curnt_cal_stage = 2;
    }
}


#endif
