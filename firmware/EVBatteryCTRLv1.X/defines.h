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
// Tm = 32767 * (1 / (((clkSpeedmhz * PLL) / 4) / tiksPerIRQ))
//#define IPS 29.48;   //million instructions per second.
#define IPS 14.74   //million instructions per second.
#define BAUD1 9600  //Default BAUD rate for PORT 1
#define BAUD2 9600  //Default BAUD rate for PORT 2
#define calc_125 0.00003472 //Value for calculating the total current in and out of battery every second.
//Firmware Version String
#define version "\n\rV1.0_2S-4S\n\r"
//IO inputs
#define __PwrKey !PORTFbits.RF1 //Power on/off switch, button, or key.
#define BV_Fault PORTEbits.RE8  //Battery Voltage Fault.
#define V_Bus_Stat PORTEbits.RE4 //USB-C VBus status.
#define C_Fault PORTDbits.RD0 //Battery or charge input/output current fault.
//Analog inputs
#define ChargeVoltage ADCBUF0 //Voltage
#define BCsense ADCBUF1 //Current
#define Btemp ADCBUF2 //Batt Temp
#define Mtemp ADCBUF3 //My Temp
#define LithCell_V1 ADCBUF4 //Cell 1 Volts
#define LithCell_V2 ADCBUF5 //Cell 2 Volts
#define LithCell_V3 ADCBUF6 //Cell 3 Volts
#define LithCell_V4 ADCBUF7 //Cell 4 Volts
#define CCsense ADCBUF8 //CCsense
//IO outputs
#define KeepAlive LATFbits.LATF0 //Enables power to self and system.
#define PreCharge LATFbits.LATF6 //Power Output pre-charge
#define PowerOutEnable LATCbits.LATC15 //Power output enable.
//LED outputs
#define Mult_SEL LATEbits.LATE2 //LED and Cell ballance multiplexed select.
#define Mult_B1 LATEbits.LATE0
#define Mult_B3 LATDbits.LATD2
#define Mult_B2 LATDbits.LATD1
#define Mult_B4 LATDbits.LATD3
#define LED_dir_1 TRISE
#define LED_dir_2 TRISD
#define LED_HiZ_1 PWM_TRIS_DIR | 0x0001
#define LED_HiZ_2 GENERAL3_DIR | 0x000E
#define DFLT_1 PWM_TRIS_DIR
#define DFLT_2 GENERAL3_DIR

#define Heat_CTRL PDC1  //Heater PWM.
#define CHctrl PDC2     //Charge buck PWM.
#define CH_Boost PDC3   //Charge boost PWM.

//IO
#define ANALOG_DIR 0x01FF
#define ANALOG_TRIS TRISB
#define ANALOG_LAT LATB
#define ANALOG_PORT PORTB

#define GENERAL1_DIR 0x1FFF
#define GENERAL1_TRIS TRISC
#define GENERAL1_LAT LATC
#define GENERAL1_PORT PORTC

#define GENERAL2_DIR 0xFF8E
#define GENERAL2_TRIS TRISF
#define GENERAL2_LAT LATF
#define GENERAL2_PORT PORTF

#define GENERAL3_DIR 0xFFF1
#define GENERAL3_TRIS TRISD
#define GENERAL3_LAT LATD
#define GENERAL3_PORT PORTD

#define PWM_TRIS_DIR 0xFFFA
#define PWM_TRIS TRISE
#define PWM_LAT LATE
#define PWM_PORT PORTE

//Memory Defines
/* This assumes the compiler puts the stack at the end of memory space just after
 * the user variables and the stack pointer counts up */
#define ramSize 0x03FF //Size of memory.
#define ramAddressStart 0x0800  //Where the dsPIC30F3011's ram address starts.
#define stackFaultDefault ramSize + ramAddressStart - 1
#define ramFree (ramSize + ramAddressStart) - 15 //Minus 15 bytes of ram. If the stack intrudes on this then it should throw an error code before a complete system crash and undefined behavior.

//General
#define yes 1
#define no 0
#define none 0
#define Debug 3
#define Ballance 2
#define on 1
#define off 0
#define set 1
#define clear 0
#define NULL 0
#define input 1
#define output 0

//Constants
#define Cell_Count 4    //Number of cells placeholder.
#define SOC_Cycles 8
#define AuxFuse 5       //Aux charge port fuse rating placeholder.
#define PreChargeTime 2 //Output pre-charge timer placeholder.
#define LED_Brightness 10
#define V_REF 3.36      //Measured reference voltage placeholder

//Run Levels
#define Shutdown 0
#define Crit_Err 1
#define Heartbeat 2
#define Cal_Mode 3
#define On_W_Err 4
#define All_Sys_Go 5

//Charge Session Levels
#define UnknownStart 0
#define EmptyStart 1
#define FullStart 2

//Heater calibration states.
#define notrun 0
#define initialize 1
#define calibrating 2
#define ready 3
#define error 4
#define disabled 5

//Charger modes.
#define CHError 0
#define Stop 1
#define Wait 2
#define Assignment_Ready 3
#define USB2 4
#define USB3_Wimp 5
#define USB3 6
#define USB3_Fast 7
#define Solar 8
//Charger limits
#define cycleLimit 3

//##############################################################################
#endif


