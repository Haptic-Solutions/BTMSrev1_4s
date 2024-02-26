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

void temperatureCalc(void){
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

void outputReg(void){
    ////Check for key power or command power signal, but not soft power signal.
    if((CONDbits.cmd_power)){
        //Run heater if needed, but don't run this sub a second time if we are getting charge power while key is on.
        //If we are getting charge power then we need to use it to warm the battery to a higher temp if needed.
        //So check charge input first.
        if(!STINGbits.charge_GO){
            heat_control(sets.dischrg_target_temp);
        }
        dsky.max_current = dischrg_current;
        PreCharge = on;
        if(precharge_timer==PreChargeTime)PowerOutEnable = on;

            
    }
    else{
        PreCharge = off;
        PowerOutEnable = off;
        precharge_timer = 0;
    }
}

void chargeReg(void){
    //Charge current read and target calculation.
    //// Check for Charger.
    if(STINGbits.charge_GO){
        //Check to see if anything has happened with our USB_3 charging.
        if((charge_mode >= USB3_Wimp && charge_mode <= USB3_Fast) && !V_Bus_Stat){
            STINGbits.charge_GO=0;
            charge_mode = Stop;
        }
        //Check to see if something has changed or was unplugged.
        if(charge_mode > Ready && charge_mode != Solar && dsky.Cin_voltage<Charger_Target_Voltage-0.2){
            STINGbits.charge_GO=0;
            charge_mode = Stop;
        }
        //Check for charge input overvoltage
        if(dsky.Cin_voltage>26){
            STINGbits.charge_GO=0;
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
        if(charge_power > 0 && (
        dsky.battery_current > chrg_current ||
        Cell_HV_Check() ||
        dsky.Cin_voltage > Charger_Target_Voltage ||
        dsky.Cin_current > Max_Charger_Current)){
            if(ch_boost_power > 0)ch_boost_power--;
            else charge_power--;
        }
        else if(ch_boost_power < 50 && (
        dsky.battery_current < chrg_current ||
        !Cell_HV_Check() ||
        dsky.Cin_voltage < Charger_Target_Voltage ||
        dsky.Cin_current < Max_Charger_Current)){
            if(charge_power < 100)charge_power++;
            else ch_boost_power++;
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
void heat_control(float target_temp){
    /* Heater regulation. Ramp the heater up or down. If the battery temp is out
     * of range then the target charge or discharge current will be set to 0 and the charge
     * regulation routine will power the heater without charging the battery.
     */
    if(vars.heat_cal_stage == ready){
        if(dsky.battery_temp < (target_temp - 0.5) && heat_power < heat_set){
            if(heat_rly_timer == 0)heat_power++;
            PowerOutEnable = on;     //Heat Relay On
            if(heat_rly_timer == 3)heat_rly_timer = 2; //wait two 0.125ms cycles before allowing heat regulation to start.
        }
        else if(dsky.battery_temp > (target_temp + 0.5)){
            if(heat_power > 0)heat_power--;
            if(heat_power <= 0){
                PowerOutEnable = off;     //Heat Relay Off
                heat_rly_timer = 3;     //Reset heat relay timer
            }
        }
    }
}

#endif
