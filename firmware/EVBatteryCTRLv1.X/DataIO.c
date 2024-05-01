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

#ifndef DATAIO_C
#define DATAIO_C

#include "common.h"
#include "DataIO.h"

void USB_Power_Present_Check(void){
    if(dsky.Cin_voltage>3.5){
        U1MODEbits.UARTEN = 1;  //enable UART1
        U1STAbits.UTXEN = 1;    //enable UART1 TX
        I2CCONbits.I2CEN = 1;   //enable I2C interface
    }
    else {
        U1MODEbits.UARTEN = 0;  //disable UART1
        U1STAbits.UTXEN = 0;    //disable UART1 TX
        I2CCONbits.I2CEN = 0;   //disable I2C interface
    }
}

//Check to make sure serial_port is either 1 or 2, if it's not then default to port 1
int port_Sanity(int serial_port){
    if(serial_port != PORT1 && serial_port != PORT2){
        fault_log(0x3E, 0x00);
        return PORT2;   //default to port2 because it's always on.
    }
    else return serial_port;
}

void Buffrst(int serial_port){
    serial_port = port_Sanity(serial_port);
    if (Buffer[serial_port][Buff_index[serial_port]] == NULL){
        Buff_index[serial_port] = clear;
        portBSY[serial_port] = clear;  //Inhibits writing to buffer while the serial port is transmitting buffer.
    }
    if(Buff_index[PORT1] == clear && Buff_index[PORT2] == clear)CONDbits.slowINHIBIT = 0;
}

void B_Sanity_CHK(int serial_port){
    serial_port = port_Sanity(serial_port);
    if(Buff_index[serial_port]<0)Buff_index[serial_port]=0;
    if(Buff_index[serial_port]>=bfsize)Buff_index[serial_port]=0;
}

//Check if serial port is busy.
//If used, ensure that it is used by an IRQ priority that is lower than TX IRQs.
void portBusyIdle(int serial_port){
    serial_port = port_Sanity(serial_port);
    while(portBSY[serial_port]){
        //CPUact = 0;      //Turn CPU ACT light off.
        Idle();                 //Idle Loop, saves power.
    }
    //CPUact = 1;      //Turn CPU ACT light on.
}

//*************************************************************************************************
//Converts four bit hex numbers to ASCII
char four_bit_hex_cnvt(int numb){
    char asci_hex = 0;
    int temp = 0;
    temp = 0x0F & numb;

    if(temp < 10){
        asci_hex = temp + 48;
    }
    else{
        asci_hex = temp + 55;
    }
    return asci_hex;
}

void port_check(int serial_port){
    serial_port = port_Sanity(serial_port);
    //Check if valid port has been selected.
    if (serial_port > 0x01){
        fault_log(0x1A, 0x00);        //Log invalid port error.
        FtempIndex[serial_port] = clear;
        return;
    }
    //check if port is busy sending data.
/*    if(portBSY[serial_port]){
        if(serial_port)
            //fault_log(0x28);       //Log Port2 Busy Error.
        else
            //fault_log(0x27);       //Log Port1 Busy Error.
        return;
    }*/
    //check if another process is currently writing to buffer.
    if(writingbuff[serial_port]){
        return;
    }
}

