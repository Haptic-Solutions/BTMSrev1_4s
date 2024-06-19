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

#ifndef pwropt_H
#define	pwropt_H

//USB-PD stuff
#define USBPD_Addr 0x51
#define PD_PDO 0x00
#define PD_Valid_Source 0x1C
#define PD_Status 0x1D
#define PD_IRQ_Mask 0x1E
#define PD_Voltage 0x20
#define PD_Current 0x21
#define PD_Temp 0x22
#define PD_OCPTHR 0x23
#define PD_OTPTHR 0x24
#define PD_DRTHR 0x25
#define PD_TR25 0x28
#define PD_TR50 0x2A
#define PD_TR75 0x2C
#define PD_TR100 0x2E
#define PD_ReqDO 0x30
#define PD_VID 0x34

extern int Get_PD_Sources(void);
extern int Calc_PD_Option(unsigned char);
extern int Set_PD_Option(unsigned char);
extern int Get_Highest_PD(void);
extern int Get_Lowest_PD_Voltage(void);
extern void List_PD_Options(int);
extern void Last_PD(int);

float   PD_Last_Current = 0;
float   PD_Last_Voltage = 0;
unsigned char    PD_Last_Status = 0;
unsigned char    PD_Src_Count = 0;

#endif

