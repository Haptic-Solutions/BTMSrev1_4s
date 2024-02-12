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
    if((keySwitch || CONDbits.cmd_power)){
        //Turn cmd_power off if keySwitch is turned on then off.
        if(keySwitch)STINGbits.sw_off = on;
        else if (!keySwitch && STINGbits.sw_off){
            CONDbits.cmd_power = off;
            STINGbits.sw_off = off;
        }
        ctRelay = on;          //contactor relay on, but only if fault shutdown is 0
        AUXrelay = on;         //Turn on AUX
        if(contact_rly_timer == 3)
            contact_rly_timer = 2;         //wait two 0.125ms cycles before allowing charge regulation to start.

        //Run heater if needed, but don't run this sub a second time if we are getting charge power while key is on.
        //If we are getting charge power then we need to use it to warm the battery to a higher temp if needed.
        //So check charge input first.
        if(!chrgSwitch){
            heat_control(sets.dischrg_target_temp);
        }
        if(contact_rly_timer == 0){
            //Integral Mode
            //High temp limiting.
            voltage_output += analog_smpl_time * ((dsky.battery_temp - sets.dischrg_max_temp) * temp_proportion);
            if(voltage_output > sets.battery_rated_voltage){
                voltage_output = sets.battery_rated_voltage;
            }
            else if(voltage_output < sets.dischrg_voltage){
                voltage_output = sets.dischrg_voltage;
            }

            //Low voltage limiting.
            current_output += analog_smpl_time * ((dsky.battery_voltage - voltage_output) * vltg_proportion);
            if(current_output > dischrg_current){
                current_output = dischrg_current;
            }
            else if(current_output < 0){
                current_output = 0;
            }

            //Current regulation.
            crnt_error = (current_output - absFloat(dsky.battery_current)) * crnt_proportion;
            if(crnt_error > 10000){
                crnt_error = 10000;
            }
            else if(crnt_error < -10000){
                crnt_error = -10000;
            }
            crnt_integral += (analog_smpl_time * crnt_error);
            if(crnt_integral > 95){
                crnt_integral = 95;
            }
            else if(crnt_integral < 0){
                crnt_integral = 0;
            }
            output_power = crnt_integral;
        }
    }
    else{
        output_power = off;
        outPWM = off;             //set output control to 0 before turning off the relay
        LATE = off;               //Insure all PORTE outputs are off.
        PWMCON1bits.PEN3L = off;  //Set PWM3 Low side to standard output so that it can be set to 0
        crnt_integral = 0;
        contact_rly_timer = 3; //Reset contactor relay timer
        AUXrelay = off; //Turn off AUX
        ctRelay = off; //Turn off contactor relay
    }
}

void chargeReg(void){
    //Charge current read and target calculation.
    //// Check for Charger.
    if(chrgSwitch){
        chrgLight = 1;          //charger light on.
        chrgRelay = 1;          //charger relay on, but only if fault shutdown is 0
        if(chrg_rly_timer == 3)chrg_rly_timer = 2;         //wait two 0.125ms cycles before allowing charge regulation to start.
        //Charger timeout check. If charger is plugged in but we aren't getting current then we
        //need to shutdown and log an error code so we don't run down the battery.
        if(chrg_check < 10000 && dsky.battery_current < -0.01 && !keySwitch &&
        dsky.battery_voltage < (dsky.chrg_voltage - 0.05) && !heat_power) chrg_check++;
        else if(chrg_check >= 10000){
            fault_log(0x1B);            //Log insufficient current from charger.
            STINGbits.fault_shutdown = yes;
            chrg_check = clear;
            chrgRelay = off;          //charger relay off. Don't waste power on a relay that is doing nothing.
            //This usually happens when we detect a charge voltage but the charge regulator isn't passing enough current or it's voltage is below the battery's voltage.
        }
        else if(chrg_check > 0) chrg_check--;

        //Run heater if needed, but don't turn it up more than what the charger can handle.
        //This way we don't discharge the battery from trying to run the heater while the charger is plugged in, but
        //not supplying enough current to do both.
        if(dsky.battery_current >= 0.02) heat_control(sets.chrg_target_temp);
        else if(dsky.battery_current < 0 && heat_power > 0) heat_power--;

        //Regulate the charger input.
        if(!chrg_rly_timer){
            // Charge regulation routine. Clean this up, it needs to use integral math for regulation.
            if(((charge_power > 0) && (dsky.battery_voltage >= (dsky.chrg_voltage))) ||
            (dsky.battery_current > (chrg_current + 0.02)))charge_power--;
            else if(((charge_power < 101) && (dsky.battery_voltage < dsky.chrg_voltage - 0.07)) ||
            (dsky.battery_current < chrg_current))charge_power++;
        }
        else charge_power = 0;       //Inhibit charging if we are in the middle of heater calibration.
    }
    else{
        chrgLight = off;          //charger light off.
        charge_power = off;       //charger set to 0
        chrgPWM = off;            //Set charger output to 0 before turning off relay
        chrgRelay = off;          //charger relay off.
        chrg_rly_timer = 3;     //reset charge relay timer.
        chrg_check = clear;         //Reset charger check timer
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
            heatRelay = on;     //Heat Relay On
            if(heat_rly_timer == 3)heat_rly_timer = 2; //wait two 0.125ms cycles before allowing heat regulation to start.
        }
        else if(dsky.battery_temp > (target_temp + 0.5)){
            if(heat_power > 0)heat_power--;
            if(heat_power <= 0){
                heatRelay = off;     //Heat Relay Off
                heat_rly_timer = 3;     //Reset heat relay timer
            }
        }
    }
}

#endif
