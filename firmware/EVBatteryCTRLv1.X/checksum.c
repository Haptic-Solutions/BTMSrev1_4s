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

#ifndef chksum_C
#define chksum_C

#include "checksum.h"
#include "common.h"

/********************/
/* Update checksum. */
//Used for updating the Settings RAM checksum.
void ram_chksum_update(void){
    ramSets_checksum();         //Generate New Checksum
    ramSets_chksum_old = ramSets_chksum;    //Copy it.
}
//Update the Program Memory checksum.
void prgm_chksum_update(void){
    flash_checksum();         //Generate New Checksum
    sets.flash_chksum_old = flash_chksum;    //Copy it.
}
//Update the EEPROM checksum.
void nvm_chksum_update(void){
    eeprom_checksum();         //Generate New Checksum
    eeprom_write(0x01FF, rom_chksum);    //Copy it.
}

/******************************************/
/* Checksum comparison and error logging. */
//Check settings checksum stored in ram against an older version of itself.
int check_ramSets(void){
    ramSets_checksum();
    if(ramSets_chksum != ramSets_chksum_old){
        fault_log(0x2B);    //Log an error if it doesn't match.
        return 1;
    }
    return 0;
}
//Check settings checksum stored in ram against settings checksum from EEPROM.
int check_nvmSets(void){
    ramSets_checksum();
    nvmSets_checksum();
    if(ramSets_chksum != nvSets_chksum){
        fault_log(0x2C);    //Log an error if it doesn't match.
        STINGbits.fault_shutdown = 1;
        return 1;
    }
    return 0;
}
//Checks program memory checksum.
int check_prog(void){
    if(CONDbits.chkInProgress) return 0;
    CONDbits.chkInProgress = 1;
    flash_checksum();
    if(sets.flash_chksum_old != flash_chksum){
        fault_log(0x29);    //Log an error if it doesn't match.
        STINGbits.fault_shutdown = 1;
        CONDbits.chkInProgress = 0;
        return 1;
    }
    CONDbits.chkInProgress = 0;
    return 0;

}
//Checks EEPROM memory checksum.
int check_nvmem(void){
    eeprom_checksum();
    if(eeprom_read(0x01FF) != rom_chksum){
        fault_log(0x2A);    //Log an error if it doesn't match.
        STINGbits.fault_shutdown = 1;
        return 1;
    }
    return 0;
}

/*********************************/
/* Checksum generation routines. */
/*********************************/
//Generates checksum of flash and chip config memory.
void flash_checksum(void){
    flash_chksum = 0;
    int xaddr = 0;
    int yaddr = 0;
    //Read program memory space.
    for(xaddr=0;xaddr<0x1FFF;xaddr++){
        flash_chksum += ((0x00FF & memread(0x00,xaddr*2)) + ((0xFF00 & memread(0x00,xaddr*2)) / 256));
        flash_chksum += upperMem;
    }
    //Read chip config memory space.
    for(yaddr=0xF8;yaddr<0xFF;yaddr++)
        for(xaddr=0;xaddr<0x7FFF;xaddr++){flash_chksum += ((0x00FF & memread(yaddr,xaddr*2)) + ((0xFF00 & memread(yaddr,xaddr*2)) / 256));}
    flash_chksum += (210 * 2); //No matter what I do, the checksum is always a difference of 420 from what MPLAB says it should be.
}
//Generates checksum of EEPROM memory.
void eeprom_checksum(void){
    rom_chksum = 0;
    int xaddr = 0;
    //Read program memory space except last byte because that's where the EEPROM's checksum is stored.
    for(xaddr=0;xaddr<0x01FE;xaddr++){
        rom_chksum += ((0x00FF & eeprom_read(xaddr)) + ((0xFF00 & eeprom_read(xaddr)) / 256));
    }
}
//Generates checksum of Settings stored in EEPROM memory.
void nvmSets_checksum(void){
    nvSets_chksum = 0;
    int xaddr = 0;
    //Read program memory space except last byte because that's where the EEPROM's checksum is stored.
    for(xaddr=0;xaddr<(cfg_space);xaddr++){
        nvSets_chksum += ((0x00FF & eeprom_read(xaddr)) + ((0xFF00 & eeprom_read(xaddr)) / 256));
    }
}
//Generates checksum of Settings stored in RAM.
void ramSets_checksum(void){
    ramSets_chksum = 0;
    int xaddr = 0;
    //Read settings memory space.
    for(xaddr=0;xaddr<(cfg_space);xaddr++){
        ramSets_chksum += ((0x00FF & sets.settingsArray[xaddr]) + ((0xFF00 & sets.settingsArray[xaddr]) / 256));
    }
}

#endif
