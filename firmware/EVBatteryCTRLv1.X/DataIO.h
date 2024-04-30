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

#ifndef DATAIO_H
#define	DATAIO_H

#define PORT1 0
#define PORT2 1
#define simple 1
#define full 0
#define bfsize 100

extern unsigned int BaudCalc(float, float);
extern void load_float(float, int);
extern void load_string(char*, int);
extern void send_string(char*, int);
extern void copy_string(char*, int);
extern void dispatch_Serial(int);
extern char four_bit_hex_cnvt(int);
extern void Buffrst(int);
extern void BuffNull(int);
extern void USB_Power_Present_Check(void);
extern void portBusyIdle(int);
extern void load_const_string(const char*, int);
extern float Get_Float(int, int);
void load_hex(int, int);
int port_Sanity(int);

//Serial port stuff
float tx_float[2] = {0,0};
int Buff_index[2] = {0,0};
int StempIndex[2] = {0,0};
int FtempIndex[2] = {0,0};
char nibble[2][4] = {{0,0,0,0},{0,0,0,0}};
char float_out[2][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
char Buffer[2][bfsize];
char config_space[2] = {0,0};
char tx_temp[2] = {0,0};
char portBSY[2] = {0,0};
char writingbuff[2] = {0,0};
char dynaSpace[2] = {0,0};

#endif	/* DATAIO_H */

