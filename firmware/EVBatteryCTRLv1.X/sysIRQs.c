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

#ifndef sysIRQS_C
#define sysIRQS_C

#include "IRQs.h"
#include "common.h"
#include "DataIO.h"
#include "Init.h"
#include "display.h"
#include "eeprom.h"
#include "checksum.h"
#include "sysChecks.h"
#include "regulate.h"


/* Batter OV fault IRQ. */
void __attribute__((interrupt, no_auto_psv)) _INT0Interrupt (void){
    //CPUact = 1;
    Batt_IO_OFF();
    STINGbits.fault_shutdown = 1;
    fault_log(0x3A);
    URFLAGbits.OverVLT_Fault = set;
    save_vars();
    IFS0bits.INT0IF = 0;
}

/* Current sensor Fault IRQ. */
void __attribute__((interrupt, no_auto_psv)) _INT1Interrupt (void){
    //CPUact = on;
    Batt_IO_OFF();
    STINGbits.fault_shutdown = 1;
    fault_log(0x39);
    save_vars();
    IFS1bits.INT1IF = clear;
}

/* Analog Input IRQ */
void __attribute__((interrupt, no_auto_psv)) _ADCInterrupt (void){
    //CPUact = on;
    //Get 8 samples for averaging.
    if (analog_avg_cnt < 8){
        //Force use of all 0's if we haven't burned the first ADC sample after a startup.
        //The ADC takes a moment to get correct values but it still sends the IRQs anyways.
        if (STINGbits.adc_sample_burn){
            CavgVolt += ChargeVoltage; //Charger Voltage
            BavgCurnt += BCsense; //Battery Current
            avgBTemp += Btemp; //Batt Temp
            avgSTemp += Mtemp; //Self Temp
            BavgVolt[0] += LithCell_V1;
            BavgVolt[1] += LithCell_V2;
            BavgVolt[2] += LithCell_V3;
            BavgVolt[3] += LithCell_V4;
            CavgCurnt += CCsense; //Charger Current
            //Check for sane values.
            analog_sanity();
        }
        else{
            //Burn the first average.
            CavgVolt = 0;
            BavgCurnt = 0;
            avgBTemp = 0;
            avgSTemp = 0;
            BavgVolt[0] = 0;
            BavgVolt[1] = 0;
            BavgVolt[2] = 0;
            BavgVolt[3] = 0;
            CavgCurnt = 0;
        }
        analog_avg_cnt++;
    }
    else {
        calcAnalog(); //Calculate analog inputs.
        //Get open circuit voltage percentage if current is less than 0.1 amps
        if(STINGbits.adc_sample_burn)volt_percent();
        //Reset analog average count.
        analog_avg_cnt = clear;
        //Do a battery check after each valid sample.
        //Check to make sure the battery and other systems are within safe operating conditions.
        //Shutdown and log the reason why if they aren't safe.
        if(STINGbits.adc_sample_burn && !STINGbits.fault_shutdown) explody_preventy_check();
        //Check to see if the system is ready to run.
        IsSysReady(); //If there is a fault, keep it from running.
        //ADC sample burn check. Only burn once when main power is on.
        if (CONDbits.Run_Level < Cal_Mode && STINGbits.adc_sample_burn == yes){
            ADCON1bits.ADON = off;                // turn ADC off to save power.
            STINGbits.adc_sample_burn = no;     //Burn the first ADC sample on every power up of ADC.
        }
        else STINGbits.adc_sample_burn = yes;      //We have burned the first set.
        //Run the LED routine
        LED_Mult(on);
    }
    //End IRQ
    IFS0bits.ADIF = 0;
}

