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

#ifndef DATAIRQS_C
#define DATAIRQS_C

#include "IRQs.h"
#include "common.h"
#include "DataIO.h"
#include "Init.h"
#include "display.h"
#include "eeprom.h"
#include "checksum.h"

/*****************/
/* IRQs go here. */
/*****************/

void Deep_Sleep_timer_reset(void){
    DeepSleepTimer = sets.DeepSleepAfter-1;      //reset the timer when main_power is on.
    DeepSleepTimerSec = 59;                   //60 seconds.
}

/* Non time-critical systems. Timer 4 IRQ. 1 Second.*/
//For low priority CPU intensive processes and checks.
void __attribute__((interrupt, no_auto_psv)) _T4Interrupt (void){
    IFS1bits.T4IF = clear;
    if(Auto_Eval > 0){
        if(dsky.chrg_percent>99.8 && !CONDbits.Chrg_Inhibit){
            print_info(no, -1, PORT1);
            print_info(no, -1, PORT2);
            send_string(I_Auto, Eval_Discharging, PORT1);
            send_string(I_Auto, Eval_Discharging, PORT2);
            chargeInhibit(yes);
            CONDbits.Power_Out_EN = on;
        }
        else if(dsky.chrg_percent<Eval_Start && CONDbits.Chrg_Inhibit && !CONDbits.Power_Out_EN){
            print_info(no, -1, PORT1);
            print_info(no, -1, PORT2);
            send_string(I_Auto, Eval_Charging, PORT1);
            send_string(I_Auto, Eval_Charging, PORT2);
            chargeInhibit(no);
            CONDbits.Power_Out_EN = off;
            Auto_Eval--;
            if(Auto_Eval==0){
                send_string(I_Auto, Eval_Finished, PORT1);
                send_string(I_Auto, Eval_Finished, PORT2);
            }
            Full_Charge();
        }
        //Load used has shutdown before auto evaluation could complete. Aborted.
        else if((dsky.chrg_percent>25 && CONDbits.Chrg_Inhibit && !CONDbits.Power_Out_EN)){
            print_info(no, -1, PORT1);
            print_info(no, -1, PORT2);
            send_string(I_Auto, Eval_Error, PORT1);
            send_string(I_Auto, Eval_Error, PORT2);
            chargeInhibit(no);
            CONDbits.Power_Out_EN = off;
            fault_log(0x44, 0x00);
            Auto_Eval = 0;
        }
        //Charger or power parameters don't line up for Evaluation. Aborting.
        else if((!CONDbits.Chrg_Inhibit && CONDbits.Power_Out_EN) || (dsky.Cin_voltage<C_Min_Voltage)){
            if(!CONDbits.Chrg_Inhibit && CONDbits.Power_Out_EN)fault_log(0x45, 0x01);
            else if((dsky.Cin_voltage<C_Min_Voltage))fault_log(0x45, 0x02);
            else fault_log(0x45, 0x03);
            print_info(no, -1, PORT1);
            print_info(no, -1, PORT2);
            send_string(I_Auto, Eval_Error, PORT1);
            send_string(I_Auto, Eval_Error, PORT2);
            chargeInhibit(no);
            CONDbits.Power_Out_EN = off;
            Auto_Eval = 0;
        }
    }
    /* Deep Sleep TIMER stuff. Do this to save power.
     * This is so that this system doesn't drain your 1000wh battery over the
     * course of a couple weeks while being unplugged from a charger.
     * The dsPIC30F3011 is a power hog even in Idle and Sleep modes.
     * For future people, KEEP USING IRQs FOR STUFF!!! Don't make the CPU wait
     * for anything! The dsPIC30F3011 is a power drain and will consume all
     * your electrons and burn your lunch and house down from the heat that it generates! */
    if(Run_Level > Cal_Mode && Run_Level != On_W_Err){
        if(STINGbits.OverCRNT_Fault){
            //If there has been a hardware over-current event then we need to power off sooner to reset the OC latches.
            DeepSleepTimer=0;
            DeepSleepTimerSec = 5;
        }
        else {
            Deep_Sleep_timer_reset();
        }
    }
    //Run_Level is at Heartbeat or below. Start counting down.
    else if (sets.DeepSleepAfter > -1){
        //When main_power is off count down in minutes.
        if(DeepSleepTimerSec <= 0){
            DeepSleepTimerSec = 59;
            if(DeepSleepTimer <= 0) STINGbits.deep_sleep = 1; //set deep_sleep to 1. Power off the system to save power after all IRQ's are finished.
            else DeepSleepTimer--;
        }
        else DeepSleepTimerSec--;
    }
    //Auto power off stuff
    float C_Curnt_test = 0;
    if(dsky.Cin_current>0)C_Curnt_test = ch_crnt_avg;
    float W_Diff_Test = dsky.battery_crnt_average*dsky.pack_vltg_average - C_Curnt_test*ch_vltg_avg;
    if(CONDbits.Power_Out_EN && (sets.auto_off_watts > -1) && ((-1*W_Diff_Test) < sets.auto_off_watts)){
        if(PowerOffTimerSec <= 0){
            if(PowerOffTimer <= 0){
                CONDbits.Power_Out_EN = 0;  //Turn off the power.
                CONDbits.Power_Out_Lock = 1; //Keep other processes from turning the power back on right away.
            }
            else {
                PowerOffTimer--;
                PowerOffTimerSec = 59;
            }
        }
        PowerOffTimerSec--;
    }
    else {
        PowerOffTimer = sets.PowerOffAfter-1;
        PowerOffTimerSec = 59;
    }
    //Runtime program memory check. Checks every half hour except on startup it will run after 10 seconds.
    if(check_timer == 1800 && Run_Level > Crit_Err){
        if(check_prog() == 1) Run_Level=Crit_Err;  //Program memory is corrupted and cannot be trusted.
        check_timer = clear;
    }
    else if(Run_Level > Crit_Err) check_timer++;
    //Check settings ram in background. (lowest priority IRQ))
    //Don't check if in Calibration mode because some setting might be changing on the fly.
    if(Run_Level != Cal_Mode && Run_Level > Crit_Err && check_timer){
        if(check_ramSets()){
            //If failed, attempt to recover.
            get_settings();
            //Make no more than 5 attempts to recover before going into debug mode.
            if(ram_err_count >= 5) Run_Level=Crit_Err; //Settings memory is corrupted and cannot be trusted.
            else ram_err_count++;
        }
    }
    //Determine how many cells the battery pack has if it hasn't been determined yet and we are in cal run_time.
    if(Run_Level == Cal_Mode && sets.Cell_Count < 2 && !CONDbits.V_Cal && avg_rdy > 0){
        if(Cell_Voltage_Average[1]>0.5)sets.Cell_Count=2;
        if(Cell_Voltage_Average[2]>0.5)sets.Cell_Count=3;
        if(Cell_Voltage_Average[3]>0.5)sets.Cell_Count=4;
        save_sets();
    }
    //End IRQ
}

