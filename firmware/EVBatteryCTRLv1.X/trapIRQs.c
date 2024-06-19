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
//Level 14 hard
void __attribute__((interrupt)) _OscillatorFail (void){
    Tfaultsbits.OSC = 1;
    INTCON1bits.OSCFAIL = 0;
    asm("reset");
}
//Level 13 hard
void __attribute__((interrupt)) _StackError (void){
    Tfaultsbits.STACK = 1;
    INTCON1bits.STKERR = 0;
    asm("reset");
}
//Level 12 hard
void __attribute__((interrupt)) _AddressError (void){
    Tfaultsbits.ADDRESS = 1;
    INTCON1bits.ADDRERR = 0;
    asm("reset");
}
//Level 11 soft
void __attribute__((interrupt)) _MathError (void){
    Tfaultsbits.MATH = 1;
    INTCON1bits.MATHERR = 0;
    asm("reset");
}
void __attribute__((interrupt)) _FLTAInterrupt (void){
    Tfaultsbits.FLTA = 1;
    IFS2bits.FLTAIF = 0;
    asm("reset");
}
void __attribute__((interrupt)) _ReservedTrap7 (void){
    Tfaultsbits.RESRVD = 1;
    asm("reset");
}
/****************/
/* END IRQs     */
/****************/

#endif
