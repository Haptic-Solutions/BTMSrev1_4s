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

#ifndef INIT_C
#define INIT_C

#include "common.h"
#include "defines.h"
#include "Init.h"

void default_sets(void){
    /* Each analog voltage input uses a 10K resistor over a 1K resistor.
     * Both rated for 0.1% tolerance and are physically close to each other
     * to minimize thermal drift. */
    sets.R1_resistance = 10;            //R1 resistance in Kohms
    sets.R2_resistance = 1;             //R2 resistance in Kohms
    sets.S_vlt_adjst[0] = 0.204;        //These values are added to each analog input BEFORE individual cell voltages are calculated.
    sets.S_vlt_adjst[1] = 0.152;
    sets.S_vlt_adjst[2] = 0.111;
    sets.S_vlt_adjst[3] = 0.014;
    sets.Ch_vlt_adjst = 0.177;          //Gets added to charge input voltage.
    /*****************************/
    //Battery Ratings and setpoints
    sets.partial_charge = 0.90;            //Percentage of voltage to charge the battery up to. Set to 0 to disable.
    sets.absolute_max_cell_voltage = 4.28;      //Max battery voltage before lockout.
    sets.cell_rated_voltage = 4.2;     //Target max charge voltage
    sets.dischrg_voltage = 3.5;         //Minimum battery voltage
    sets.low_voltage_shutdown = 2.4;    //Battery Low lockout voltage
    sets.dischrg_C_rating = 2;           //Discharge C rating
    sets.limp_current = 1;              //Limp mode current in amps. Minimum current to regulate to.
    sets.chrg_C_rating = 1;          //Charge C rating.
    sets.amp_hour_rating = 2.6;         //Battery amp hour rating.
    sets.over_current_shutdown = 8;        //Shutdown current. Sometimes the regulator isn't fast enough and this happens.
    sets.absolute_max_current = 8.5;      //Max regulating current.
    /**************************************/
    sets.auto_off_watts = 0.5;       //Minimum amount of power draw to start the auto power off timer.
    // Battery thermocouple
    sets.res_at_25 = 10;                  //resistance at 25C in Kohms
    sets.temp_coefficient = -4.4;           //temperature coefficient in deg.
    sets.cycles_to_80 = 2000;           //Number of charge cycles to 80% capacity.
    //Charge temps.
    sets.chrg_min_temp = 10;          //Battery minimum charge temperature. Stop Charging at this temp.
    sets.chrg_reduce_low_temp = 15;      //Reduce charge current when lower than this temp.
    sets.chrg_max_temp = 50;          //Battery max charge temp. Stop charging at this temp.
    sets.chrg_reduce_high_temp = 45; //Reduce charge current when higher than this temp.
    sets.chrg_target_temp = 25;      //Battery heater charge target temp. Keeps us nice and warm in the winter time.
    //Discharge temps.
    sets.dischrg_min_temp = 0;       //Battery minimum discharge temperature.
    sets.dischrg_reduce_low_temp = 10;    //Reduced current discharge low temperature.
    sets.dischrg_max_temp = 60;       //Battery max discharge temperature.
    sets.dischrg_reduce_high_temp = 55;       //Battery reduced discharge high temperature.
    sets.dischrg_target_temp = 15;      //Battery heater discharge target temp. Keeps us nice and warm in the winter time.
    //Shutdown temps.
    sets.battery_shutdown_temp = 65;      //Max battery temp before shutting down everything.
    sets.ctrlr_shutdown_temp = 80;        //Max BMS temp before shutdown.
    //Some other stuff.
    sets.max_heat = 3;              //Heater watts that you want to use.
    sets.DeepSleepAfter = 60;    //Deep Sleep the system after this many minutes of not being plugged in or keyed on.
    sets.PowerOffAfter = 1;     //Power off the output after this many minutes when power off wattage is below set amount or 0. 
    sets.Cell_Count = -1;       //Uninitialized cell count.
    sets.PWR_SW_MODE = push_and_hold;
    //page[2][5][6];              //Display page holder. (PORT)(Page#)(Variable to Display: A '0' at the start = Skip Page)
    vars.testBYTE = 0x46;
    vars.heat_cal_stage = disabled;
    for(int i=0;i<4;i++)OV_Timer[i]=0;
        //page[2][5][6];              //Display page holder. (PORT)(Page#)(Variable to Display: A '0' at the start = Skip Page)
    //Port 1 display defaults
    sets.page[PORT1][0][0] = 0x01;  //Battery %
    sets.page[PORT1][0][1] = 0x08;  //S1
    sets.page[PORT1][0][2] = 0x09;  //S2
    sets.page[PORT1][0][3] = 0x0A;  //S3
    sets.page[PORT1][0][4] = 0x0B;  //S4
    sets.page[PORT1][0][5] = 0x0C;  //Watts
    sets.page[PORT1][1][0] = 0x14;  //New Line
    sets.page[PORT1][1][1] = 0x00;  //NULL terminator
    sets.pageDelay[PORT1][0] = 0;
    sets.pageDelay[PORT1][1] = 4;   //0.5 seconds.
    sets.pageDelay[PORT1][2] = 0;
    sets.pageDelay[PORT1][3] = 0;
    sets.page[PORT2][0][0] = 0x01;  //Battery %
    sets.page[PORT2][0][1] = 0x08;  //S1
    sets.page[PORT2][0][2] = 0x09;  //S2
    sets.page[PORT2][0][3] = 0x0A;  //S3
    sets.page[PORT2][0][4] = 0x0B;  //S4
    sets.page[PORT2][0][5] = 0x0C;  //Watts
    sets.page[PORT2][1][0] = 0x14;  //New Line
    sets.page[PORT2][1][1] = 0x00;  //NULL terminator
    sets.pageDelay[PORT2][0] = 0;
    sets.pageDelay[PORT2][1] = 4;   //0.5 seconds.
    sets.pageDelay[PORT2][2] = 0;
    sets.pageDelay[PORT2][3] = 0;
    sets.PxVenable[PORT1] = off;         //Port 1 display out is disabled by default.
    sets.PxVenable[PORT2] = off;         //Port 2 display out is enabled by default.
    ram_chksum_update();        //Generate new checksum.
}
//Configure IO
void configure_IO(void){
    STINGbits.zero_current = 0;
    dsky.peak_power = 0;
    /*****************************/
    //Battery Sensor Input
    dsky.battery_temp = 0;           //Battery Temperature
    dsky.my_temp = 0;                //Controller board Temperature
    dsky.pack_voltage = 0;        //Battery voltage
    for(int i=0;i<sets.Cell_Count;i++)open_voltage_percentage[i] = 0;     //Battery Voltage Percentage.
    dsky.battery_current = 0;        //Battery charge/discharge current
    CONDbits.Port1_Echo=yes;
    CONDbits.Port2_Echo=yes;
    /**************************/
    /* Osc Config*/
    OSCCONbits.NOSC = 1;
    OSCCONbits.POST = 0;
    OSCCONbits.LPOSCEN = 0;
    OSCCONbits.OSWEN = 1;
    /**************************/
    //Disable IRQ on port change.
    CNEN1 = 0;
    CNEN2 = 0;
    //Disable IRQ on port change pullup resistors.
    CNPU1 = 0;
    CNPU2 = 0;
    /**************************/
    /* General 1 IO */
    GENERAL1_TRIS = GENERAL1_DIR;
    GENERAL1_LAT = 0;
    GENERAL1_PORT = 0;
    /**************************/
    
    /**************************/
    /* General 3 IO. */
    GENERAL3_TRIS = GENERAL3_DIR;
    GENERAL3_LAT = 0;
    GENERAL3_PORT = 0;
    /* PWM outputs. */
    PWM_TRIS = PWM_TRIS_DIR;
    PWM_LAT = 0;
    PWM_PORT = 0;
/*****************************/
/* Configure PWM */
/*****************************/
    PTCON = 0x0000;     //Set the PWM module and set to free running mode for edge aligned PWM, and pre-scale divide by 2
    PTMR = 0;
    PTPER = PWM_Period;         //set period. 0% - 99%
    SEVTCMP = 0;
    PWMCON1 = 0x0070;           //Set PWM output for single mode.
    PWMCON2 = 0x0000;
    DTCON1 = 0x0000;        //0 Dead time. Not needed.
    FLTACON = 0;
    OVDCON = 0x2A00;        //Only high-side PWM pins are being used for PWM.
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
    //U1MODEbits.WAKE = 1;
    U1BRG = BaudCalc(BAUD1, IPS);     //calculate the baud rate.
    //Default power up of UART should be 8n1

    //PORT 2 setup
    U2STA = 0;
    U2STAbits.UTXISEL = 0;
    U2MODE = 0;
    //U2MODEbits.WAKE = 1;
    U2BRG = BaudCalc(BAUD2, IPS);     //calculate the baud rate.
    //Default power up of UART should be 8n1
    
/*****************************/
/* Configure I2C */
/*****************************/
    I2CCON = 0;
    I2CBRG = 0x1FF; //Speed not too critical. As long as it's within specs.
/*****************************/
//Timer configs at 58,960,000 hz
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
    PR2 = 0x7074;     //28788
    TMR2 = 0x0000;
    T2CON = 0x0000;
    T2CONbits.TCKPS = 2;  //1:64 prescale

/*****************************/
/* Configure Timer 3 */
/* idk, blink some lights or smth */
/*****************************/
/* For 1/16 second timing operations. */
    PR3 = 0x383A;     //14398
    TMR3 = 0x0000;
    T3CON = 0x0000;
    T3CONbits.TCKPS = 2;        //1:256 prescale

/*****************************/
/* Configure Timer 4 */
/* Non-Critical 1S Timing. */
/*****************************/
/* For low priority 1 second timing operations. */
    PR4 = 0xE0EA;   //57,578
    TMR4 = 0x0000;
    T4CON = 0x0000;
    T4CONbits.TCKPS = 3;        //1:256 prescale

/*****************************/
/* Configure Timer 5 */
/*****************************/
/* For low priority 1/16th second timing operations. */
    PR5 = 0x383A;     //14398
    TMR5 = 0x0000;
    T5CON = 0x0000;
    T5CONbits.TCKPS = 2;        //1:64 prescale

/*****************************/
/* Configure and Enable analog inputs */
/*****************************/
    ADCON1 = 0x02E4;
    //ADCON2 = 0x0410;
    ADCON2 = 0x0424;
    ADCON3 = 0x0980;    //A/D internal RC clock
    //ADCON3 = 0x0900;    //A/D system clock
    ADCHS = 0x0000;
    ADPCFG = 0xFE00;
    ADCSSL = 0x01FF;

    //Configure IRQ Priorities
    IPC2bits.ADIP = 7;      //Analog inputs and regulation routines, Important.
    IPC0bits.INT0IP = 6;    //Over voltage IRQ.
    IPC4bits.INT1IP = 6;    //Over current IRQ.
    IPC1bits.T2IP = 6;      //0.125 second IRQ for some math timing, Greater priority.
    IPC3bits.MI2CIP = 5;    //I2C Master IRQ has to stay lower priority than T2IRQ but higher than heartbeat
    IPC0bits.T1IP = 4;      //Heartbeat IRQ, eh, not terribly important.
    IPC3bits.SI2CIP = 4;    //I2C Slave IRQ
    IPC1bits.T3IP = 4;      //Blink some lights
    IPC2bits.U1TXIP = 3;    //TX 1 IRQ, Text can wait
    IPC6bits.U2TXIP = 3;    //TX 2 IRQ, Text can wait
    IPC2bits.U1RXIP = 2;    //RX 1 IRQ, Text can wait
    IPC6bits.U2RXIP = 2;    //RX 2 IRQ, Text can wait
    IPC5bits.T5IP = 2;      //0.125 Sec Non-critical. Used for HUD.
    IPC5bits.T4IP = 1;      //1 Sec Checksum timer IRQ and power off timer.
    IPC5bits.INT2IP = 1;    //Not used.
}

