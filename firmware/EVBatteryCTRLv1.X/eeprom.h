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

#ifndef eeprom_H
#define	eeprom_H

extern int eeprom_erase(int);   //address. 0x00 through 0x1FF.      Returns 0 on success.
extern int eeprom_write(int, int);  //address, data.    Returns 0 on success.
extern int eeprom_read(int);    //address. Returns data or 0 on failure.
extern void save_sets(void);
extern int read_sets(void);
extern void save_vars(void);
extern int read_vars(void);
extern void get_variables(void);
void get_settings(void);

int upperMem = 0;
int printSets = 0;
int eRead = 0;
char offset = 0;
int address = 0;

#endif	/* DATAIO_H */

