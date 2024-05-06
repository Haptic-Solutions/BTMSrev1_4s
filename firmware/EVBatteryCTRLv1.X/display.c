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

#ifndef DKSY_C
#define DKSY_C

#include "common.h"
#include "display.h"
#include "DataIO.h"
#include "errorCodes.h"
#include "eeprom.h"
#include "checksum.h"



void C_Point_CHK(int serial_port){
    serial_port = port_Sanity(serial_port);
    if(CMD_Point[serial_port] < 0)CMD_Point[serial_port]=0;
    if(CMD_Point[serial_port] >= Clength)CMD_Point[serial_port]=0;
}

//Loads one of the serial buffers with user defined data and then dispatches it.
void pageOut(int pageNum, int serial_port){
    serial_port = port_Sanity(serial_port);
    dodispatch[serial_port] = no;
    for(pageVar[serial_port]=0;pageVar[serial_port]<6;pageVar[serial_port]++){
        varNum[serial_port] = sets.page[serial_port][pageNum][pageVar[serial_port]];
        varNum[serial_port] &= 0xFF;
        if(varNum[serial_port] < signStart)dynaSpace[serial_port] = yes;       //Do not reserve a space for a sign char if we don't have to.
        if(varNum[serial_port] == wattsNum)config_space[serial_port] = yes;   //Reserve spaces for 0's when showing watts so that text isn't jumping around.
        //Skip page if first Var is listed as NULL, or if we get a NULL later then we are done.
        if(varNum[serial_port] == 0)break;
        //Check if loading custom data or not.
        if(varNum[serial_port] > 0x00FB){
            switch(varNum[serial_port]){
                case 0x00FC:
                    load_string(sets.custom_data1, serial_port);
                break;
                case 0x00FD:
                    load_string(sets.custom_data2, serial_port);
                break;
                case 0x00FE:
                    load_string(sets.custom_data3, serial_port);
                break;
                case 0x00FF:
                    load_string(sets.custom_data4, serial_port);
                break;
            }
            dodispatch[serial_port] = yes; //if we have at least one variable to display then dispatch.
        }
        else if(varNum[serial_port] == nlNum){
            load_string("\n\r", serial_port);
            dodispatch[serial_port] = yes; //if we have at least one variable to display then dispatch.
        }
        else if(varNum[serial_port] < varLimit){
            if(varNum[serial_port] != nlNum)load_float(0.01+dsky.dskyarrayFloat[varNum[serial_port]], serial_port);   //Load the number.
            Buff_index[serial_port] -= 2;  //Subtract 2 from buffer index.
            load_const_string(Vlookup[varNum[serial_port]], serial_port);        //Load the number's text.
            load_string(" ", serial_port);  //Load a space after everything.
            dodispatch[serial_port] = yes; //if we have at least one variable to display then dispatch.
        }
    }
    if (dodispatch[serial_port]){
        dispatch_Serial(serial_port);
    }
}

void displayOut(int serial_port){
    serial_port = port_Sanity(serial_port);
    if(sets.PxVenable[serial_port] && !portBSY[serial_port] && Run_Level == All_Sys_Go){
        if(PxVtimer[serial_port] == 0){
            pageOut(PxPage[serial_port], serial_port);
            PxVtimer[serial_port] = sets.pageDelay[serial_port][PxPage[serial_port]] - 1;
            if (PxVtimer[serial_port] < 0) PxVtimer[serial_port] = 0;
            if(PxPage[serial_port] < 4 && sets.page[serial_port][PxPage[serial_port]][0]) PxPage[serial_port]++; //If we get a NULL for first variable then skip go back to page 0
            else PxPage[serial_port] = 0;
        }
        else PxVtimer[serial_port]--;
    }
}

/* Read fault codes to serial port.
 * This takes up about 2% of program space.*/
