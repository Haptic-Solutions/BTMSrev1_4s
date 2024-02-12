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

#include "common.h"

/* Include the Source AND Headers HERE or else mplab gets pissy for some reason.
 * Don't bother trying to include the source and header files into the project,
 * it doesn't work. Either I'm doing it wrong or it's broken, but what I have here WORKS SO DON'T TOUCH IT.
 */

#include "defines.h"
#include "chipconfig.h"
#include "IRQs.h"
#include "sysIRQs.c"
#include "dataIRQs.c"
#include "trapIRQs.c"
#include "common.h"
#include "subs.c"
#include "DataIO.h"
#include "DataIO.c"
#include "Init.h"
#include "Init.c"
#include "display.c"
#include "display.h"
#include "eeprom.c"
#include "eeprom.h"
#include "checksum.c"
#include "checksum.h"
#include "sysChecks.c"
#include "sysChecks.h"
#include "regulate.c"
#include "regulate.h"

/* Program Start */
/***********************************************************
***********************************************************/
int main(void){
    CONDbits.EnableChIRQ = 1;
    /* General 3 IO. */
    GENERAL3_TRIS = 0xFFF1; //set portd to all inputs except for RD2(KEEPALIVE), RD3(UNUSED), and RD1(mainContactor)
    GENERAL3_LAT = 0;
    GENERAL3_PORT = 0;
    keepAlive = 1; //Enable Keep Alive signal. System keeps itself on while main_power is enabled.
    /* Analog inputs and general IO */
    //Initialize PORTB first.
    ANALOG_TRIS = 0x008F;          //set portb to mix analog inputs and digital outputs.
    ANALOG_LAT = 0;
    ANALOG_PORT = 0; //clear portb
    CPUact = 1;             //Turn on CPU ACT light.
    //Calculate space required for eeprom storage.
    cfg_space = sizeof(sets) / 2;
    vr_space = sizeof(vars) / 2;
    dsky_space = sizeof(dsky) / 2;
    //Get variable data if it exists.
    get_variables();
    //Get either default or custom settings.
    get_settings();
    //Do an initial reset and warm start check.
    first_check();
    //Disable Charge Detect IRQ on power up.
    CONDbits.EnableChIRQ = 0;
    //Initialize Systems.
    Init();

/*****************************/
    // Main Loop.
/*****************************/
    /* Everything is run using IRQs from here on out.
     * Look in the other source files that MPLAB doesn't open automatically.
     */
    for (;;)        //loop forever. or not, idc, we have IRQs for stuff.
    {
        //Deep sleep check.
        if(STINGbits.deep_sleep){
            io_off();               //Turn off all IO before sleeping.
            CPUact = 0;      //Turn CPU ACT light off.
            power_off();        //Cuts main power to self.
            /* If the keep alive pin isn't used or if the power control hardware
             * is faulty then this does nothing and the micro will
             * sleep on the next instruction. Even in Sleep it still draws
             * nearly a quarter of a watt! WTF Microchip? Why did I choose
             * this microcontroller again?
             * It's what I had on hand when I first started developing this.
             * Oh well, we have ways of getting around it so it works for now.
             */
            Idle();
            //Sleep();
            STINGbits.deep_sleep = 0;
        }
        else{
            CPUact = 0;      //Turn CPU ACT light off.
            Idle();                 //Idle Loop, saves power.
        }
    }
    return 0;
}