void Init(void){
/*******************************
 * initialization values setup.
*******************************/
    //Clear command buffer(s)
    for(int i=0;i<Clength;i++)CMD_buff[PORT1][i]=' ';
    for(int i=0;i<Clength;i++)CMD_buff[PORT2][i]=' ';
    //Configure stack overflow catch address.
    SPLIM = ramFree;
    //Calculate our voltage divider value(s).
    resistor_divide_const = sets.R2_resistance / (sets.R1_resistance + sets.R2_resistance);
    //Calculate reference values
    Half_ref = V_REF/2;
    analog_const = (65535*sample_Average)/V_REF;
    //We aren't in low power mode
    STINGbits.lw_pwr_init_done = 0;
/*****************************/
/* Configure IRQs. */
/*****************************/

    //Ensure interrupt nesting is enabled.
    INTCON1bits.NSTDIS = 0; //This should be the default state on chip reset.
    // Clear all interrupts flags
    IFS0 = 0;
    IFS1 = 0;
    IFS2 = 0;

	// enable select interrupts
	__asm__ volatile ("DISI #0x3FFF");  //First disable IRQs via instruction.
    IEC0 = 0;
    IEC1 = 0;
    IEC2 = 0;
    IEC0bits.MI2CIE = 1;	// Enable interrupts for I2C master
    IEC0bits.SI2CIE = 1;	// Enable interrupts for I2C slave
	IEC0bits.T1IE = 1;	// Enable interrupts for timer 1
    IEC0bits.U1RXIE = 1; //Enable interrupts for UART1 Rx.
    IEC0bits.U1TXIE = 1; //Enable interrupts for UART1 Tx.
    IEC1bits.U2RXIE = 1; //Enable interrupts for UART2 Rx.
    IEC1bits.U2TXIE = 1; //Enable interrupts for UART2 Tx.           //We use this space to store a unique ID to indicate if the EEPROM has been written to at least once.
    IEC0bits.INT0IE = 1;    //Battery Over Voltage IRQ
    IEC1bits.INT1IE = 1;    //Current sense fault IRQ
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
    USB_Power_Present_Check(); //Enable or Disable PORT1 depending if there is voltage present to FTDI chip.
    U2MODEbits.UARTEN = 1;  //enable UART2
    U2STAbits.UTXEN = 1;    //enable UART2 TX
    //We've done Init.
    STINGbits.init_done = 1;
/* End Of Initial Config stuff. */
}
void init_sys_debug(void){
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
    IEC1bits.T4IE = 1;	// Enable interrupts for timer 4
    DISICNT = 0;
    CONDbits.IRQ_RESTART = 1;
/*****************************/
/* Disable our devices except T4 and serial ports. */
/*****************************/
    //ADCON1bits.ADON = 0;    // Disable ADC
    PTCONbits.PTEN = 0;     // Disable PWM
    T2CONbits.TON = 0;      // Disable Timer 2
    T1CONbits.TON = 0;      // Disable Timer 1
    T3CONbits.TON = 0;      // Disable Timer 3
    //T4CONbits.TON = 1;      // Disable Timer 4
    T5CONbits.TON = 0;      // Disable Timer 5
    USB_Power_Present_Check(); //Enable or Disable PORT1 depending if there is voltage present to FTDI chip.
    U2MODEbits.UARTEN = 1;  //enable UART2
    U2STAbits.UTXEN = 1;    //enable UART2 TX
/* End Of Initial Config stuff. */
}