void fault_read(int serial_port){
    serial_port = port_Sanity(serial_port);
    send_string("\n\rReading Faults.\n\r", serial_port);
    if(vars.fault_count > maxFCodes){
        send_string("Fault Log Full.\n\r", serial_port);
    }
    if(vars.fault_count == 0){
        send_string("No fault codes.\n\r", serial_port);
    }
    else{
        for(flt_index[serial_port]=0;flt_index[serial_port]<vars.fault_count;flt_index[serial_port]++){
            portBusyIdle(serial_port);  //Check to see if port is ready.
            load_string("Code: ", serial_port);
            load_hex(vars.fault_codes[0][flt_index[serial_port]],serial_port);
            load_string(" :: Attribute: ", serial_port);
            load_hex(vars.fault_codes[1][flt_index[serial_port]], serial_port);
            load_string(" -> ", serial_port);
            int ecode = vars.fault_codes[0][flt_index[serial_port]];
            if(!ecode || ecode < sizeof(errArray))load_const_string(errArray[ecode-1], serial_port);
            else load_const_string(codeDefault, serial_port);
            send_string("\n\r", serial_port);
        }
    }
    portBusyIdle(serial_port);
    send_string("\n\r", serial_port);
    send_string("Flags::|Sets LK||Batt OV||Batt HV|", serial_port);
    send_string("|Batt UV||Batt OT||Sys OT|\n\r", serial_port);
    send_string("        ", serial_port);
    unsigned char flagMask = 0x01;
    for(int i=0;i<6;i++){
        if(Flags&flagMask)load_string("SET      ", serial_port);
        else load_string("Clear    ", serial_port);
        flagMask*=2; //Shift the bit left by one.
    }
    send_string("\n\r", serial_port);
}

void send_Int_Array(int* data, int start, int end, int serial_port){
    serial_port = port_Sanity(serial_port);
    send_string("  ",serial_port);
    for(int i=start;i<=end;i++){
        load_float(data[i], serial_port);
        load_string("  ",serial_port);
    }
    send_string("\n\r",serial_port);
}

void send_Float_Array(float* data, int start, int end, int serial_port){
    serial_port = port_Sanity(serial_port);
    send_string("  ",serial_port);
    for(int i=start;i<=end;i++){
        load_float(data[i], serial_port);
        load_string("  ",serial_port);
    }
    send_string("\n\r",serial_port);
}

void all_info(int serial_port){
    serial_port = port_Sanity(serial_port);
    send_string("\n\r", serial_port);
    /* Settings FLOAT variables. */
    send_string("System Settings::\n\r", serial_port);
    send_string("1: |R1|      |R2|     |S1C|    |S2C|     |S3C|    |S4C|\n\r", serial_port);
    send_Float_Array(sets.settingsFloat, 1, 6, serial_port);
    send_string("\n\r", serial_port);
    send_string("2: |PC|      |MBV|    |BRV|    |DV|      |LVS|    |DCR|\n\r", serial_port);
    send_Float_Array(sets.settingsFloat, 7, 12, serial_port);
    send_string("\n\r", serial_port);
    send_string("3: |LC|      |CCR|    |AHR|    |OCS|    |AMC|\n\r", serial_port);
    send_Float_Array(sets.settingsFloat, 13, 17, serial_port);
    send_string("\n\r", serial_port);
    /*Settings INT variables. */
    send_string("4: |CT80|      |CmT|    |CRL|    |CMXT|    |CRH|    |CTT|\n\r", serial_port);
    send_Int_Array(sets.settingsINT, 1, 6, serial_port);
    send_string("\n\r", serial_port);
    send_string("5: |DmT|    |DRL|    |DMXT|    |DRH|    |DTT|\n\r", serial_port);
    send_Int_Array(sets.settingsINT, 7, 11, serial_port);
    send_string("\n\r", serial_port);
    send_string("6: |BST|    |CST|    |MHT|    |POA|\n\r", serial_port);
    send_Int_Array(sets.settingsINT, 12, 15, serial_port);
    send_string("\n\r***********\n\r", serial_port);
    send_string("Display::\n\r", serial_port);
    send_string("1: |B%|      |PV|     |TV|    |PW|     |AV|\n\r", serial_port);
    send_Float_Array(dsky.dskyarrayFloat, 1, 5, serial_port);
    send_string("\n\r", serial_port);
    send_string("2: |CV|      |CA|\n\r", serial_port);
    send_Float_Array(dsky.dskyarrayFloat, 6, 7, serial_port);
    send_string("\n\r", serial_port);
    send_string("3: |S1|    |S2|     |S3|    |S4|\n\r", serial_port);
    send_Float_Array(Cell_Voltage_Average, 0, 3, serial_port);
    send_string("\n\r", serial_port);
    send_string("4: |W|      |CW|     |A|    |CB|\n\r", serial_port);
    send_Float_Array(dsky.dskyarrayFloat, 12, 15, serial_port);
    send_string("\n\r", serial_port);
    send_string("5: |CM|      |AA|     |OCV|    |MC|\n\r", serial_port);
    send_Float_Array(dsky.dskyarrayFloat, 16, 19, serial_port);
    send_string("\n\r Cell Config: ", serial_port);
    load_float(sets.Cell_Count, serial_port);
    send_string("\n\r Ah Rating: ", serial_port);
    load_float(sets.amp_hour_rating, serial_port);
    send_string("\n\r Capacity: ", serial_port);
    load_float(vars.battery_capacity, serial_port);
    send_string("\n\r Remaining: ", serial_port);
    load_float(vars.battery_remaining, serial_port);
    send_string("\n\r Charge Cycles: ", serial_port);
    load_float(vars.TotalChargeCycles, serial_port);
    send_string("\n\r", serial_port);
}

