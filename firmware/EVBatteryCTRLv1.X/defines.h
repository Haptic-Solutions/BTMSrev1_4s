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

#ifndef DEFINES_H
#define	DEFINES_H
//##############################################################################
#include <p30f3011.h>
//#include <libpic30.h>
//#include <xc.h>
// Tm = 32767 * (1 / (((clkSpeedmhz * PLL) / 4) / tiksPerIRQ))
//#define IPS 29.48;   //million instructions per second.
#define IPS 14.74   //million instructions per second.
#define BAUD1 9600  //Default BAUD rate for PORT 1
#define BAUD2 9600  //Default rate for PORT 2
#define calc_125 0.00003472 //Value for calculating the total current in and out of battery every second.
//Firmware Version String
#define version "\n\rV1.0A\n\r"
//IO inputs
#define keySwitch !PORTFbits.RF1
#define chrgSwitch PORTEbits.RE8
//Analog inputs
#define adcVoltage ADCBUF0 //Voltage
#define adcCurrent ADCBUF1 //Current
#define adcBTemp ADCBUF2 //Batt Temp
#define adcMTemp ADCBUF3 //Motor Temp
#define adcSTemp ADCBUF4 //Self Temp
//IO outputs
#define CPUact LATBbits.LATB6
#define errLight LATBbits.LATB5
#define chrgLight LATBbits.LATB4
#define keepAlive LATDbits.LATD2
#define fanRelay LATFbits.LATF0
#define heatRelay LATCbits.LATC15
#define AUXrelay LATBbits.LATB8
#define ctRelay LATDbits.LATD1
#define chrgRelay LATFbits.LATF6
#define outPWM PDC3
#define heatPWM PDC1
#define chrgPWM PDC2

//IO
#define ANALOG_TRIS TRISB
#define ANALOG_LAT LATB
#define ANALOG_PORT PORTB

#define GENERAL1_TRIS TRISC
#define GENERAL1_LAT LATC
#define GENERAL1_PORT PORTC

#define GENERAL3_TRIS TRISD
#define GENERAL3_LAT LATD
#define GENERAL3_PORT PORTD

#define PWM_TRIS TRISE
#define PWM_LAT LATE
#define PWM_PORT PORTE

#define GENERAL2_TRIS TRISF
#define GENERAL2_LAT LATF
#define GENERAL2_PORT PORTF

//Memory Defines
/* This assums the compiler puts the stack at the end of memory space just after
 * the user variables and the stack pointer counts up */
#define ramSize 0x03FF
#define ramAddressStart 0x0800
#define stackFaultDefault ramSize + ramAddressStart
#define ramFree (ramSize + ramAddressStart) - 15 //Minus 15 bytes of ram. If the stack intrudes on this then it should throw an error code before a complete system crash.

//General
#define yes 1
#define no 0
#define on 1
#define off 0
#define set 1
#define clear 0
#define NULL 0
#define input 1
#define output 0

//Heater calibration
#define notrun 0
#define initialize 1
#define calibrating 2
#define ready 3
#define error 4
#define disabled 5

//##############################################################################
#endif


