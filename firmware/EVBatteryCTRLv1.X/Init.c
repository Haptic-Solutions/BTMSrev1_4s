/*  Electric Vehicle Battery Monitoring System.>
    Copyright (C) <2020>  <Jarrett R. Cigainero>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>*/

#ifndef INIT_C
#define INIT_C

#include "common.h"
#include "defines.h"
#include "Init.h"

void default_sets(void){
    sets.R1_resistance = 200;            //R1 resistance in Kohms
    sets.R2_resistance = 16;             //R2 resistance in Kohms
    sets.bt_vlt_adjst = -0.1;            //battery voltage input compensation in volts.
    /*****************************/
    //Battery Ratings and setpoints
    sets.partial_charge = 0.90;            //Percentage of voltage to charge the battery up to. Set to 0 to disable.
    sets.max_battery_voltage = 59.2;      //Max battery voltage before shutdown.
    sets.battery_rated_voltage = 58.8;           //Target max charge voltage
    sets.dischrg_voltage = 47.5;        //Minimum battery voltage
    sets.low_voltage_shutdown = 43;    //Battery Low Total Shutdown Voltage
    sets.dischrg_C_rating = 2;           //Discharge C rating
    sets.limp_current = 5;              //Limp mode current in amps. Minimum current to regulate to.
    sets.chrg_C_rating = 0.5;          //Charge C rating.
    sets.amp_hour_rating = 23.4;         //Battery amp hour rating.
    sets.over_current_shutdown = 30;        //Shutdown current. Sometimes the regulator isn't fast enough and this happens.
    sets.absolute_max_current = 25;      //Max regulating current.
    //Charge temps.
    sets.chrg_min_temp = 10;          //Battery minimum charge temperature. Stop Charging at this temp.
    sets.chrg_reduce_low_temp = 15;      //Reduce charge current when lower than this temp.
    sets.chrg_max_temp = 40;          //Battery max charge temp. Stop charging at this temp.
    sets.chrg_reduce_high_temp = 35; //Reduce charge current when higher than this temp.
    sets.chrg_target_temp = 25;      //Battery heater charge target temp. Keeps us nice and warm in the winter time.
    //Discharge temps.
    sets.dischrg_min_temp = 0;       //Battery minimum discharge temperature.
    sets.dischrg_reduce_low_temp = 10;    //Reduced current discharge low temperature.
    sets.dischrg_max_temp = 55;       //Battery max discharge temperature.
    sets.dischrg_reduce_high_temp = 50;       //Battery reduced discharge high temperature.
    sets.dischrg_target_temp = 15;      //Battery heater discharge target temp. Keeps us nice and warm in the winter time.
    //Shutdown temps.
    sets.battery_shutdown_temp = 60;      //Max battery temp before shutting down everything.
    sets.ctrlr_shutdown_temp = 80;        //Max motor or motor controller temp shutdown.
    //Fan ctrl temps.
    sets.ctrlr_fan_start = 50;          //Turns on cooling fan.
    sets.batt_fan_start = 30;
    //Some other stuff.
    sets.max_heat = 50;              //Heater watts that you want to use.
    sets.travel_dist = 0.012;         //Travel Distance in KM per tire rotation or between TAC ticks.
    sets.circuit_draw = 0.014;        //Amount of current that Yeti himself draws at idle. Used for current calibration and idle mode logging.
    sets.PowerOffAfter = 120;    //Power off the system after this many minutes of not being plugged in or keyed on. 120 minutes is 2 hours.
    //page[2][5][6];              //Display page holder. (PORT)(Page#)(Variable to Display: A '0' at the start = Skip Page)
    //Port 2 display defaults
    sets.custom_data1[0] = 0x12; //Auto Return Off.
    sets.custom_data1[1] = 0x0E; //Cursor Off.
    sets.custom_data1[2] = 0x16; //Cursor Home.
    sets.custom_data1[3] = NULL; //NULL terminator.
    sets.page[PORT2][0][0] = 0xFC;  //Display Init
    sets.page[PORT2][0][1] = 3;  //V 6char
    sets.page[PORT2][0][2] = 8;  //W 7char
    sets.page[PORT2][0][3] = 9;  //BT 7char
    sets.page[PORT2][0][4] = 15; //NEWLINE + RETURN.
    sets.page[PORT2][0][5] = 2;  //%  6char
    sets.page[PORT2][1][0] = 1;  //Speed 6char
    sets.page[PORT2][1][1] = NULL;  //NULL terminator
    sets.pageDelay[PORT2][0] = 0;
    sets.pageDelay[PORT2][1] = 4;   //0.5 seconds.
    sets.pageDelay[PORT2][2] = 0;
    sets.pageDelay[PORT2][3] = 0;
    sets.PxVenable[PORT1] = off;         //Port 1 display out is disabled by default.
    sets.PxVenable[PORT2] = on;         //Port 2 display out is enabled by default.
    sets.testBYTE = 0x3335;
    vars.testBYTE = 0x46;
    ram_chksum_update();        //Generate new checksum.
}
//Configure IO
void configure_IO(void){
    STINGbits.zero_current = 0;
    dsky.peak_power = 0;
    dsky.peak_pwr_vlts = 0;
    dsky.peak_pwr_crnt = 0;
    /*****************************/
    //Battery Sensor Input
    dsky.battery_temp = 0;           //Battery Temperature
    dsky.my_temp = 0;                //Controller board Temperature
    dsky.motor_ctrl_temp = 0;         //Motor or Motor controller Temperature
    dsky.battery_voltage = 0;        //Battery voltage
    open_voltage = 0;           //Battery Open Circuit Voltage
    voltage_percentage = 0;     //Battery Voltage Percentage.
    CONDbits.got_open_voltage = 0;
    dsky.battery_current = 0;        //Battery charge/discharge current
    
    /**************************/
    /* Osc Config*/
    OSCCONbits.NOSC = 1;
    OSCCONbits.OSWEN = 1;
    OSCCONbits.LPOSCEN = 0;
    /**************************/
    //Disable IRQ on change
    CNEN1 = 0;
    CNEN2 = 0;
    //Disable IRQ on change pullups
    CNPU1 = 0;
    CNPU2 = 0;
    /**************************/
    /* General 1 IO */
    GENERAL1_TRIS = 0x0000;
    GENERAL1_LAT = 0;
    GENERAL1_PORT = 0;
    /**************************/
    /* PWM outputs and charge detect input. */
    PWM_TRIS = 0xFFEF; //set porte to all inputs except RE4
    PWM_LAT = 0;
    PWM_PORT = 0;      //Make sure PORTE is 0
    /**************************/
    /* General 2 IO */
    GENERAL2_TRIS = 0xFFBE;
    GENERAL2_LAT = 0;
    GENERAL2_PORT = 0;
/*****************************/
/* Configure PWM */
/*****************************/
    //FBORPOR = 0x82B2;
    PTCON = 0x0006;     //Set the PWM module and set to up/down mode for center aligned PWM. 6 = 37khz (4 Tcy per bit))
    PTMR = 0;
    PTPER = 49;         //set period. 0% - 99%
    SEVTCMP = 0;
    PWMCON1 = 0x00FB;       //Set PWM output for complementary mode.
    PWMCON2 = 0x0000;
    DTCON1 = 0x8181;        //Dead time is 4Tcy (1 bit)
    FLTACON = 0;
    OVDCON = 0xFF00;
    PDC1 = 0000;            //set output to 0
    PDC2 = 0000;            //set output to 0
    PDC3 = 0000;            //set output to 0

/*****************************/
/* Configure UARTs */
/*****************************/
    //PORT 1 setup
    U1STA = 0;
    U1STAbits.UTXISEL = 0;
    U1MODE = 0;
    U1MODEbits.ALTIO = 1;           //Use alternate IO for UART1.
    U1BRG = BaudCalc(BAUD1, IPS);     //calculate the baud rate.
    //Default power up of UART should be 8n1

    //PORT 2 setup
    U2STA = 0;
    U2STAbits.UTXISEL = 0;
    U2MODE = 0;
    U2BRG = BaudCalc(BAUD2, IPS);     //calculate the baud rate.
    //Default power up of UART should be 8n1
/*****************************/
/* Configure Timer 1 */
/* Scan IO every second when KeySwitch is off. */
/*****************************/
/* Timer one CTRL. */
    PR1 = 0xE0EA;
    TMR1 = 0x0000;
    T1CON = 0x0000;
    T1CONbits.TCKPS = 3;        //1:256 prescale

/*****************************/
/* Configure Timer 2 */
/*****************************/
/* For 0.125 second timing operations. */
    //PR2 = 0xE4E2;   //58,594
    //PR2 = 0x7075;     //28,789
    PR2 = 0x383A;     //14,394
    TMR2 = 0x0000;
    T2CON = 0x0000;
    T2CONbits.TCKPS = 2;        //1:64 prescale

/*****************************/
/* Configure Timer 3 */
/*For speed calculation. */
/*****************************/
/* For exactly 1 second timing operations. */
    PR3 = 0xE0EA;   //57,578
    //PR3 = 0x7271;     //29,297
    TMR3 = 0x0000;
    T3CON = 0x0000;
    T3CONbits.TCKPS = 3;        //1:256 prescale

/*****************************/
/* Configure Timer 4 */
/* Non-Critical Timing. */
/*****************************/
/* For low priority 1 second timing operations. */
    PR4 = 0xE0EA;   //57,578
    //PR3 = 0x7271;     //29,297
    TMR4 = 0x0000;
    T4CON = 0x0000;
    T4CONbits.TCKPS = 3;        //1:256 prescale
    
/*****************************/
/* Configure Timer 5 */
/*****************************/
/* For low priority 0.125 second timing operations. */
    PR5 = 0x383A;     //14,394
    TMR5 = 0x0000;
    T5CON = 0x0000;
    T5CONbits.TCKPS = 2;        //1:64 prescale

/*****************************/
/* Configure and Enable analog inputs */
/*****************************/
    ADCON3upper8 = 0x0F;
    ADCON3lower8 = 0x0F;
    analog_smpl_time = 1 / (((IPS * 1000000) / (ADCON3upper8 + ADCON3lower8)) / 45);
    ADCON1 = 0x02E4;
    ADCON2 = 0x0410;
    ADCON3 = 0x0F0F;
    ADCHS = 0x0000;
    ADPCFG = 0xFF70;
    ADCSSL = 0x008F;

    //Configure IRQ Priorities
    IPC2bits.ADIP = 7;      //Analog inputs and regulation routines, Most Important.
    IPC1bits.T2IP = 6;      //0.125 second IRQ for some math timing, Greater priority.
    IPC4bits.INT1IP = 5;    //Wheel rotate IRQ, timing is somewhat important.
    IPC0bits.T1IP = 4;      //Heartbeat IRQ, eh, not terribly important.
    IPC5bits.T5IP = 4;      //0.125 Sec Non-critical. Used for HUD, not important for system functionality.
    IPC2bits.U1TXIP = 3;    //TX 1 IRQ, Text can wait
    IPC6bits.U2TXIP = 3;    //TX 2 IRQ, Text can wait
    IPC2bits.U1RXIP = 2;    //RX 1 IRQ, Text can wait
    IPC6bits.U2RXIP = 2;    //RX 2 IRQ, Text can wait
    IPC1bits.T3IP = 2;      //Timer 3 IRQ for wheel rotate timeout. Not critical.
    IPC0bits.INT0IP = 1;    //Charger detect IRQ, only for waking up the system.
    IPC5bits.T4IP = 1;      //1 Sec Checksum timer IRQ, CPU intensive and other's need more priority.
    IPC5bits.INT2IP = 1;    //Not yet used.
}
void Init(void){
/*******************************
 * initialization values setup.
*******************************/
    //Configure stack overflow catch address.
    SPLIM = ramFree; //This should be updated according to how much ram is being used by all variables.
    //Calculate our voltage divider values.
    vltg_dvid = sets.R2_resistance / (sets.R1_resistance + sets.R2_resistance);
    //We've done Init.
    STINGbits.init_done = 1;
    //We aren't in low power mode
    STINGbits.lw_pwr = 0;
    //Calculate max charge current.
    max_chrg_current = sets.chrg_C_rating * sets.amp_hour_rating;
    //Configure the inputs, outputs, and device.
    configure_IO();

/*****************************/
/* Configure IRQs. */
/*****************************/
    
    //Ensure interrupt nesting is enabled.
    INTCON1bits.NSTDIS = 0; //This should be the default state on chip reset.
    // Clear all interrupts flags
    IFS0 = 0;
    IFS1 = 0;
    IFS2 = 0;

	// enable interrupts
	__asm__ volatile ("DISI #0x3FFF");  //First disable IRQs via instruction.
    IEC0 = 0;
    IEC1 = 0;
    IEC2 = 0;
	IEC0bits.T1IE = 1;	// Enable interrupts for timer 1
    IEC0bits.U1RXIE = 1; //Enable interrupts for UART1 Rx.
    IEC0bits.U1TXIE = 1; //Enable interrupts for UART1 Tx.
    IEC1bits.U2RXIE = 1; //Enable interrupts for UART2 Rx.
    IEC1bits.U2TXIE = 1; //Enable interrupts for UART2 Tx.
    IEC0bits.INT0IE = 1;    //Charge Detect IRQ
    CONDbits.EnableChIRQ = 1;    //By default, enable charge detect IRQ on init.
    IEC1bits.INT1IE = 1;    //Wheel rotate IRQ
    IEC1bits.INT2IE = 0;  //Disable irq for INT2, not used.
    IEC0bits.T2IE = 1;	// Enable interrupts for timer 2
    IEC0bits.T3IE = 1;	// Enable interrupts for timer 3
    IEC1bits.T4IE = 1;	// Enable interrupts for timer 4
    IEC1bits.T5IE = 1;	// Enable interrupts for timer 5
    IEC0bits.ADIE = 1;  // Enable ADC IRQs.
    INTCON2bits.INT0EP = 0;
    INTCON2bits.INT2EP = 0;
    DISICNT = 0;
/*****************************/
/* Enable our devices. */
/*****************************/
    ADCON1bits.ADON = 1;    // turn ADC ON
    PTCONbits.PTEN = 1;     // Enable PWM
    T2CONbits.TON = 1;      // Start Timer 2
    T1CONbits.TON = 1;      // Start Timer 1
    T3CONbits.TON = 1;      // Start Timer 3
    T4CONbits.TON = 1;      // Start Timer 4
    T5CONbits.TON = 1;      // Start Timer 5
    U1MODEbits.UARTEN = 1;  //enable UART1
    U1STAbits.UTXEN = 1;    //enable UART1 TX
    U2MODEbits.UARTEN = 1;  //enable UART2
    U2STAbits.UTXEN = 1;    //enable UART2 TX
/* End Of Initial Config stuff. */
}
void sys_debug(void){
    configure_IO();
    __asm__ volatile ("DISI #0x3FFF");  //First disable IRQs via instruction.
    // Clear all interrupts flags
    IFS0 = 0;
    IFS1 = 0;
    IFS2 = 0;
	// enable or Disable select interrupts
    IEC0 = 0;
    IEC1 = 0;
    IEC2 = 0;
    IEC0bits.U1RXIE = 1; //Enable interrupts for UART1 Rx.
    IEC0bits.U1TXIE = 1; //Enable interrupts for UART1 Tx.
    IEC1bits.U2RXIE = 1; //Enable interrupts for UART2 Rx.
    IEC1bits.U2TXIE = 1; //Enable interrupts for UART2 Tx.
    DISICNT = 0;
/*****************************/
/* Disable our devices. */
/*****************************/
    ADCON1bits.ADON = 0;    // Disable ADC
    PTCONbits.PTEN = 0;     // Disable PWM
    T2CONbits.TON = 0;      // Disable Timer 2
    T1CONbits.TON = 0;      // Disable Timer 1
    T3CONbits.TON = 0;      // Disable Timer 3
    T4CONbits.TON = 0;      // Disable Timer 4
    T5CONbits.TON = 0;      // Disable Timer 5
    U1MODEbits.UARTEN = 1;  //enable UART1
    U1STAbits.UTXEN = 1;    //enable UART1 TX
    U2MODEbits.UARTEN = 1;  //enable UART2
    U2STAbits.UTXEN = 1;    //enable UART2 TX
/* End Of Initial Config stuff. */
}

