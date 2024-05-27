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

#ifndef pwropt_C
#define pwropt_C

#include "poweroptions.h"
#include "common.h"
//Notes:
//void Send_I2C(int offset, int size, char address, char command)
//void Receive_I2C(int size, char address, char command)
//IC_Packet[IC_PACK_SIZE]

int Get_PD_Sources(void){
    if(dsky.Cin_voltage<3)return 0;
    Receive_I2C(1, USBPD_Addr, PD_Valid_Source);    //Get number of PD options.
    PD_Src_Count = IC_Packet[0];
    if(PD_Src_Count==0) return 0;
    Receive_I2C(28, USBPD_Addr, PD_PDO);            //Get PD options.
    return 1;
}

int Calc_PD_Option(unsigned char opt_num){
    opt_num*=4; //calculate index.
    if(PD_Src_Count==0) return 0; //Don't bother if there is nothing there to report.
    unsigned int temp_PD = ((IC_Packet[opt_num+1]>>2)&0x3F)+((IC_Packet[opt_num+2]&0x0F)<<6);
    float tempF_PD = temp_PD;
    PD_Last_Voltage = tempF_PD*0.05;
    //Now do current
    temp_PD = IC_Packet[opt_num+0]+((IC_Packet[opt_num+1]&0x03)<<8);
    tempF_PD = temp_PD;
    PD_Last_Current = tempF_PD*0.01;
    return 1;
}

int Get_Highest_PD(void){
    if(dsky.Cin_voltage<3)return 0;
    if(Get_PD_Sources()==0)return -1;   //Can't get PD sources.
    float highestPD = 0;
    unsigned char H_PD_Num=0;
    for(int i=0;i<PD_Src_Count;i++){
        if(!Calc_PD_Option(i))return 0;
        if(PD_Last_Voltage*PD_Last_Current>highestPD){
            highestPD=PD_Last_Voltage*PD_Last_Current;
            H_PD_Num=i;
        }
    }
    if(Get_PD_Sources()==0)return -1;   //Re-Get PD sources.
    if(!Calc_PD_Option(H_PD_Num))return 0;  //Store the selected PD source parameters.
    return H_PD_Num;
}

int Get_Lowest_PD_Voltage(void){
    if(dsky.Cin_voltage<3)return 0;
    if(Get_PD_Sources()==0)return -1;   //Can't get PD sources.
    float LowestPD = 100;
    unsigned char L_PD_Num=0;
    for(int i=0;i<PD_Src_Count;i++){
        if(!Calc_PD_Option(i))return 0;
        if(PD_Last_Voltage<LowestPD){
            LowestPD=PD_Last_Voltage;
            L_PD_Num=i;
        }
    }
    if(Get_PD_Sources()==0)return -1;   //Re-Get PD sources.
    if(!Calc_PD_Option(L_PD_Num))return 0;  //Store the selected PD source parameters.
    return L_PD_Num;
}

void Last_PD(int serial_port){
    load_float(PD_Last_Voltage, serial_port);
    load_string("V :: ", serial_port);
    load_float(PD_Last_Current, serial_port);
    load_string("A", serial_port);
    send_string("\n\r", serial_port);
}

void List_PD_Options(int serial_port){
    load_string("\n\rUSB-PD modes available with this charger: \n\r", serial_port);
    if(!Get_PD_Sources() || dsky.Cin_voltage<3){
        load_string("\n\rNo PD sources.", serial_port);
        return;
    }
    for(int i=0;i<PD_Src_Count;i++){
        if(!Calc_PD_Option(i)){
            load_string("\n\rPD source error.", serial_port);
            break;
        }
        Last_PD(serial_port);
    }
}

int Set_PD_Option(unsigned char opt_num){
    ch_boost_power=0;
    charge_power=0;
    if(dsky.Cin_voltage<3)return 0;
    if(Get_PD_Sources()==0)return 0;//Don't bother if there is nothing there to set.
    if(opt_num>PD_Src_Count)return 0; //If invalid source then don't bother trying.
    unsigned int opt_index=opt_num*4; //calculate index.
    IC_Packet[opt_index+3]=(opt_num+1)<<4;
    
    unsigned int temp_PD = IC_Packet[opt_index]+((IC_Packet[opt_index+1]&0x03)<<8);
    
    IC_Packet[opt_index+1]=(IC_Packet[opt_index+1]&0x03)|((temp_PD<<2)&0xFC);
    IC_Packet[opt_index+2]=((temp_PD>>6)&0x0F);
    
    Send_I2C(opt_index, 4, USBPD_Addr, PD_ReqDO); //Dispatch the data.
    Receive_I2C(1, USBPD_Addr, PD_Status); //Get status
    PD_Last_Status = IC_Packet[0];
    if((PD_Last_Status&0x03)==0x03)return 1;  //Success
    return 2;   //Fail
}


#endif