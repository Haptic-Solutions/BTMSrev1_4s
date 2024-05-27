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
#include "SysCalculations.h"
#include "safetyChecks.h"


/* Batter OV fault IRQ. */
void __attribute__((interrupt, no_auto_psv)) _INT0Interrupt (void){
    OSC_Switch(fast);
    Batt_IO_OFF();
    STINGbits.fault_shutdown = 1;
    fault_log(0x3A, 0x00);
    Flags |= OverVLT_Fault;
    save_vars();
    IFS0bits.INT0IF = 0;
}

/* Current sensor Fault IRQ. */
void __attribute__((interrupt, no_auto_psv)) _INT1Interrupt (void){
    OSC_Switch(fast);
    Batt_IO_OFF();
    STINGbits.fault_shutdown = 1;
    fault_log(0x39, 0x00);
    save_vars();
    IFS1bits.INT1IF = 0;
}

/* Analog Input IRQ */
void __attribute__((interrupt, no_auto_psv)) _ADCInterrupt (void){
    IFS0bits.ADIF = 0;
    Cell_Volt=on; //enable cell voltage sense.
    OSC_Switch(fast);
    output_PWM();
    //Get 8 samples for averaging.
    if (analog_avg_cnt < sample_Average){
        //Force use of all 0's if we haven't burned the first ADC sample after a startup.
        //The ADC takes a moment to get correct values but it still sends the IRQs anyways.
        if (STINGbits.adc_sample_burn){
            CavgVolt += ChargeVoltage; //Charger Voltage
            BavgCurnt += BCsense; //Battery Current
            //avgBTemp += Btemp; //Batt Temp
            avgSTemp += Mtemp; //Self Temp
            avgBTemp = avgSTemp;
            BavgVolt[0] += LithCell_V1;
            BavgVolt[1] += LithCell_V2;
            BavgVolt[2] += LithCell_V3;
            BavgVolt[3] += LithCell_V4;
            CavgCurnt += CCsense; //Charger Current
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
        if(STINGbits.adc_sample_burn && analog_const!=0)calcAnalog(); //Calculate analog inputs.
        //Reset analog average count.
        analog_avg_cnt = clear;
        //Check to see if the system is ready to run.
        if(Flags&syslock)IsSysReady(); //If there is a fault, keep system from running. Do this only if settings are LOCKED
        //ADC sample burn check. Only burn once when main power iCell_Voltage_Average[i]s on. Otherwise burn every time heartbeat activates the ADC
        if (Run_Level < Cal_Mode && STINGbits.adc_sample_burn == yes && gas_gauge_timer == 0){
            ADCON1bits.ADON = off;                // turn ADC off to save power.
            Cell_Volt=off; //disable cell voltage sense.
            STINGbits.adc_sample_burn = no;     //Burn the first ADC sample on every power up of ADC.
        }
        else STINGbits.adc_sample_burn = yes;      //We have burned the first set.
        USB_Power_Present_Check(); //Enable or Disable PORT1 depending if there is voltage present to FTDI chip.
    }
    //Run the LED routine
    if((Run_Level > Cal_Mode || (gas_gauge_timer > 0 && Run_Level != Cal_Mode)) && (Flags&syslock))LED_Mult(on);
    else if(!(Flags&syslock) && !CONDbits.V_Cal)LED_Mult(Ltest);
    else if(Run_Level != Crit_Err && Run_Level != Cal_Mode) LED_Mult(Ballance);
    else LED_Mult(off);
    //End IRQ
}

/* Heartbeat IRQ, Once every Second. Lots of stuff goes on here. */
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt (void){
    IFS0bits.T1IF = 0;
    OSC_Switch(fast);
    //calculate target charge voltage
    pack_target_voltage = sets.battery_rated_voltage*sets.Cell_Count;
    //Check for how fast we are charging.
    if(dsky.battery_crnt_average > (sets.chrg_C_rating*sets.amp_hour_rating)*0.75)CONDbits.fastCharge = 1;
    else CONDbits.fastCharge = 0;
    //Check if a cell has reached it's ballance voltage.
    int bal_L = 0;
    float lowest_cell = 100;
    int lowest_c_num = 0;
    //Do not run ballance resistor on the lowest cell.
    for(int i=0;i<sets.Cell_Count;i++){
        if(Cell_Voltage_Average[i]<lowest_cell){
            lowest_c_num = i;
            lowest_cell = Cell_Voltage_Average[i];
        }
    }
    //Check which cell is equal to or above set voltage.
    for(int i=0;i<sets.Cell_Count;i++){
        if(Cell_Voltage_Average[i]>=sets.battery_rated_voltage && !CONDbits.V_Cal && i!=lowest_c_num){
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
        fault_log(0x2D, 0x00);
        char garbage;
        //Flush the buffer.
        while(U1STAbits.URXDA)garbage = U1RXREG;
        U1STAbits.OERR = 0; //Clear the fault bit so that receiving can continue.
    }
    if(U2STAbits.OERR){
        fault_log(0x2E, 0x00);
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

    //Clear fault_shutdown if all power modes are turned off.
    if(Run_Level < Cal_Mode){
        shutdown_timer = 1;     //Acts like a resettable circuit breaker.
        STINGbits.fault_shutdown = no;
    }

    //Get the absolute value of battery_usage and store it in absolute_battery_usage.
    vars.absolute_battery_usage = absFloat(vars.battery_usage);
    //Calculate the max capacity of the battery once the battery has been fully charged and fully discharged.
    if(CONDbits.got_open_voltage && first_cal == 3){
        //Don't let battery_remaining go below 0% or above 100%;
        //This should never happen in normal conditions. This is just a catch.
        if(vars.battery_remaining < 0) vars.battery_remaining = 0;
        else if(vars.battery_remaining > vars.battery_capacity) vars.battery_remaining = vars.battery_capacity;
    }
    //**************************************************
    //Calculate battery %
    if(vars.battery_capacity == 0)vars.battery_capacity=0.0001;  //Prevent divide by zero. Make it a safe value.
    dsky.chrg_percent = ((vars.battery_remaining / vars.battery_capacity) * 100);
    /****************************************/
    //Calculate number of charge cycles the battery is going through
    if(dsky.battery_crnt_average>0.015 && CONDbits.charger_detected){
        vars.chargeCycleLevel+=dsky.battery_crnt_average/3600;
        if(vars.chargeCycleLevel>=vars.battery_capacity){
            vars.chargeCycleLevel = 0;
            if(vars.TotalChargeCycles<65535)vars.TotalChargeCycles++;
            //And decrease battery capacity after every full charge cycle.
            float capDec = sets.cycles_to_80 * 5;
            if(capDec==0)capDec=1;
            vars.battery_capacity *= 1-(1/capDec);
        }
    }
    if(PORTS_DONE() && slowINHIBIT_Timer > 0 && !CONDbits.charger_detected)slowINHIBIT_Timer--;
    /* End the IRQ. */
}

/* 0.125 second IRQ */
//Used for some critical math timing operations. Cycles through every 1/8 sec.
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt (void){
    IFS0bits.T2IF = 0;
    OSC_Switch(fast);
    // turn ADC on to get a sample.
    ADCON1bits.ADON = on;
    //Blink some LEDs
    BlinknLights++; //Count up all the time once every 1/8 second.
    //I2C timeout counter and error logger.
    if(IC_Timer>0)IC_Timer--;
    else if(IC_Timer==0){
        fault_log(0x40, IC_Seq);
        IC_Timer=-1;
        IC_Seq = clear;
        I2CCONbits.I2CEN = 0;   //disable I2C interface
    }
    //Check power switch or button.
    if(PWR_SW)gas_gauge_timer = gauge_timer;
    else if(gas_gauge_timer>0 && Run_Level != Cal_Mode)gas_gauge_timer--;
    switch(sets.PWR_SW_MODE){
        case push_and_hold:
            if(PWR_SW){
                if(button_timer == 16){
                    if(CONDbits.Power_Out_EN)CONDbits.Power_Out_EN = 0;
                    else CONDbits.Power_Out_EN = 1;
                    button_timer = 17;
                }
                else if(button_timer < 16) button_timer++;
            }
            else button_timer = 0;
        break;
        case toggle_switch:
            if(PWR_SW && !CONDbits.Power_Out_Lock)CONDbits.Power_Out_EN = 1;
            else {
                CONDbits.Power_Out_EN = 0;
                CONDbits.Power_Out_Lock = 0;
            }
        break;
        case on_with_charger:
            if(dsky.Cin_voltage>4 && !CONDbits.Power_Out_Lock)CONDbits.Power_Out_EN = 1;
            else if(dsky.Cin_voltage<1) {
                CONDbits.Power_Out_EN = 0;
                CONDbits.Power_Out_Lock = 0;
            }
        break;
        case off_with_charger:
            if(dsky.Cin_voltage<1 && !CONDbits.Power_Out_Lock)CONDbits.Power_Out_EN = 1;
            else if(dsky.Cin_voltage>4) {
                CONDbits.Power_Out_EN = 0;
                CONDbits.Power_Out_Lock = 0;
            }
        break;
        default:
        break;
    }
    //Check pre-charge timer.
    if(CONDbits.Power_Out_EN && precharge_timer<PreChargeTime)precharge_timer++;
    //Soft over-current monitoring.
    if(dsky.max_current > 0 && CONDbits.Power_Out_EN && absFloat(dsky.battery_current) > dsky.max_current && (Flags&syslock)){
        if(soft_OVC_Timer > SOC_Cycles){
            CONDbits.Power_Out_EN = off;
            fault_log(0x2F, 0x00);
            STINGbits.fault_shutdown = yes;
        }
        else soft_OVC_Timer++;
    }
    //Low voltage monitoring and auto off.
    for(int i=0;i<sets.Cell_Count;i++){
        if(dsky.Cell_Voltage[i] < sets.low_voltage_shutdown && (Flags&syslock)){
            CONDbits.Power_Out_EN = off;
            fault_log(0x04, i+1);
            STINGbits.fault_shutdown = yes;
        }
    }
    dsky.watts = dsky.battery_crnt_average * dsky.pack_vltg_average;

    //Get average voltage and current.
    if(STINGbits.adc_valid_data){
        if(avg_cnt < 8){
            for(int i=0;i<Max_Cell_Count;i++){
                temp_Cell_Voltage_Average[i] += dsky.Cell_Voltage[i];
            }
            CavgCurnt_temp += dsky.Cin_current;
            bt_crnt_avg_temp += dsky.battery_current;
            bt_vltg_avg_temp += dsky.pack_voltage;
            avg_cnt++;
        }
        else{
            for(int i=0;i<Max_Cell_Count;i++){
                temp_Cell_Voltage_Average[i] /= 8;
                Cell_Voltage_Average[i] = temp_Cell_Voltage_Average[i];
            }
            CavgCurnt_temp /= 8;
            CavgCurnt = CavgCurnt_temp;
            bt_crnt_avg_temp /= 8;
            dsky.battery_crnt_average = bt_crnt_avg_temp;
            bt_vltg_avg_temp /= 8;
            dsky.pack_vltg_average = bt_vltg_avg_temp;
            for(int i=0;i<Max_Cell_Count;i++){
                temp_Cell_Voltage_Average[i] = 0;
            }
            CavgCurnt_temp = 0;
            bt_vltg_avg_temp = 0;
            bt_crnt_avg_temp = 0;
            avg_cnt = 0;
            initial_comp();
            if(avg_rdy<2)avg_rdy++;
        }
    }
    //Check for sane analog values.
    if((Flags&syslock) && STINGbits.adc_valid_data && !STINGbits.fault_shutdown) analog_sanity();
    //Check to make sure the battery and other systems are within safe operating conditions.
    //Shutdown and log the reason why if they aren't safe.
    if((Flags&syslock) && STINGbits.adc_valid_data && !STINGbits.fault_shutdown && avg_rdy > 0) explody_preventy_check();
    //Check for over current condition.
    if((Flags&syslock) && STINGbits.adc_valid_data && !STINGbits.fault_shutdown)currentCheck();
    //*************************
    //Get peak power output.
    if(avg_rdy>0){
        float power = absFloat(dsky.battery_crnt_average * dsky.pack_vltg_average);
        if (power > dsky.peak_power){
            dsky.peak_power = power;
        }
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
    //LED test sequencer
    LED_Test*=2;
    if(LED_Test>8){
        LED_Test=0x01;
        if(CONDbits.LED_test_ch)CONDbits.LED_test_ch=0;
        else CONDbits.LED_test_ch=1;
    }
    /****************************************/
    //Initial startup sequence and calibration.
    initialCal();
    /* End the IRQ. */
}
/****************/
/* END IRQs     */
/****************/

#endif