//Loads ascii HEX into buffer.
void load_hex(int numb, int serial_port){
    serial_port = port_Sanity(serial_port);
    B_Sanity_CHK(serial_port);
    port_check(serial_port);
    nibble[serial_port][0] = (numb & 0xF000)/4096;
    nibble[serial_port][1] = (numb & 0x0F00)/256;
    nibble[serial_port][2] = (numb & 0x00F0)/16;
    nibble[serial_port][3] = (numb & 0x000F);
    writingbuff[serial_port] = yes;
    Buffer[serial_port][Buff_index[serial_port]] = '0';
    if (Buff_index[serial_port] < bfsize-1)Buff_index[serial_port]++;
    Buffer[serial_port][Buff_index[serial_port]] = 'x';
    if (Buff_index[serial_port] < bfsize-1)Buff_index[serial_port]++;
    int x;
    for(x=0;x<4;x++){
        Buffer[serial_port][Buff_index[serial_port]] = four_bit_hex_cnvt(nibble[serial_port][x]);
        if (Buff_index[serial_port] < bfsize-1)
            Buff_index[serial_port]++;
    }
    writingbuff[serial_port] = no;
}
//Start the data transfer from one of the buffers to the selected serial port
//Dispatch the data in the buffers to the display by creating a TX IRQ
void dispatch_Serial(int serial_port){
    serial_port = port_Sanity(serial_port);
    B_Sanity_CHK(serial_port);
    if(portBSY[serial_port])return;             //If port is busy, don't dispatch a second time.
    portBSY[serial_port] = yes;                 //Tell everyone else that port is now busy.
    Buffer[serial_port][Buff_index[serial_port]] = NULL;   //Put NULL char at end of string.
    Buff_index[serial_port] = clear;               //Start Index at 0.
    if(serial_port) IFS1bits.U2TXIF = set;        //Start transmitting by manually sending an IRQ.
    else IFS0bits.U1TXIF = set;                   //Start transmitting by manually sending an IRQ.
}

//Send a string of text to a buffer that can then be dispatched to a serial port.
void load_string(char *string_point, int serial_port){
    serial_port = port_Sanity(serial_port);
    B_Sanity_CHK(serial_port);
    port_check(serial_port);
    writingbuff[serial_port] = yes;
    StempIndex[serial_port] = clear;
    while (string_point[StempIndex[serial_port]]){
        Buffer[serial_port][Buff_index[serial_port]] = string_point[StempIndex[serial_port]];
        if (Buff_index[serial_port] < bfsize-1)
            Buff_index[serial_port]++;
        else break;
        StempIndex[serial_port]++;
    }
    writingbuff[serial_port] = no;
}

//Send a string of text to a buffer that can then be dispatched to a serial port.
void load_const_string(const char *string_point, int serial_port){
    serial_port = port_Sanity(serial_port);
    B_Sanity_CHK(serial_port);
    port_check(serial_port);
    writingbuff[serial_port] = yes;
    StempIndex[serial_port] = clear;
    while (string_point[StempIndex[serial_port]]){
        Buffer[serial_port][Buff_index[serial_port]] = string_point[StempIndex[serial_port]];
        if (Buff_index[serial_port] < bfsize-1)
            Buff_index[serial_port]++;
        else break;
        StempIndex[serial_port]++;
    }
    writingbuff[serial_port] = no;
}

//Send text to buffer and auto dispatch the serial port.
void send_string(char *string_point, int serial_port){
    serial_port = port_Sanity(serial_port);
    load_string(string_point, serial_port);
    dispatch_Serial(serial_port);
    portBusyIdle(serial_port);  //Check to see if port is ready.
}