//Another Heavy process IRQ
//For low priority CPU intensive processes and checks, and 1/16th second non-critical timing.
void __attribute__((interrupt, no_auto_psv)) _T5Interrupt (void){
    IFS1bits.T5IF = clear;
    //Blink some LEDs
    BlinknLights++; //Count up all the time once every 1/8 second.
    //Do display stuff.
    displayOut(PORT1);
    displayOut(PORT2);
    //End IRQ
}

/**********************************************************************************************************************/
/**********************************************************************************************************************/
/* Data and Command input and processing IRQ for Port 1 */
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt (void){
    IFS0bits.U1RXIF = clear;
    if(U1STAbits.URXDA)Command_Interp(PORT1);
/****************************************/
    Deep_Sleep_timer_reset(); //if in cal mode, reset timer after every byte received via serial.
    /* End the IRQ. */
}

/* Data and Command input and processing IRQ for Port 2. */
void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt (void){
    IFS1bits.U2RXIF = clear;
    if(U2STAbits.URXDA)Command_Interp(PORT2);
/****************************************/
    Deep_Sleep_timer_reset(); //if in cal mode, reset timer after every byte received via serial.
    /* End the IRQ. */
}

/**********************************************************************************************************************/
//Data dispatch complete, reset everything.
void Buffrst(int serial_port){
    if (Buffer[serial_port][B_Out_index[serial_port]] == NULL){
        B_Out_index[serial_port] = clear;    //Reset the buffer index.
        portBSY[serial_port] = clear;  //Inhibits writing to buffer while the serial port is transmitting.
    }
}

/* Output IRQ for Port 1 */
void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt (void){
    IFS0bits.U1TXIF = clear;
    //Dispatch the buffer to the little 4 word Serial Port buffer as it empties.
    while(!U1STAbits.UTXBF && (Buffer[PORT1][B_Out_index[PORT1]] != NULL) && portBSY[PORT1]){
        U1TXREG = Buffer[PORT1][B_Out_index[PORT1]];
        B_Out_index[PORT1]++;
    }
    //Reset the buffer index and count when done sending.
    Buffrst(PORT1);
    /****************************************/
    /* End the IRQ. */
}