void setsLockedErr(int serial_port){
    serial_port = port_Sanity(serial_port);
    load_string("Unable: Settings Locked.\n\r", serial_port);
}

void Command_Interp(int serial_port){
    serial_port = port_Sanity(serial_port);
    //Get data. Get allll the data.
    while (((serial_port == PORT1 && U1STAbits.URXDA) || (serial_port == PORT2 && U2STAbits.URXDA)) && !cmdRDY[serial_port]){
        C_Point_CHK(serial_port);
        //Data input
        if(serial_port)CMD_buff[serial_port][CMD_Point[serial_port]] = U2RXREG;
        else CMD_buff[serial_port][CMD_Point[serial_port]] = U1RXREG;
        //Data echo
        if ((CMD_buff[serial_port][CMD_Point[serial_port]] != 0x0D) ||
        (CMD_buff[serial_port][CMD_Point[serial_port]] != 0x0A)){
            if(serial_port)U2TXREG = CMD_buff[serial_port][CMD_Point[serial_port]];
            else U1TXREG = CMD_buff[serial_port][CMD_Point[serial_port]];
        }
        //Check for a RETURN
        char cmdinput = CMD_buff[serial_port][CMD_Point[serial_port]];
        if (cmdinput == 0x0D || cmdinput == 0x0A){
            load_string("\n\r", serial_port);
            bufsize[serial_port] = CMD_Point[serial_port];
            CMD_Point[serial_port] = clear;
            cmdRDY[serial_port] = set; //Tell our command handler to process.
        }
        //No RETURN detected? Store the data.
        else if(CMD_Point[serial_port] < Clength)CMD_Point[serial_port]++;
    }
    //Command Handler.
    if (cmdRDY[serial_port]){
        //Send command receive "@"
        load_string("@", serial_port);
        //Check for faults.
        if(vars.fault_count){
            //Send fault alert "!"
            load_string("!", serial_port);
        }
        if(Run_Level == Crit_Err){
            //Send fault alert "!"
            load_string(" ->CrE!<-", serial_port);
        }
        switch(CMD_buff[serial_port][tempPoint[serial_port]]){
            case '\r':
            break;
            case '\n':
            break;
            case '#':   //Reset the CPU
                if(Flags&syslock)setsLockedErr(serial_port);
                else {
                    CMD_Point[serial_port] = clear;
                    cmdRDY[serial_port] = clear;
                    asm("reset");
                }
            break;
            case '$':
                //Generate flash and chip config checksum and compare it to the old one.
                load_string("\n\rPRG:\n\rStored:", serial_port);
                load_hex(sets.flash_chksum_old, serial_port);
                load_string("\n\rCalc:  ", serial_port);
                if(check_prog()==2)load_string("Mem Busy", serial_port);
                else load_hex(flash_chksum, serial_port);
                load_string("\n\r", serial_port);
            break;
            case '%':
                //Generate EEPROM checksum and compare it to the old one.
                load_string("\n\rNVM:\n\rStored:", serial_port);
                load_hex(eeprom_read(0x01FF), serial_port);
                load_string("\n\rCalc:  ", serial_port);
                if(check_nvmem()==2)load_string("Mem Busy", serial_port);
                else load_hex(rom_chksum, serial_port);
                load_string("\n\r", serial_port);
            break;
            case '^':
                if(Flags&syslock)setsLockedErr(serial_port);
                else {
                    load_string("\n\rSets and Vars Saved.\n\r", serial_port);
                    save_sets();
                    save_vars();  //Save settings to NV-memory
                }
            break;
            case '~':
                if(Flags&syslock)setsLockedErr(serial_port);
                else {
                    default_sets(); //Load default Settings.
                    save_sets();    //Save them to EEPROM.
                    nvm_chksum_update();    //Update EEPROM checksum.
                }
            break;
            case '!': //Clear variables and restart.
                if(Flags&syslock)setsLockedErr(serial_port);
                else {
                    eeprom_erase(cfg_space);
                    nvm_chksum_update();    //Update EEPROM checksum.
                    CMD_Point[serial_port] = clear;
                    cmdRDY[serial_port] = clear;
                    asm("reset");
                }
            break;
            case 'H':
                vars.heat_cal_stage = initialize;
            break;
            case 'h':
                vars.heat_cal_stage = disabled;
                save_vars();
            break;
            case 'S':
                STINGbits.deep_sleep = set;
            break;
            case 'F':
                fault_read(serial_port);          //Read all fault codes.
            break;
            case 'P':
                load_string("P On\n\r", serial_port);
                CONDbits.Power_Out_EN = on;
            break;
            case 'p':
                load_string("P Off\n\r", serial_port);
                v_test = clear;
                CONDbits.Power_Out_EN = off;
            break;
            case 'O':
                load_string("\n\rHUD On\n\r", serial_port);
                sets.PxVenable[serial_port] = on;
                ram_chksum_update();        //Generate new checksum.
            break;
            case 'o':
                load_string("\n\rHUD Off\n\r", serial_port);
                sets.PxVenable[serial_port] = off;
                ram_chksum_update();        //Generate new checksum.
            break;
            case 't':
                load_string("Time left: ", serial_port);
                load_float(DeepSleepTimer, serial_port);
                load_string(" minutes and ", serial_port);
                load_float(DeepSleepTimerSec, serial_port);
                load_string(" seconds.\n\r", serial_port);
            break;
            case 'T':
                timer_reset();
            break;
            case 'C':
                vars.fault_count = clear;
                STINGbits.errLight = clear;
                STINGbits.fault_shutdown = clear;
                if(vars.heat_cal_stage != disabled)
                    vars.heat_cal_stage = notrun;
                STINGbits.osc_fail_event = clear;
                if(!(Flags&syslock))Flags=clear;
                save_vars();
                load_string("\n\rFaults Cleared.\n\r", serial_port);
            break;
            case '&':
                if(Run_Level == Crit_Err && !(Flags&syslock))Run_Level = Heartbeat; //Attempt to bring back from critical error.
                else if(Flags&syslock)
            break;
            case 'Z':
                STINGbits.p_charge = no;
                dsky.chrg_voltage = sets.battery_rated_voltage;
                if(PORTEbits.RE8){
                    vars.partial_chrg_cnt = clear;
                }
                else{
                    vars.partial_chrg_cnt = 10;
                }
            break;
            case '*':   //Print firmware version.
                load_string(version, serial_port);
            break;
            case 'i':   //Print info.
                ADCON1bits.ADON = on;                // turn ADC on
                all_info(serial_port);
            break;
            case 'l':  //Unlock the system and allow variables to be modified.
                Flags &= 0xFE;
                CONDbits.Power_Out_EN = off;
                STINGbits.CH_Voltage_Present = off;
                save_vars();
                load_string("Sets UnLKD.\n\r", serial_port);
            break;
            case 'L':  //Lock the system and enable system functionality.
                send_string("Wait...", serial_port);
                first_cal = 0;  //Initiate calibration routine
                Flags |= syslock; //Lock the settings so that things can run without disruption.
                while(first_cal!=3)Idle();  //Wait until calibration is done.
                save_vars();
                load_string("Sets LKD.\n\r", serial_port);
            break;
            case 'Q':
                if(!(Flags&syslock))Volt_Cal(serial_port);
                else if(Flags&syslock)setsLockedErr(serial_port);
            break;
            case 'm':
                if(CONDbits.Power_Out_EN)load_string("\n\rPower Out On.", serial_port);
                if(CONDbits.charger_detected)load_string("\n\rCharge Go.", serial_port);
                load_string("\n\rRL ", serial_port);
                load_float(Run_Level, serial_port);
                load_string("\n\rCH ", serial_port);
                load_float(charge_mode, serial_port);
                load_string("\n\r", serial_port);

            break;
            default:
                load_string("Unknown Command.\n\r", serial_port);
            break;
        }
        CMD_Point[serial_port] = clear;
        cmdRDY[serial_port] = no;
        tempPoint[serial_port] = clear;
    }
    dispatch_Serial(serial_port);
}

