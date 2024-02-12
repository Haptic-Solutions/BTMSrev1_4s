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

//Loads one of the serial buffers with user defined data and then dispatches it.
void pageOut(int pageNum, int serial_port){
    dodispatch[serial_port] = no;
    for(pageVar[serial_port]=0;pageVar[serial_port]<6;pageVar[serial_port]++){
        varNum[serial_port] = sets.page[serial_port][pageNum][pageVar[serial_port]];
        varNum[serial_port] &= 0xFF;
        if(varNum[serial_port] < 8)dynaSpace[serial_port] = yes;       //Do not reserve a space for a sign char if we don't have to.
        if(varNum[serial_port] == 8)config_space[serial_port] = yes;   //Reserve spaces for 0's when showing watts so that text isn't jumping around.
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
        else if(varNum[serial_port] <= varLimit){
            if(varNum[serial_port] != 0x10)load_float(dsky.dskyarrayFloat[varNum[serial_port]], serial_port);   //Load the number.
            Buff_index[serial_port] -= 2;  //Subtract 2 from buffer index.
            if(varNum[serial_port] == 1 || varNum[serial_port] == 8)Buff_index[serial_port] -= 2; //If Speed or Watts variable then remove decimal and last '0'
            load_string(Vlookup[varNum[serial_port]], serial_port);        //Load the number's text.
            if(varNum[serial_port] != 0x10)load_string(" ", serial_port);  //Load a space afterwards.
            dodispatch[serial_port] = yes; //if we have at least one variable to display then dispatch.
        }
    }
    if (dodispatch[serial_port]){
        dispatch_Serial(serial_port);
    }
}

