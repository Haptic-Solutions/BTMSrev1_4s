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

extern void USB_Power_Present_Check(void);
extern char four_bit_hex_cnvt(int);
extern void load_hex(int, int, int);
extern void dispatch_Serial(int);
extern void load_string(int, char*, int);
extern void load_const_string(int, const char*, int);
extern void send_string(int, char*, int);
extern void load_float(int, float, int);
extern float Get_Float(int, int);
extern unsigned int BaudCalc(float, float);

extern void Send_I2C(unsigned int, unsigned int, unsigned char, unsigned char);
extern void Receive_I2C(unsigned int, unsigned char, unsigned char);

//Serial port stuff
float tx_float[2] = {0,0};
int Buff_index[2] = {0,0};
int B_Out_index[2] = {0,0};
int StempIndex[2] = {0,0};
int FtempIndex[2] = {0,0};
int nibble[2][4] = {{0,0,0,0},{0,0,0,0}};
char float_out[2][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
char Buffer[2][bfsize];
char config_space[2] = {0,0};
char tx_temp[2] = {0,0};
char portBSY[2] = {0,0};
char writingbuff[2] = {0,0};
char dynaSpace[2] = {0,0};

//I2C stuff
#define IC_PACK_SIZE 30
unsigned char IC_Address = 0;     //address of the I2C device.
unsigned char IC_Command = 0;     //sub address inside the device
unsigned char IC_Packet[IC_PACK_SIZE];      //data buffer
unsigned int IC_Pack_Index = 0;  //data buffer index
unsigned int IC_Pack_Size = 0;   //Number of bytes to transmit or have been received.
int IC_Timer = -1;       //Number of tries before erroring out.
unsigned char IC_Seq = 0;         //I2C sequence status.

#define MD_Send 0
#define MD_Recieve 1

#define IC_Stop_start 1 //send
#define IC_start 2      //send
#define slv_adr 3       //send
#define slv_ack 4       //wait for ack
#define cmd_adr 5       //send
#define cmd_ack 6       //wait for ack
#define rpt_strt 7      //send
#define rpt_slv_adr 8   //send with or without read bit
#define rpt_slv_ack 9   //wait for ack
#define slv_data 10      //either send or receive
#define data_ack 11     //either send ack or wait for ack
#define IC_stop 12      //send

#endif	/* DATAIO_H */