void BAL_Out(char LEDS){
    LED_dir_1 = LED_HiZ_1;
    LED_dir_2 = LED_HiZ_2;
    Mult_SEL = 0;
    Mult_B1 = !(!(LEDS&0x01)); //WTF?? Can't do it without !(!())
    Mult_B2 = !(!(LEDS&0x02)); //Cleaner looking than writing an if()
    Mult_B3 = !(!(LEDS&0x04));
    Mult_B4 = !(!(LEDS&0x08));
    LED_dir_1 = DFLT_1;
    LED_dir_2 = DFLT_2;
    
}

void LED_Out(char LEDS){
    LED_dir_1 = LED_HiZ_1;
    LED_dir_2 = LED_HiZ_2;
    Mult_SEL = 1;
    Mult_B1 = !(LEDS&0x01);
    Mult_B2 = !(LEDS&0x02);
    Mult_B3 = !(LEDS&0x04);
    Mult_B4 = !(LEDS&0x08);
    LED_dir_1 = DFLT_1;
    LED_dir_2 = DFLT_2;
}


void LED_ChrgLVL(float LEVEL){
    if((LEVEL > 90 && !CONDbits.charger_detected) || (LEVEL > 100 && CONDbits.charger_detected))LED_Out(0x0F);
    else if(LEVEL > 75)LED_Out(0x07);
    else if(LEVEL > 50)LED_Out(0x03);
    else if(LEVEL >= 25)LED_Out(0x01);
    else if(LEVEL < 25 && !STINGbits.CH_Voltage_Present){
        if(BlinknLights&0x04)LED_Out(0x01);      //Low battery indication.
        else LED_Out(0x00);
    }
    else LED_Out(0x00);
}

