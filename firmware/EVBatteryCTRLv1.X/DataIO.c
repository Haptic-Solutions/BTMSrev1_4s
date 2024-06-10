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

//This routine insures that no voltage is present on the AUX/VBUS bus when there isn't a charger connected.
//Without this, IO lines and pullup resistors will back-drive through the PD chip.
void USB_Power_Present_Check(void){
    if(dsky.Cin_voltage>3.5){
        U1MODEbits.UARTEN = 1;  //enable UART1
        U1STAbits.UTXEN = 1;    //enable UART1 TX
        GENERAL2_TRIS = GENERAL2_DIR | 0x0C;       //set I2C lines to inputs.
    }
    else {
        U1MODEbits.UARTEN = 0;  //disable UART1
        U1STAbits.UTXEN = 0;    //disable UART1 TX
        I2CCONbits.I2CEN = 0;   //disable I2C interface
        GENERAL2_TRIS = GENERAL2_DIR & 0xFFF3;           //set I2C lines to Outputs.
        I2CCONbits.I2CEN = 0;   //disable I2C interface
    }
}
/******************************************************************************/
/* Pre-check port status's, wait or break if something isn't right. */
//Check for valid port selection.
void port_valid_check(int serial_port){
    //Check if valid port has been selected.
    if (serial_port > 0x01 || serial_port < 0x00){
        fault_log(0x1A, 1+serial_port);        //Log invalid port error.
        return;
    }
}
//Check if buffer index is out of range.
void Buffer_Index_Sanity_CHK(int serial_port){
    if(Buff_index[serial_port]<0){
        Buff_index[serial_port]=0;
        fault_log(0x12, (1+serial_port)|0x10);
    }
    if(Buff_index[serial_port]>=bfsize){
        Buff_index[serial_port]=0;
        fault_log(0x12, (1+serial_port)|0x20);
    }
}
//Check for if another process is writing to buffer. Wait for it to finish.
void buffer_write_Idle(int serial_port){
    while(writingbuff[serial_port]==yes){
        Idle();
    }
}
//Check if serial port is busy.
//If used, ensure that it is used by an IRQ priority that is lower than TX IRQs.
void port_Busy_Idle(int serial_port){
    while(portBSY[serial_port]==yes){
        Idle();                 //Idle Loop, saves power.
    }
}
/* Do it all at once. */
void write_check(int serial_port){
    port_valid_check(serial_port);
    Buffer_Index_Sanity_CHK(serial_port);
    buffer_write_Idle(serial_port);
    port_Busy_Idle(serial_port);
}
/******************************************************************************/

//Start the data transfer from one of the buffers to the selected serial port
//Dispatch the data in the buffers to the display by creating a TX IRQ
void dispatch_Serial(int serial_port){
    portBSY[serial_port] = yes;                 //Tell everyone else that port is now busy.
    Buffer[serial_port][Buff_index[serial_port]] = NULL;   //Put NULL char at end of string.
    Buff_index[serial_port] = clear;              //Start Index at 0.
    if(serial_port==PORT2) IFS1bits.U2TXIF = set;        //Start transmitting by manually sending an IRQ.
    else IFS0bits.U1TXIF = set;                   //Start transmitting by manually sending an IRQ.
    port_Busy_Idle(serial_port);
}

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