/* Output IRQ for Port 2 */
void __attribute__((interrupt, no_auto_psv)) _U2TXInterrupt (void){
    IFS1bits.U2TXIF = clear;
    //Dispatch the buffer to the little 4 word Serial Port buffer as it empties.
    while(!U2STAbits.UTXBF && (Buffer[PORT2][B_Out_index[PORT2]] != NULL) && portBSY[PORT2]){
        U2TXREG = Buffer[PORT2][B_Out_index[PORT2]];
        B_Out_index[PORT2]++;
    }
    //Reset the buffer index and count when done sending.
    Buffrst(PORT2);
    /****************************************/
    /* End the IRQ. */
}

/* I2C stuff */
/***************************************************************************/
/*
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
*/

void clear_I2C_Buffer(void){
    for(int i=0;i<IC_PACK_SIZE;i++)IC_Packet[i]=0;
}

void Send_I2C(unsigned int offset, unsigned int size, unsigned char address, unsigned char command){
    if(IC_Seq==0 && Run_Level>Crit_Err){
        int hi = I2CRCV;  //Reading this clears it out.
        hi+=1;      //Force the compiler to not remove this variable.
        I2CCON = 0;
        I2CSTAT = 0;
        I2CBRG = 0x1FF;
        CONDbits.IC_RW = MD_Send;
        IC_Seq=IC_start;        //Init sequence
        I2CCONbits.I2CEN = 1;   //enable I2C interface
        IC_Pack_Size = size+offset; //Load size of packet.
        IC_Pack_Index=offset;   //Set buffer index.
        IC_Address = address;   //Load address of chip we want to send to.
        IC_Command = command;   //Load command we want to send.
        IC_Timer = 16;  //2 seconds for timeout.
        IFS0bits.MI2CIF = set;  //Kick off the IRQ
        while(IC_Seq!=0){
            if(dsky.Cin_voltage<3)break;
            Idle(); //Wait for completion.
        }
        clear_I2C_Buffer();     //Clear buffer.
    }
}

void Receive_I2C(unsigned int size, unsigned char address, unsigned char command){
    if(IC_Seq==0 && Run_Level>Crit_Err){
        IC_Packet[0] = I2CRCV;  //Reading this clears it out.
        I2CCON = 0;
        I2CSTAT = 0;
        I2CBRG = 0x1FF;
        clear_I2C_Buffer();     //Clear buffer.
        CONDbits.IC_RW = MD_Recieve;
        IC_Seq=IC_start;        //Init sequence
        I2CCONbits.I2CEN = 1;   //enable I2C interface
        IC_Pack_Size = size;    //Load size of packet expected.
        IC_Pack_Index=0;        //Reset buffer index.
        IC_Address = address;   //Load address of chip we want to send to.
        IC_Command = command;   //Load command we want to send.
        IC_Timer = 16;  //2 seconds for timeout.
        IFS0bits.MI2CIF = set;  //Kick off the IRQ
        while(IC_Seq!=0){
            if(dsky.Cin_voltage<3)break;
            Idle(); //Wait for completion.
        }
    }
}



