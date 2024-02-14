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

#ifndef TRAPIRQS_C
#define TRAPIRQS_C

#include "IRQs.h"
#include "common.h"
#include "sysChecks.h"
#include "eeprom.h"

/*****************/
/* IRQs go here. */
/*****************/

/* CPU TRAPS, log erros here and shut down if needed.*/
void __attribute__((interrupt, no_auto_psv)) _FLTAInterrupt (void){
    //CPUact = 1;
    io_off();
    STINGbits.fault_shutdown = 1;
    fault_log(0x0C);        //PWM fault. External.
    save_vars();
    IFS2bits.FLTAIF = 0;
}
void __attribute__((interrupt, no_auto_psv)) _OscillatorFail (void){
    //Check the PLL lock bit as fast as possible before anything else because it doesn't stay set for long.
    if(OSCCONbits.LOCK == 0){
        if(!STINGbits.osc_fail_event){
            fault_log(0x12);
        }
    }
    //CPUact = 1;
    io_off();
    STINGbits.fault_shutdown = 1;
    if(STINGbits.osc_fail_event){
        fault_log(0x0D);
    }
    STINGbits.osc_fail_event = 1;         //Only log it once per reset.
    save_vars();
    INTCON1bits.OSCFAIL = 0;
}
void __attribute__((interrupt, no_auto_psv)) _AddressError (void){
    //CPUact = 1;
    io_off();
    STINGbits.fault_shutdown = 1;
    //send_string(0x03, "Address Error Event.");
    fault_log(0x0E);
    save_vars();
    INTCON1bits.ADDRERR = 0;
}
void __attribute__((interrupt, no_auto_psv)) _StackError (void){
    //CPUact = 1;
    SPLIM = stackFaultDefault;
    io_off();
    STINGbits.fault_shutdown = 1;
    //send_string(0x03, "Stack Error Event.");
    fault_log(0x0F);
    save_vars();
    INTCON1bits.STKERR = 0;
}
void __attribute__((interrupt, no_auto_psv)) _MathError (void){
    //CPUact = 1;
    io_off();
    STINGbits.fault_shutdown = 1;
    //send_string(0x03, "Math Error Event.");
    fault_log(0x10);
    save_vars();
    INTCON1bits.MATHERR = 0;
}
void __attribute__((interrupt, no_auto_psv)) _ReservedTrap7 (void){
    //CPUact = 1;
    io_off();
    STINGbits.fault_shutdown = 1;
    fault_log(0x11);
    save_vars();
    //INTCON1bits.DMACERR = 0;
}
/****************/
/* END IRQs     */
/****************/

#endif
