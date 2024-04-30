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

#ifndef REGULATE_C
#define REGULATE_C

#include "regulate.h"
#include "common.h"
#include "Init.h"

char Cell_HV_Check(){
    for(int i=0;i<Cell_Count;i++){
        if(dsky.Cell_Voltage[i]>=dsky.chrg_voltage) return 1;
    }
    return 0;
}

float Temperature_I_Calc(float lowTCutout, float lowBeginReduce, float highTCutout, float highBeginReduce){
    if(dsky.battery_temp < lowBeginReduce) percentOut = (dsky.battery_temp - lowTCutout) / (lowBeginReduce - lowTCutout);
    else if (dsky.battery_temp > highBeginReduce) percentOut = 1 + (-1 * (dsky.battery_temp - highTCutout) / (highBeginReduce - highTCutout));
    else return 1;
    //Clamp the result 0 - 1
    if(percentOut > 1) return 1;
    else if (percentOut < 0) return 0;
    else return percentOut;
}

inline void temperatureCalc(void){
    //Calculate max discharge current based off battery temp and battery remaining.
    dischrg_current = (sets.dischrg_C_rating * vars.battery_remaining)
    * Temperature_I_Calc(sets.dischrg_min_temp, sets.dischrg_reduce_low_temp, sets.dischrg_max_temp, sets.dischrg_reduce_high_temp);
    if(dischrg_current < sets.limp_current) dischrg_current = sets.limp_current;
    //Calculate max charge current based off battery temp and battery remaining.
    chrg_remaining = (vars.battery_capacity - vars.battery_remaining);
    if(chrg_remaining < 0.2) chrg_remaining = 0.2;  //Minimum charge current is 0.2 * charge C rating.
    chrg_current = (sets.chrg_C_rating * chrg_remaining)
    * Temperature_I_Calc(sets.chrg_min_temp, sets.chrg_reduce_low_temp, sets.chrg_max_temp, sets.chrg_reduce_high_temp);
}

inline void outputReg(void){
    ////Check for key power or command power signal, but not soft power signal.
    if((CONDbits.Power_Out_EN && Run_Level != Cal_Mode)){
        //Run heater if needed, but don't run this sub a second time if we are getting charge power while key is on.
        //If we are getting charge power then we need to use it to warm the battery to a higher temp if needed.
        //So check charge input first.
        if(!STINGbits.CH_Voltage_Present){
            heat_control(sets.dischrg_target_temp);
        }
        dsky.max_current = dischrg_current;
        if(precharge_timer==PreChargeTime)PowerOutEnable = on;

            
    }
    else{
        PowerOutEnable = off;
        precharge_timer = 0;
    }
}

inline void chargeReg(void){
    //Charge current read and target calculation.
    //// Check for Charger.
    if(STINGbits.CH_Voltage_Present && CONDbits.charger_detected && Run_Level != Cal_Mode){
        //Check to see if anything has happened with our USB_3 charging. && !V_Bus_Stat
        if((charge_mode >= USB3_Wimp && charge_mode <= USB3_Fast)){
            STINGbits.CH_Voltage_Present=0;
            charge_mode = Stop;
        }
        //Check to see if something has changed or was unplugged.
        if(charge_mode > Assignment_Ready && charge_mode != Solar && dsky.Cin_voltage<Charger_Target_Voltage-1){
            STINGbits.CH_Voltage_Present=0;
            charge_mode = Stop;
        }
        //Check for charge input overvoltage
        if(dsky.Cin_voltage>26){
            STINGbits.CH_Voltage_Present=0;
            charge_mode = Stop;
            fault_log(0x38);
            ALL_shutdown();
        }
        //Run heater if needed, but don't turn it up more than what the charger can handle.
        //This way we don't discharge the battery from trying to run the heater while the charger is plugged in, but
        //not supplying enough current to do both.
        if(dsky.battery_current >= 0.02) heat_control(sets.chrg_target_temp);
        else if(dsky.battery_current < 0 && heat_power > 0) heat_power--;

        //Regulate the charger input.
        // Charge regulation routine.
        if(charge_power > 0 && (dsky.battery_current > chrg_current || Cell_HV_Check() || dsky.Cin_current > Max_Charger_Current || dsky.Cin_voltage < Charger_Target_Voltage - 0.05)){
            if(ch_boost_power > 0)ch_boost_power-=2;
            else charge_power-=2;
        }
        else if(ch_boost_power < PWM_MaxBoost && (dsky.battery_current < chrg_current && !Cell_HV_Check() && dsky.Cin_current < Max_Charger_Current && dsky.Cin_voltage > Charger_Target_Voltage + 0.05)){
            if(charge_power < PWM_MaxChrg)charge_power+=2;
            else ch_boost_power+=2;
        }
    }
    else{
        charge_power = off;
        ch_boost_power = off;
        CH_Boost = off;
        CHctrl = off;
    }
}

//Heater regulation.
inline void heat_control(float target_temp){
    /* Heater regulation. Ramp the heater up or down. If the battery temp is out
     * of range then the target charge or discharge current will be set to 0 and the charge
     * regulation routine will power the heater without charging the battery.
     */
    if(vars.heat_cal_stage == ready){
        if(dsky.battery_temp < (target_temp - 0.5) && heat_power < heat_set)heat_power++;
        else if(dsky.battery_temp > (target_temp + 0.5)){
            if(heat_power > 0)heat_power--;
        }
    }
}

#endif