//Gas gauge and ballance circuit output control.
void LED_Mult(char attributes){
    if(attributes >= on){
        //Run multiplexed routine.
        //Debug mode LEDs
        if(attributes == Debug)LED_Out(0x06);
        else if(attributes == Ltest){
            if(CONDbits.LED_test_ch)BAL_Out(LED_Test);
            else LED_Out(LED_Test);
        }
        else if(mult_timer >= LED_Brightness && attributes == on){
            //Display LEDs
            mult_timer = 0;
            //Error blink LED
            if(STINGbits.errLight){
                if(BlinknLights&0x10)LED_Out(0x02); //Slow blink.
                else LED_Out(0x00);
            }
            //Charging level indication.
            else if(CONDbits.charger_detected){
                if(BlinknLights&0x01 && (charge_mode == USB3_Fast || CONDbits.fastCharge))LED_ChrgLVL(dsky.chrg_percent+25); //Fast charging indication.
                else if(BlinknLights&0x02 && charge_mode != USB3_Fast && !CONDbits.fastCharge)LED_ChrgLVL(dsky.chrg_percent+25);  //Normal charging indication.
                else LED_ChrgLVL(dsky.chrg_percent);
            }
            //Power level indication.
            else LED_ChrgLVL(dsky.chrg_percent);
        }
        else{
            //Balance LEDs
            if(mult_timer<LED_Brightness)mult_timer++;
            BAL_Out(Ballance_LEDS);
        }
    }
    else {
        //Turn all multiplexed outputs off.
        BAL_Out(0x00);
    }
}

#endif
//CONDbits.pwr_detect