//Loads ascii HEX into buffer.
void load_hex(int index, int numb, int serial_port){
    write_check(serial_port);
    writingbuff[serial_port] = yes;
    nibble[serial_port][0] = (numb & 0xF000)/4096;
    nibble[serial_port][1] = (numb & 0x0F00)/256;
    nibble[serial_port][2] = (numb & 0x00F0)/16;
    nibble[serial_port][3] = (numb & 0x000F);
    if(index>I_Auto)Buff_index[serial_port]=index;
    Buffer[serial_port][Buff_index[serial_port]] = '0';
    if (Buff_index[serial_port] < bfsize-1)Buff_index[serial_port]++;
    Buffer[serial_port][Buff_index[serial_port]] = 'x';
    if (Buff_index[serial_port] < bfsize-1)Buff_index[serial_port]++;
    for(int x=0;x<4;x++){
        Buffer[serial_port][Buff_index[serial_port]] = four_bit_hex_cnvt(nibble[serial_port][x]);
        if (Buff_index[serial_port] < bfsize-1)Buff_index[serial_port]++;
    }
    writingbuff[serial_port] = no;
}
//Converts int numbers to ASCII
char int_cnvt(int numb){
    char asci_int = 0;
    int temp = 0;
    temp = 0x0F & numb;
    if(temp < 10){
        asci_int = temp + 48;
    }
    return asci_int;
}
//Loads ascii int into buffer.
void load_int(int index, int numb, int serial_port){
    write_check(serial_port);
    writingbuff[serial_port] = yes;
    if(index>I_Auto)Buff_index[serial_port]=index;
    Buffer[serial_port][Buff_index[serial_port]] = ' ';
    if(numb<0){
        Buffer[serial_port][Buff_index[serial_port]] = '-';
        numb*=-1;
    }
    if(numb>9999){
        numb=9999;
        Buffer[serial_port][Buff_index[serial_port]] = '>';
    }
    if (Buff_index[serial_port] < bfsize-1)Buff_index[serial_port]++;
    if(numb>999)nibble[serial_port][0] = numb/1000;
    else nibble[serial_port][0] = 0;
    numb -= nibble[serial_port][0]*1000;
    if(numb>99)nibble[serial_port][1] = numb/100;
    else nibble[serial_port][1] = 0;
    numb -= nibble[serial_port][1]*100;
    if(numb>9)nibble[serial_port][2] = numb/10;
    else nibble[serial_port][2] = 0;
    numb -= nibble[serial_port][2]*10;
    if(numb>0)nibble[serial_port][3] = numb;
    else nibble[serial_port][3] = 0;
    for(int x=0;x<4;x++){
        Buffer[serial_port][Buff_index[serial_port]] = int_cnvt(nibble[serial_port][x]);
        if (Buff_index[serial_port] < bfsize-1)Buff_index[serial_port]++;
    }
    writingbuff[serial_port] = no;
}

//Send a string of text to a buffer that can then be dispatched to a serial port.
void load_string(int index, char *string_point, int serial_port){
    write_check(serial_port);
    writingbuff[serial_port] = yes;
    if(index>I_Auto)Buff_index[serial_port]=index;
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
void load_const_string(int index, const char *string_point, int serial_port){
    write_check(serial_port);
    writingbuff[serial_port] = yes;
    if(index>I_Auto)Buff_index[serial_port]=index;
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
void send_string(int index, char *string_point, int serial_port){
    write_check(serial_port);
    load_string(index, string_point, serial_port);
    dispatch_Serial(serial_port);
}

//Copy float data to buffer.
void cpyFLT(int serial_port){
    Buffer[serial_port][Buff_index[serial_port]] = float_out[serial_port][FtempIndex[serial_port]];
    //Do not overrun the buffer.
    if (Buff_index[serial_port] < bfsize-1)Buff_index[serial_port]++;
}
/* Sends a float to buffer as plane text. */
void load_float(int index, float f_data, int serial_port){
    write_check(serial_port);
    writingbuff[serial_port] = yes;   //Tell other processes we are busy with the buffer.
    if(index>I_Auto)Buff_index[serial_port]=index;
    FtempIndex[serial_port] = 0;
    tx_float[serial_port] = 0;
    tx_temp[serial_port] = 0;

    float_out[serial_port][0] = ' ';
    if (f_data < 0){
        f_data *= -1;                       //Convert to absolute value.
        float_out[serial_port][0] = '-';    //Put a - in first char
    }
    f_data += 0.00001;
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
    writingbuff[serial_port] = no;
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
    if(BD==0)BD=9600; //Prevent divide by zero, default to 9600 baud.
    float INS = mlt * 1000000;
    float OutPut = ((INS/BD)/16)-1;
    unsigned int Oputs = OutPut;
    return Oputs;             //Weird things happen when you try to calculate
                              //a float directly into an int. Don't do this.
    /************************/
}

#endif
