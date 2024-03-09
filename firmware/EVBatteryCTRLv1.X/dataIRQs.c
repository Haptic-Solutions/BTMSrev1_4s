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

#ifndef DATAIRQS_C
#define DATAIRQS_C

#include "IRQs.h"
#include "common.h"
#include "DataIO.h"
#include "Init.h"
#include "display.h"
#include "eeprom.h"
#include "checksum.h"

/*****************/
/* IRQs go here. */
/*****************/

/* Non time-critical systems. Timer 4 IRQ. 1 Second.*/
//For low priority CPU intensive processes and checks.
void __attribute__((interrupt, no_auto_psv)) _T4Interrupt (void){
    //CPUact = on;
    /* Deep Sleep TIMER stuff. Do this to save power.
     * This is so that this system doesn't drain your 1000wh battery over the
     * course of a couple weeks while being unplugged from a charger.
     * The dsPIC30F3011 is a power hog even in Idle and Sleep modes.
     * For future people, KEEP USING IRQs FOR STUFF!!! Don't make the CPU wait
     * for anything! The dsPIC30F3011 is a power drain and will consume all
     * your electrons and burn your lunch and house down from the heat that it generates! */
    if(Run_Level > Heartbeat){
        if(STINGbits.OverCRNT_Fault){
            //If there has been a hardware over-current event then we need to power off sooner to reset the OC latches.
            PowerOffTimer=0;
            PowerOffTimerSec = 19;
        }
        else {
            PowerOffTimer = sets.PowerOffAfter;      //reset the timer when main_power is on.
            PowerOffTimerSec = 59;                   //60 seconds.
        }
    }
    //Run_Level is at Heartbeat or below. Start counting down.
    else{
        //When main_power is off count down in minutes.
        if(PowerOffTimerSec <= 0){
            PowerOffTimerSec = 59;
            if(PowerOffTimer <= 0) STINGbits.deep_sleep = 1; //set deep_sleep to 1. Power off the system to save power after all IRQ's are finished.
            else PowerOffTimer--;
        }
        else PowerOffTimerSec--;
    }
    //Runtime program memory check. Checks every half hour except on startup it will run after 10 seconds.
    //This seems to cause a stack error sometimes? Maybe too much as getting nested causing the stack to grow too large.
    if(check_timer == 1800 && Run_Level > Crit_Err){
        if(check_prog() == 1) Run_Level=Crit_Err;  //Program memory is corrupted and cannot be trusted.
        check_timer = clear;
    }
    else if(Run_Level > Crit_Err) check_timer++;
    //Check settings ram in background. (lowest priority IRQ))
    //Don't check if in Calibration mode because some setting might be changing on the fly.
    //Don't check right after a PGM memory check as it takes too much time and could crash the system.
    if(Run_Level != Cal_Mode && Run_Level > Crit_Err && check_timer){
        if(check_ramSets()){
            //If failed, shutdown and attempt to recover.
            get_settings();
            //Make no more than 5 attempts to recover before going into debug mode.
            if(ram_err_count >= 5) Run_Level=Crit_Err; //Settings memory is corrupted and cannot be trusted.
            else ram_err_count++;
        }
    }
    //End IRQ
    IFS1bits.T4IF = clear;
}

//Another Heavy process IRQ
//For low priority CPU intensive processes and checks, and 0.125 second non-critical timing.
void __attribute__((interrupt, no_auto_psv)) _T5Interrupt (void){
    //CPUact = on;
    //Do display stuff.
    //displayOut(PORT1);
    //displayOut(PORT2);
    //End IRQ
    IFS1bits.T5IF = clear;
}

/* Data and Command input and processing IRQ for Port 1 */
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt (void){
    //CPUact = on;
    Command_Interp(PORT1);
/****************************************/
    /* End the IRQ. */
    IFS0bits.U1RXIF = clear;
}

/* Data and Command input and processing IRQ for Port 2. */
void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt (void){
    //CPUact = on;
    Command_Interp(PORT2);
/****************************************/
    /* End the IRQ. */
    IFS1bits.U2RXIF = clear;
}

/* Output IRQ for Port 1 */
void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt (void){
    //CPUact = on;
    //Dispatch the buffer to the little 4 word Serial Port buffer as it empties.
    while(!U1STAbits.UTXBF && (Buffer[PORT1][Buff_index[PORT1]] != NULL) && portBSY[PORT1]){
        U1TXREG = Buffer[PORT1][Buff_index[PORT1]];
        Buff_index[PORT1]++;
    }
    //Reset the buffer index and count when done sending.
    Buffrst(PORT1);
    /****************************************/
    /* End the IRQ. */
    IFS0bits.U1TXIF = clear;
}

/* Output IRQ for Port 2 */
void __attribute__((interrupt, no_auto_psv)) _U2TXInterrupt (void){
    //CPUact = on;
    //Dispatch the buffer to the little 4 word Serial Port buffer as it empties.
    while(!U2STAbits.UTXBF && (Buffer[PORT2][Buff_index[PORT2]] != NULL) && portBSY[PORT2]){
        U2TXREG = Buffer[PORT2][Buff_index[PORT2]];
        Buff_index[PORT2]++;
    }
    //Reset the buffer index and count when done sending.
    Buffrst(PORT2);
    /****************************************/
    /* End the IRQ. */
    IFS1bits.U2TXIF = clear;
}

/****************/
/* END IRQs     */
/****************/

#endif