//Go in to low power mode when not in use.
void low_power_mode(void){
    io_off();
    ADCON1bits.ADON = 0;    // turn ADC off
    T2CONbits.TON = 0;      // Stop Timer 2
    T3CONbits.TON = 0;      // Stop Timer 3
    T4CONbits.TON = 0;      // Stop Timer 4
    T5CONbits.TON = 0;      // Stop Timer 5
    // disable interrupts
    IEC1bits.INT1IE = 0;    //disable Wheel rotate IRQ
    IEC0bits.T2IE = 0;      //disable interrupts for timer 2
    IEC0bits.T3IE = 0;	// Disable interrupts for timer 3
    IEC1bits.T4IE = 0;	// Disable interrupts for timer 4
    IEC1bits.T5IE = 0;	// Disable interrupts for timer 5
    INTCON2bits.INT1EP = 0;
    INTCON2bits.INT2EP = 0;
    //Set check_timer to just a few seconds before check.
    check_timer = 0x0700;
    //Need to reinit on restart
    STINGbits.init_done = 0;
    //Tell everyone we are in low power mode.
    STINGbits.lw_pwr = 1;
}

/* Turn everything off so we don't waste any more power.
 * Only plugging in the charge will restart the CPU, or yaknow, just restart the CPU... */
void low_battery_shutdown(void){
    CONDbits.cmd_power = 0;
    CONDbits.soft_power = 0;
    PTCONbits.PTEN = 0;     // Turn off PWM
    T1CONbits.TON = 0;      // Stop Timer 1
    // Clear all interrupts flags
    IFS0 = 0;
    IFS1 = 0;
    IFS2 = 0;
    	// disable interrupts
	__asm__ volatile ("DISI #0x3FFF");
	IEC0bits.T1IE = 0;	// disable interrupts for timer 1
    IEC0bits.ADIE = 0;  //disable ADC IRQs.
    INTCON2bits.INT1EP = 0;
    INTCON2bits.INT2EP = 0;
    low_power_mode();
    STINGbits.deep_sleep = 1;     //Tell the system to enter a deep sleep after we have completed all tasks one last time.
}

#endif
