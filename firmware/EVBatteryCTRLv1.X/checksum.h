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

#ifndef chksum_H
#define	chksum_H

void flash_checksum(void);
void eeprom_checksum(void);
int check_prog(void);
int check_nvmem(void);
void nvmSets_checksum(void);
void ramSets_checksum(void);
int check_ramSets(void);
int check_nvmSets(void);
void ram_chksum_update(void);
void prgm_chksum_update(void);
void nvm_chksum_update(void);

int flash_chksum = 0;
int rom_chksum = 0;
int nvSets_chksum = 0;
int ramSets_chksum = 0;
int ramSets_chksum_old = 0;
int check_timer = 0;
int ram_err_count = 0;

#endif	/* DATAIO_H */