void displayOut(int serial_port){
    if(sets.PxVenable[serial_port] && !portBSY[serial_port] && CONDbits.main_power){
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

//Check if serial port is busy.
//If used, ensure that it is used by an IRQ priority that is lower than TX IRQs.
void portBusyIdle(int serial_port){
    while(portBSY[serial_port]){
        CPUact = 0;      //Turn CPU ACT light off.
        Idle();                 //Idle Loop, saves power.
    }
    CPUact = 1;      //Turn CPU ACT light on.
}

/* Read fault codes to serial port.
 * This takes up over 5% of program space.*/
void fault_read(int serial_port){
    load_string("Reading Faults.\n\r", serial_port);
    dispatch_Serial(serial_port);
    flt_index[serial_port] = 0;
    portBusyIdle(serial_port);  //Check to see if port is ready.
    if(vars.fault_count > 10){
        load_string("Fault Log Full.\n\r", serial_port);
        dispatch_Serial(serial_port);
    }
    if(vars.fault_count == 0){
        load_string("No fault codes.\n\r", serial_port);
        dispatch_Serial(serial_port);
    }
    else{
        while(flt_index[serial_port] < vars.fault_count){
            portBusyIdle(serial_port);  //Check to see if port is ready.
            load_string("Code: ", serial_port);
            load_hex(vars.fault_codes[flt_index[serial_port]],serial_port);
            load_string(" -> ", serial_port);
            int ecode = vars.fault_codes[flt_index[serial_port]];
            if(!ecode || ecode < numOfCodes)load_string(errArray[ecode-1], serial_port);
            else load_string(codeDefault, serial_port);
            load_string("\n\r", serial_port);
            dispatch_Serial(serial_port);
            flt_index[serial_port]++;
        }
    }
}
void get_mem(int serial_port){
    int data = 0;
    int addr = 0x00FF & CMD_buff[serial_port][1];   //Get raw 8 bit address data.
    if(addr < cfg_space) data = sets.settingsArray[addr];
    else if(addr < cfg_space + vr_space) data = vars.variablesArray[addr - cfg_space];
    else if(addr < cfg_space + vr_space + dsky_space) data = dsky.dskyarray[addr - (cfg_space + vr_space)];
    else data = 0xFFFF;
    load_hex(data, serial_port);
}

void Command_Interp(int serial_port){
    //Get data. Get allll the data.
    while (((serial_port == PORT1 && U1STAbits.URXDA) || (serial_port == PORT2 && U2STAbits.URXDA)) && !cmdRDY[serial_port]){
        //Data input
        if(serial_port)CMD_buff[serial_port][CMD_Point[serial_port]] = U2RXREG;
        else CMD_buff[serial_port][CMD_Point[serial_port]] = U1RXREG;
        //Data echo
        if (Lecho[serial_port] && ((CMD_buff[serial_port][CMD_Point[serial_port]] != 0x0D) ||
        (CMD_buff[serial_port][CMD_Point[serial_port]] != 0x0A))){
            if(serial_port)U2TXREG = CMD_buff[serial_port][CMD_Point[serial_port]];
            else U1TXREG = CMD_buff[serial_port][CMD_Point[serial_port]];
        }
        //Check for a RETURN
        char cmdinput = CMD_buff[serial_port][CMD_Point[serial_port]];
        if (cmdinput == 0x0D || cmdinput == 0x0A){
            if (Lecho[serial_port])load_string("\n\r", serial_port);
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
        if(Lecho[serial_port])load_string("@", serial_port);
        //Check for faults.
        if(vars.fault_count){
            //Send fault alert "!"
            if(Lecho[serial_port])load_string("!", serial_port);
        }
        switch(CMD_buff[serial_port][tempPoint[serial_port]]){
            case '\r':
            break;
            case '\n':
            break;
            case '#':
                CMD_Point[serial_port] = clear;
                cmdRDY[serial_port] = clear;
                asm("reset");
            break;
            case '$':
                //Generate flash and chip config checksum and compare it to the old one.
                load_string("\n\rPRG:\n\rStored:", serial_port);
                load_hex(sets.flash_chksum_old, serial_port);
                load_string("\n\rCalc:  ", serial_port);
                check_prog();
                load_hex(flash_chksum, serial_port);
                load_string("\n\r", serial_port);
            break;
            case '&':
                //Generate EEPROM checksum and compare it to the old one.
                load_string("\n\rNVM:\n\rStored:", serial_port);
                load_hex(eeprom_read(0x01FF), serial_port);
                load_string("\n\rCalc:  ", serial_port);
                check_nvmem();
                load_hex(rom_chksum, serial_port);
                load_string("\n\r", serial_port);
            break;
            case '%':
                if(Lecho[serial_port])load_string("\n\rSettings and Vars Saved.\n\r", serial_port);
                save_sets();
                save_vars();  //Save settings to NV-memory
            break;
            case '~':
                default_sets(); //Load defaults.
                eeprom_erase(0x0000);   //Erase address 0x0000 to 0xFFFF
                nvm_chksum_update();    //Update EEPROM checksum.
            break;
            case 'H':
                vars.heat_cal_stage = initialize;
            break;
            case 'h':
                vars.heat_cal_stage = disabled;
                save_vars();
            break;
            case 'E':
                Lecho[serial_port] = set;
            break;
            case 'e':
                Lecho[serial_port] = clear;
            break;
            case 'S':
                STINGbits.deep_sleep = set;
            break;
            case 'F':
                fault_read(serial_port);          //Read all fault codes.
            break;
            case 'P':
                if(Lecho[serial_port])load_string("P On\n\r", serial_port);
                CONDbits.cmd_power = on;
            break;
            case 'p':
                if(Lecho[serial_port])load_string("P Off\n\r", serial_port);
                v_test = clear;
                CONDbits.cmd_power = clear;
            break;
            case 'O':
                if(Lecho[serial_port])load_string("HUD On\n\r", serial_port);
                sets.PxVenable[serial_port] = on;
                ram_chksum_update();        //Generate new checksum.
            break;
            case 'o':
                if(Lecho[serial_port])load_string("HUD Off\n\r", serial_port);
                sets.PxVenable[serial_port] = off;
                ram_chksum_update();        //Generate new checksum.
            break;
            case 'C':
                vars.fault_count = clear;
                STINGbits.fault_shutdown = clear;
                if(vars.heat_cal_stage != disabled)
                    vars.heat_cal_stage = notrun;
                STINGbits.osc_fail_event = clear;
                save_vars();
                if(Lecho[serial_port])load_string("Faults Cleared.\n\r", serial_port);
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
            case '!':
                get_mem(serial_port); //Gets settings/vars memory address specified and sends back the result in raw.
            break;
            default:
                if(Lecho[serial_port])load_string("Unknown Command.\n\r", serial_port);
            break;
        }
        CMD_Point[serial_port] = clear;
        cmdRDY[serial_port] = no;
        tempPoint[serial_port] = clear;
    }
    dispatch_Serial(serial_port);
}

#endif
