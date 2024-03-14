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

/* Include the Source AND Headers HERE or else mplab slowINHIBIT_Timergets pissy for some reason.
 * Don't bother trying to include the source and header files into the project,
 * it doesn't work. Either I'm doing it wrong or it's broken, but what I have here WORKS SO DON'T TOUCH IT.
 */
//#include <p30f3011.h>
//#include <libpic30.h>
//#include <xc.h>
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
    CONDbits.clockSpeed = slow; //Force a switchover to fast clock. It will not switch if this bool is == to fast
    OSC_Switch(fast);
    slowINHIBIT_Timer = 10;
    /* General 3 IO. */
    GENERAL3_TRIS = GENERAL3_DIR;
    GENERAL3_LAT = 0;
    GENERAL3_PORT = 0;
    KeepAlive = 1; //Enable Keep Alive signal. System keeps itself on while main_power is enabled.
    /* Analog inputs */
    //Initialize PORTB first.
    ANALOG_TRIS = ANALOG_DIR;          //set portb to analog inputs.
    ANALOG_LAT = 0;
    ANALOG_PORT = 0; //clear portb
    configure_IO();
    Batt_IO_OFF();
    //CPUact = 1;             //Turn on CPU ACT light.
    //Calculate space required for eeprom storage.
    cfg_space = sizeof(sets) / 2;
    vr_space = sizeof(vars) / 2;
    dsky_space = sizeof(dsky) / 2;
    Exception_Check();
    //Get either default or custom settings.
    get_settings();
    vars.battery_capacity = sets.amp_hour_rating; //Set capacity based on AH rating.
    //Get variable data if it exists.
    get_variables();
    //Do an initial reset and warm start check.
    first_check();
    //Initialize Systems.
    Run_Level = Cal_Mode;
    Init();
    send_string("Init. \n\r", PORT1);
    send_string("Init. \n\r", PORT2);

/*****************************/
    // Main Loop.
/*****************************/
    /* Everything is run using IRQs from here on out.
     * Look in the other source files that MPLAB doesn't open automatically.
     */
    for (;;)        //loop forever. or not, idc, we have IRQs for stuff.
    {
        //Check trap flag bits.
        Exception_Check();
        if(Run_Level == Crit_Err)death_loop();
        //Deep sleep check.
        if(STINGbits.deep_sleep){
            Batt_IO_OFF();               //Turn off all IO before sleeping.
            //CPUact = 0;      //Turn CPU ACT light off.
            Deep_Sleep();        //Cuts main power to self.
            /* If the keep alive pin isn't used or if the power control hardware
             * is faulty then this does nothing and the micro will
             * sleep on the next instruction. Even in Sleep it still draws
             * nearly a quarter of a watt! WTF Microchip? Why did I choose
             * this microcontroller again?
             * It's what I had on hand when I first started developing this.
             * Oh well, we have ways of getting around it so it works for now.
             */
            //Heat_CTRL = 50;
            OSC_Switch(slow);
            Idle();
            OSC_Switch(fast);
            //Sleep();
            STINGbits.deep_sleep = 0;
        }
        else {
            //CPUact = 0;      //Turn CPU ACT light off.
            //Heat_CTRL = 50;
            OSC_Switch(slow);
            Idle();                 //Idle Loop, saves power.
            OSC_Switch(fast);
        }
    }
    return 0;
}
