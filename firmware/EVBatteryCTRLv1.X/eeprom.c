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

#ifndef eeprom_C
#define eeprom_C

#include "eeprom.h"
#include "checksum.h"
#include "common.h"
//Only to be used at start of system
void get_variables(void){
    if(eeprom_read(cfg_space) == 0x7654) {
        read_vars();
    }
}
//Only to be used at start of system
void get_settings(void){
    if(eeprom_read(0x0000) == 0x4567){
        int x = 0;
        for(;;){
            if(!read_sets()){
                //Attempt to copy data no more than 5 times.
                if(x >= 5)death_loop();//If settings are read back but the EEPROM shows corruption, we cannot trust the settings, nor can we trust defaults.
                x++;
            }
            else break;
        }
    }
    else if(eeprom_read(0x0000) == 0xFFFF){
        //If no settings were previously stored in EEPROM then it should be safe to load defaults.
        prgm_chksum_update();//If a first read is detected, update the prog_checksum.
        default_sets();
        save_sets();//Save sets including program memory checksum to eeprom.
    }
}
//Save settings to EEPROM
void save_sets(void){
    int x = 0;
    for(x=0;x<cfg_space;x++){
        eeprom_write(x, sets.settingsArray[x]);
    }
    //Write this in memory so we know we have written data at least once before.
    eeprom_write(0x0000, 0x4567);
    nvm_chksum_update();
}
//Read settings from EEPROM
//Returns 1 on success.
int read_sets(void){
    //First check to make sure EEPROM checksum hasn't changed since last write.
    if(check_nvmem()){
        return 0;
    }
    int x;
    for(x=0;x<cfg_space;x++){
        sets.settingsArray[x] = eeprom_read(x);
    }
    //Update the settings ram checksum.
    ram_chksum_update();
    //Now generate and compare checksums of settings ram and settings EEPROM to ensure a correct copy of data.
    if(check_nvmSets()){
        return 0;
    }
    return 1;
}
//Save vars to EEPROM
void save_vars(void){
    int x = 0;
    for(x=0;x<vr_space;x++){
        eeprom_write(x+cfg_space, vars.variablesArray[x]);
    }
    //Write this in memory so we know we have written data at least once before.
    eeprom_write(cfg_space,0x7654);
    eeprom_write(cfg_space+vr_space, Flags); //Write the un-resettable flags to end of vars.
    nvm_chksum_update();
    CONDbits.failSave = 0;
}
//Read vars from EEPROM
//Returns 1 on success
int read_vars(void){
    if(check_nvmem())return 0;
    int x = 0;
    for(x=0;x<vr_space;x++){
        vars.variablesArray[x] = eeprom_read(x+cfg_space);
    }
    Flags = eeprom_read(vr_space+cfg_space);
    return 1;
}

/**********************/
/* EEPROM Interaction */
//EEPROM functions. Yes, it is faster to write 16 words at a time rather than one at a time. I'm too lazy to implement that.
int eeprom_erase(int addrs){
    int adrfinal = 0;
    if (addrs > 0x1FF){
        return 1;       //error clearing, address out of range.
    }
    else{
        __asm__ volatile ("DISI #0x3FFF");   //Disable all non-critical IRQs.
        __asm__ ("PUSH w1");
        adrfinal = addrs * 2;
        adrfinal += 0xFC00;
        //Erase location.
        NVMADRU = 0x7F;
        NVMADR = adrfinal;
        __asm__ volatile ("MOV #0x4044,w1");
        __asm__ volatile ("MOV w1,NVMCON");
        __asm__ volatile ("MOV #0x55,w1");
        __asm__ volatile ("MOV w1,NVMKEY");
        __asm__ volatile ("MOV #0xAA,w1");
        __asm__ volatile ("MOV w1,NVMKEY");
        __asm__ volatile ("BSET NVMCON,#0x0F");
        __asm__ volatile ("NOP");
        __asm__ volatile ("NOP");
        __asm__ volatile ("POP w1");
        while(NVMCONbits.WR) //Wait here until write is finished.
        DISICNT = 0;    //ReEnable all non-critical IRQs.
        return 0;
    }
}
/** Write a Byte to EEPROM **/
int eeprom_write(int addrs, int data){
    eeprom_erase(addrs);
    if (addrs > 0x1FF){
        return 1;       //error writing, address out of range.
    }
    else{
        __asm__ volatile ("DISI #0x3FFF");   //Disable all IRQs.
        __asm__ volatile ("PUSH w0");
        __asm__ volatile ("PUSH w1");
        __asm__ volatile ("PUSH w2");
        addrs *=  2;
        addrs += 0xFC00;
        //Write to location.
        //DO NOT TOUCH THIS, EVERYTHING MUST BE DONE IN THIS EXACT ORDER OR IT WILL NOT WORK!!!
        TBLPAG = 0x7F;     //ADDRESS UPPER
        //__asm__ ("MOV W1,TBLPAG");
        WREG2 = data;    //DATA
        WREG0 = addrs;   //ADDRESS LOWER
        //ESPECIALLY DON'T TOUCH THE ORDER THAT THE WREGs GET WRITTEN TO.
        __asm__ volatile ("TBLWTL w2,[w0]");
        __asm__ volatile ("MOV #0x4004,w1");
        __asm__ volatile ("MOV w1,NVMCON");
        __asm__ volatile ("MOV #0x55,w1");
        __asm__ volatile ("MOV w1,NVMKEY");
        __asm__ volatile ("MOV #0xAA,w1");
        __asm__ volatile ("MOV w1,NVMKEY");
        __asm__ volatile ("BSET NVMCON,#0x0F");
        __asm__ volatile ("NOP");
        __asm__ volatile ("NOP");
        __asm__ volatile ("POP w2");
        __asm__ volatile ("POP w1");
        __asm__ volatile ("POP w0");
        while(NVMCONbits.WR) //Wait here until write is finished.
        DISICNT = 0;        //ReEnable all non-critical IRQs.
        return 0;
    }
}

int memread(char Moffset, int Maddress){
    offset = Moffset; //Save to memory instead of W register.
    address = Maddress; //This is really bad, but the compiler sometimes reuses WREG's while I'm using them manually (which is bad enough).
    __asm__ volatile ("DISI #0x3FFF");   //Disable all IRQs.
    __asm__ volatile ("PUSH w4");
    __asm__ volatile ("PUSH w0");
    TBLPAG = offset;    //Offset in memory
    WREG0 = address;    //Address to read from
    __asm__ volatile ("TBLRDH [w0],w4");
    __asm__ volatile ("NOP");
    __asm__ volatile ("NOP");
    upperMem = WREG4;   //Get upper 8 bits from program memory, NOT EEPROM/NVM
    TBLPAG = offset;    //Offset in memory
    WREG0 = address;    //Address to read from
    __asm__ volatile ("TBLRDL [w0],w4");
    __asm__ volatile ("NOP");
    __asm__ volatile ("NOP");
    eRead = WREG4;
    __asm__ volatile ("POP w0");
    __asm__ volatile ("POP w4");
    DISICNT = 0;        //ReEnable all non-critical IRQs.
    return eRead; //WREG4 will contain data read from NVmem
}

int eeprom_read(int addrs){
    if (addrs > 0x1FF){
        return 0;       //error reading, address out of range. Return what we hope to be a safe value.
    }
    else{
        return memread(0x7F, (0xFC00+(addrs*2)));
    }
}

#endif
