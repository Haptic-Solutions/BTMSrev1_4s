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

#ifndef DSKY_H
#define	DSKY_H

extern void Command_Interp(int);
extern void fault_read(int);
extern void displayOut(int);
extern void LED_Mult(char);
extern void Chng_LED_Mode(char);

unsigned int CMD_Point[2];  //Command Pointer
unsigned int bufsize[2];
char CMD_buff[2][6];              //Command Buffer
char cmdRDY[2] = {0,0};
char cmdOVFL[2] = {0,0};
char Terr[2] = {0,0};

unsigned int tempPoint[2];
unsigned int flt_index[2];
unsigned int PxPage[2];
unsigned int pageVar[2];
unsigned int varNum[2];
unsigned int dodispatch[2];
char PxVtimer[2];

#endif	/* DATAIO_H */