void __attribute__((interrupt, no_auto_psv)) _MI2CInterrupt (void){
    IFS0bits.MI2CIF = clear;
    /****************************************/
    for(int i=0;i<10;i++)Idle();
    if(I2CSTATbits.IWCOL){
        fault_log(0x41, IC_Seq);   //Log a write collision error.
        I2CSTATbits.IWCOL = 0;
        IC_Seq = clear;
         I2CCONbits.PEN = set;
    }
    else {
        switch(IC_Seq){
            //Send start bit
            case IC_start:  //2
                if(!I2CCONbits.SEN)I2CCONbits.SEN = set;
                //else if(I2CSTATbits.S && !I2CSTATbits.P){fault_log(0x3F, 0xF0); IC_Seq=clear; break;}
                else if(I2CSTATbits.S){fault_log(0x3F, 0xF1); IC_Seq=clear; break;}
                //else if(!I2CSTATbits.P){fault_log(0x3F, 0xF2); IC_Seq=clear; break;}
                else {fault_log(0x3F, IC_Seq); IC_Seq=clear; break;}
                //Check if writing, if so then skip to rpt_slv_adr on next IRQ.
                IC_Seq++;
                IC_Timer = 16;  //2 seconds for timeout.
            break;
            //Send slave address
            case slv_adr: //3
                I2CTRN = (IC_Address*2);//Send address with write bit
                IC_Seq++;
                IC_Timer = 16;  //2 seconds for timeout.
            break;
            //Check ACK from slave
            case slv_ack: //4
                if(I2CSTATbits.ACKSTAT){fault_log(0x43, IC_Seq); IC_Seq=clear; IC_Timer = -1; break;}
                IC_Seq++;
                IC_Timer = 16;  //2 seconds for timeout.
            //break; //Do not break. Receiving an ACK does not generate an IRQ.
            //Send command
            case cmd_adr: //5
                I2CTRN = IC_Command;
                IC_Timer = 16;  //2 seconds for timeout.
                if(CONDbits.IC_RW == MD_Send)IC_Seq = rpt_slv_ack;
                else IC_Seq++;
            break;
            //Check ACK from slave
            case cmd_ack: //6
                if(I2CSTATbits.ACKSTAT){fault_log(0x43, IC_Seq); IC_Seq=clear; IC_Timer = -1; break;}
                IC_Seq++;
                IC_Timer = 16;  //2 seconds for timeout.
            //break; //Do not break. Receiving an ACK does not generate an IRQ.
            //Send repeat start sequence
            case rpt_strt: //7
                //if(CONDbits.IC_RW == MD_Send)load_string("F",PORT2);
                I2CCONbits.RSEN = set;
                IC_Seq++;
                IC_Timer = 16;  //2 seconds for timeout.
            break;
            //Send slave address
            case rpt_slv_adr: //8
                if(CONDbits.IC_RW == MD_Send)I2CTRN = (IC_Address*2);  //Write, last bit is 0
                else I2CTRN = (IC_Address*2)|0x01;          //Read, last bit is 1
                IC_Seq++;
                IC_Timer = 16;  //2 seconds for timeout.
            break;
            //Check ACK from slave
            case rpt_slv_ack: //9
                if(I2CSTATbits.ACKSTAT){fault_log(0x43, IC_Seq); IC_Seq=clear; IC_Timer = -1; break;}
                IC_Seq++;
                IC_Timer = 16;  //2 seconds for timeout.
                if(CONDbits.IC_RW == MD_Recieve){
                    I2CCONbits.RCEN = MD_Recieve;
                    CONDbits.IC_ACK=set;
                    break; //Only break if receiving.
                }
            //Setting I2CCONbits.RCEN to read mode will cause an IRQ when read data is ready.
            //Send/receive data to/from slave
            case slv_data: //10 0x0A
                //Read
                if(CONDbits.IC_RW == MD_Recieve && IC_Pack_Index < IC_Pack_Size && IC_Pack_Index < IC_PACK_SIZE){
                    if(CONDbits.IC_ACK==set){
                        IC_Packet[IC_Pack_Index] = I2CRCV;
                        //Do ACK thing.
                        if(IC_Pack_Index == IC_Pack_Size-1){
                            I2CCONbits.ACKDT = set;                                //Send NACK to signal end of data to slave.
                            IC_Seq=IC_stop;                                        //After a NACK we go straight to stop sequence on next IRQ.
                        }
                        else I2CCONbits.ACKDT = clear;                             //Send ACK to signal we are still expecting more data from slave.
                        I2CCONbits.ACKEN = set;                                    //Now actually send that info.
                        CONDbits.IC_ACK=clear;                                     //Do read sequence on next IRQ.
                        IC_Pack_Index++;
                    }
                    else if(IC_Pack_Index < IC_Pack_Size) {
                        CONDbits.IC_ACK=set;                                       //Do ACK sequence on next IRQ.
                        I2CCONbits.RCEN = MD_Recieve;
                    }
                    break;
                }
                //write
                else if(CONDbits.IC_RW == MD_Send && IC_Pack_Index < IC_Pack_Size && IC_Pack_Index < IC_PACK_SIZE){
                    I2CTRN = IC_Packet[IC_Pack_Index];
                    //I2CTRN = 0x5F;
                    IC_Seq--;
                    IC_Pack_Index++;
                    break;
                }
                else IC_Seq++;
                IC_Timer = 16;  //2 seconds for timeout.
            //Do not break here.
            //Check for ACK
            case data_ack: //11 0x0B
                if(I2CSTATbits.ACKSTAT){fault_log(0x43, IC_Seq); IC_Seq=clear; IC_Timer = -1; break;}
                IC_Seq++;
                IC_Timer = 16;  //2 seconds for timeout.
            //Do not break here.
            //Send stop sequence
            case IC_stop: //12 0x0C
                I2CCONbits.ACKDT = clear;
                I2CCONbits.PEN = set;
                IC_Seq++;
                IC_Timer = 16;  //2 seconds for timeout.
            //break;    //eh, who cares
            default:
                IC_Seq = clear;
                IC_Timer = -1;  //Set to idle.
                I2CCONbits.I2CEN = 0;   //disable I2C interface
            break;
        }
    }
    /* End the IRQ. */
}

void __attribute__((interrupt, no_auto_psv)) _SI2CInterrupt (void){
    /****************************************/
    /* End the IRQ. */
    IFS0bits.SI2CIF = clear;
}

/****************/
/* END IRQs     */
/****************/

#endif