//Copy float data to buffer.
void cpyFLT(int serial_port){
    serial_port = port_Sanity(serial_port);
    B_Sanity_CHK(serial_port);
    Buffer[serial_port][Buff_index[serial_port]] = float_out[serial_port][FtempIndex[serial_port]];
    //Do not overrun the buffer.
    if (Buff_index[serial_port] < bfsize-1)Buff_index[serial_port]++;
}
/* Sends a float to buffer as plane text. */
void load_float(float f_data, int serial_port){
    serial_port = port_Sanity(serial_port);
    FtempIndex[serial_port] = 0;
    tx_float[serial_port] = 0;
    tx_temp[serial_port] = 0;

    float_out[serial_port][0] = ' ';
    if (f_data < 0){
        f_data *= -1;                       //Convert to absolute value.
        float_out[serial_port][0] = '-';    //Put a - in first char
    }
    if (f_data > 9999.999){
        f_data = 9999.999;      //truncate it if it's too big of a number.
        float_out[serial_port][0] = '?';    //Put a ? in first char if truncated.
    }
    else if (f_data < 0000.001 && f_data != 0){
        f_data = 0000.001;      //truncate it if it's too big of a number.
        float_out[serial_port][0] = '<';    //Put a ? in first char if truncated.
    }

    tx_float[serial_port] = f_data / 1000;
    FtempIndex[serial_port]++;
    while (FtempIndex[serial_port] <= 8){
        if (FtempIndex[serial_port] == 5){
            float_out[serial_port][5] = '.';    //Put a decimal at the 5th spot.
            FtempIndex[serial_port]++;          //Go to 6th spot after.
        }
        tx_temp[serial_port] = tx_float[serial_port];   //Truncate anything on the right side of the decimal.
        float_out[serial_port][FtempIndex[serial_port]] = tx_temp[serial_port] + 48; //Convert it to ASCII.
        FtempIndex[serial_port]++;                                                   //Go to next ASCII spot.
        tx_float[serial_port] = (tx_float[serial_port] - tx_temp[serial_port]) * 10; //Shift the float left by 1
    }

/* Write to buffer */
    FtempIndex[serial_port] = 0;
    port_check(serial_port);        //Check serial port to see if it's busy before writing to buffer.
    writingbuff[serial_port] = 1;   //Tell other processes we are busy with the buffer.
    while (FtempIndex[serial_port] < 9){
        //If 0, do not copy unless it's 00.000 or a '-' or greater than 999 && config_space is 1
        while(float_out[serial_port][FtempIndex[serial_port]] == '0' &&
        !config_space[serial_port] && FtempIndex[serial_port] < 3 && f_data < 1000){
            FtempIndex[serial_port]++;
        }
        //Copy data. Check for dynamic spacing for sign char.
        if(dynaSpace[serial_port]){
            switch(float_out[serial_port][FtempIndex[serial_port]]){
                case '-':
                    cpyFLT(serial_port);
                case ' ':
                    FtempIndex[serial_port]++;
                break;
            }
            dynaSpace[serial_port] = 0;
        }
        else{
            cpyFLT(serial_port);
            FtempIndex[serial_port]++;
        }
        //Clear 'ifzero' if anything but '0', '-', or ' ' found.
        if(float_out[serial_port][FtempIndex[serial_port]] != '0' &&
        float_out[serial_port][FtempIndex[serial_port]] != '-' &&
        float_out[serial_port][FtempIndex[serial_port]] != ' '){
            config_space[serial_port] = 0;
        }
    }
    config_space[serial_port] = 0;
    writingbuff[serial_port] = 0;
}

//get floating point number from text input
float Get_Float(int index, int serial_port){
    float F_Temp = 0;
    float F_Dec_Mult = 0.1;
    int Past_Dec = no;
    int Is_Negative = no;
    if(CMD_buff[serial_port][index]=='-')Is_Negative = yes;
    for(int i=index;i<9+index&&i<Clength;i++){
        if(Is_Negative && i==index)i++;
        char F_Text = CMD_buff[serial_port][i];
        if((F_Text==0 || F_Text==' ' || F_Text=='\n' || F_Text=='\r' || F_Text<0x30 || F_Text>0x39) && F_Text!='.'){
            if(Is_Negative)return F_Temp*-1;
            else return F_Temp;
        }
        if(F_Text=='.'){
            Past_Dec = yes;
        }
        if(Past_Dec && F_Text!='.'){
            float Tnum = F_Text-0x30;
            Tnum *= F_Dec_Mult;
            F_Dec_Mult *= 0.1;
            F_Temp += Tnum;
        }
        else if(F_Text!='.'){
            float Tnum = F_Text-0x30;
            F_Temp *= 10;
            F_Temp += Tnum;
        }
    }
    if(Is_Negative)return F_Temp*-1;
    else return F_Temp;
}

unsigned int BaudCalc(float BD, float mlt){
    /* Calculate baud rate. */
    if(CONDbits.clockSpeed == slow)mlt /= 16;
    if(BD==0)BD=9600; //Prevent divide by zero, default to 9600 baud.
    float INS = mlt * 1000000;
    float OutPut = ((INS/BD)/16)-1;
    unsigned int Oputs = OutPut;
    return Oputs;             //Weird things happen when you try to calculate
                              //a float directly into an int. Don't do this.
    /************************/
}

#endif