//Go in to low power mode when not in use.
void low_power_mode(void){
    Batt_IO_OFF();
    T3CONbits.TON = 0;      // Stop Timer 3
    T5CONbits.TON = 0;      // Stop Timer 5
    // disable interrupts
    IEC0bits.T3IE = 0;	// Disable interrupts for timer 3
    IEC1bits.T5IE = 0;	// Disable interrupts for timer 5
    INTCON2bits.INT1EP = 0;
    INTCON2bits.INT2EP = 0;
    //Set check_timer to 10 seconds before check on startup.
    check_timer = 1790;
    //Need to reinit on restart
    STINGbits.init_done = 0;
    //Tell everyone we are in low power mode.
    STINGbits.lw_pwr_init_done = 1;
}

/* Turn everything off so we don't waste any more power.
 * Only plugging in the charge will restart the CPU, or yaknow, just restart the CPU... */
void low_battery_shutdown(void){
    Run_Level = Shutdown;
    ADCON1bits.ADON = 0;    // turn ADC off
    PTCONbits.PTEN = 0;     // Turn off PWM
    // Clear all interrupts flags
    IEC0bits.ADIE = 0;  //disable ADC IRQs.
    INTCON2bits.INT1EP = 0;
    INTCON2bits.INT2EP = 0;
    low_power_mode();
    STINGbits.deep_sleep = 1;     //Tell the system to enter a deep sleep after we have completed all tasks one last time.
}

#endif