/* Heartbeat IRQ, Once every Second. Lots of stuff goes on here. */
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt (void){
    //CPUact = on;
    ADCON1bits.ADON = on;    // turn ADC on to get a sample.
    //Check for how fast we are charging.
    if(dsky.battery_crnt_average > (sets.chrg_C_rating*sets.amp_hour_rating)*0.75)CONDbits.fastCharge = 1;
    else CONDbits.fastCharge = 1;
    //Check if a cell has reached it's ballance voltage.
    int bal_L = 0;
    for(int i=0;i<Cell_Count;i++){
        if(dsky.Cell_Voltage[i]>=sets.battery_rated_voltage){
            switch(i){
                case 0 : bal_L = bal_L | 0x01;
                break;
                case 1 : bal_L = bal_L | 0x02;
                break;
                case 2 : bal_L = bal_L | 0x04;
                break;
                case 3 : bal_L = bal_L | 0x08;
                break;
                default:
                break;
            }
        }
    }
    Ballance_LEDS = bal_L;
    //Check for receive buffer overflow.
    if(U1STAbits.OERR){
        fault_log(0x2D);
        char garbage;
        //Flush the buffer.
        while(U1STAbits.URXDA)garbage = U1RXREG;
        U1STAbits.OERR = 0; //Clear the fault bit so that receiving can continue.
    }
    if(U2STAbits.OERR){
        fault_log(0x2E);
        char garbage;
        //Flush the buffer.
        while(U2STAbits.URXDA)garbage = U2RXREG;
        U2STAbits.OERR = 0; //Clear the fault bit so that receiving can continue.
    }
    //Main power check
    main_power_check();
    //Charger plug-in check.
    chargeDetect();
    //Calculate limit currents based on temperature.
    temperatureCalc();

    /***************************************************************************/
    // Check for charger disconnect.
    if(!BV_Fault){
        //chrgLight = off;  //charger light off.
        charge_power = 0;
    }

    //Clear fault_shutdown if all power modes are turned off.
    if(CONDbits.Run_Level < Cal_Mode){
        shutdown_timer = 1;     //Acts like a resettable circuit breaker.
        STINGbits.fault_shutdown = no;
    }


    //Get the absolute value of battery_usage and store it in absolute_battery_usage.
    vars.absolute_battery_usage = absFloat(vars.battery_usage);
    //Calculate the max capacity of the battery once the battery has been fully charged and fully discharged.
    if(voltage_percentage > 99 && power_session != 4){
        //battery_capacity = absolute_battery_usage;
        vars.battery_remaining = vars.battery_capacity;
        power_session = 4;
        vars.battery_usage = 0;  //reset battery usage session.
    }
    //At about 82% voltage the battery is at about 50% actual capacity for lithium ion.
    else if(voltage_percentage < 83 && voltage_percentage > 81 && (power_session == 4 || power_session == 0)){
        vars.battery_capacity = vars.absolute_battery_usage;  //Calculate the max capacity of the battery after a half discharge.
        vars.battery_capacity *= 2;
        power_session = 2;
    }
    else if(voltage_percentage < 1 && power_session != 0){
        vars.battery_capacity = vars.absolute_battery_usage;  //Calculate the max capacity of the battery after a full discharge.
        vars.battery_remaining = 0;  // Set ah remaining to 0 when less than 2% voltage.
        power_session = 0;
        vars.battery_usage = 0;  //reset battery usage session.
    }
    //Don't let battery_remaining go below 0;
    //This should never happen in normal conditions. This is just a catch.
    if(vars.battery_remaining < 0) vars.battery_remaining = 0;
    //*******************************************
    //Don't let battery_remaining go above battery capacity.
    if(vars.battery_remaining > vars.battery_capacity) vars.battery_remaining = vars.battery_capacity;
    //Don't let 'battery_remaining' go above the partial charge percentage when partial charging.
    //To Do: This isn't exactly right because, for example, ~90% Voltage != ~90% total capacity!!!
    //It's only a few % off so for now it's okay. Will implement real voltage curve calculation later.
    if(STINGbits.p_charge && (vars.battery_remaining > (vars.battery_capacity * sets.partial_charge))
    && dsky.pack_vltg_average <= (sets.battery_rated_voltage * sets.partial_charge))
        vars.battery_remaining = (vars.battery_capacity * sets.partial_charge);
    //**************************************************
    //Calculate battery %
    dsky.chrg_percent = ((vars.battery_remaining / vars.battery_capacity) * 100);
    /****************************************/
    //Initial startup sequence and calibration.
    initialCal();
    /* End the IRQ. */
	IFS0bits.T1IF = 0;
}

/* 0.125 second IRQ */
//Used for some critical math timing operations. Cycles through every 1/8 sec.
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt (void){
    //CPUact = on;
    //Blink some LEDs
    BlinknLights++; //Just count up all the time once every 1/8 second.
    //Check pre-charge timer.
    if(CONDbits.Power_Out_EN && precharge_timer<PreChargeTime)precharge_timer++;
    //Soft over-current monitoring.
    if(absFloat(dsky.battery_current) > dsky.max_current){
        if(soft_OVC_Timer > SOC_Cycles){
            CONDbits.Power_Out_EN = off;
            fault_log(0x2F);
            STINGbits.fault_shutdown = yes;
        }
        else soft_OVC_Timer++;
    }
    //Low voltage monitoring and auto off.
    for(int i=0;i<4;i++){
        if(dsky.Cell_Voltage[i] < sets.dischrg_voltage){
            CONDbits.Power_Out_EN = off;
            //fault_log(0x04);
            //STINGbits.fault_shutdown = yes;
        }
    }
    dsky.watts = dsky.battery_crnt_average * dsky.pack_vltg_average;
    //Relay On Timers. Wait a little bit after turning on the relays before trying to regulate.
    if(heat_rly_timer > 0 && heat_rly_timer != 3)//
        heat_rly_timer--;

    //Get average voltage and current.
    if(avg_cnt >= 8){
        bt_crnt_avg_temp /= 8;
        dsky.battery_crnt_average = bt_crnt_avg_temp;
        bt_vltg_avg_temp /= 8;
        dsky.pack_vltg_average = bt_vltg_avg_temp;
        bt_vltg_avg_temp = 0;
        bt_crnt_avg_temp = 0;
        avg_cnt = 0;
        if(STINGbits.charge_GO)current_cal();
    }
    else{
        bt_crnt_avg_temp += dsky.battery_current;
        bt_vltg_avg_temp += dsky.pack_voltage;
        avg_cnt++;
    }
    //*************************
    //Get peak power output.
    float power = absFloat(dsky.battery_crnt_average * dsky.pack_vltg_average);
    if (power > dsky.peak_power){
        dsky.peak_power = power;
    }
    //*****************************
    //Calculate and Log AH usage for battery remaining and total usage.
    //Do not track current usage if below +-0.002 amps due to error in current sensing. We need a lower pass filter then what we already have.
    if(absFloat(dsky.battery_current) > 0.002){
        //Calculate how much current has gone in/out of the battery.
        vars.battery_usage += (calc_125 * dsky.battery_current);
        vars.battery_remaining += (calc_125 * dsky.battery_current);
    }
    //*************************************************************
    /****************************************/
    /* End the IRQ. */
	IFS0bits.T2IF = 0;
}
/****************/
/* END IRQs     */
/****************/

#endif
