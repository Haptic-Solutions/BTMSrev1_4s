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

#ifndef DKSY_C
#define DKSY_C

#include "common.h"
#include "display.h"
#include "DataIO.h"
#include "errorCodes.h"
#include "eeprom.h"
#include "checksum.h"
#include "poweroptions.h"



void C_Point_CHK(int serial_port){
    if(CMD_Point[serial_port] < 0)CMD_Point[serial_port]=0;
    if(CMD_Point[serial_port] >= Clength)CMD_Point[serial_port]=0;
}

//Loads one of the serial buffers with user defined data and then dispatches it.
void pageOut(int pageNum, int serial_port){
    dodispatch[serial_port] = no;
    for(pageVar[serial_port]=0;pageVar[serial_port]<6;pageVar[serial_port]++){
        varNum[serial_port] = sets.page[serial_port][pageNum][pageVar[serial_port]];
        varNum[serial_port] &= 0xFF;
        if(varNum[serial_port] < signStart)dynaSpace[serial_port] = yes;       //Do not reserve a space for a sign char if we don't have to.
        if(varNum[serial_port] == wattsNum)config_space[serial_port] = yes;   //Reserve spaces for 0's when showing watts so that text isn't jumping around.
        //Skip page if first Var is listed as NULL, or if we get a NULL later then we are done.
        if(varNum[serial_port] == 0)break;
        //Check if loading custom data or not.
        if(varNum[serial_port] > 0x00FB){
            switch(varNum[serial_port]){
                case 0x00FC:
                    load_string(I_Auto, sets.custom_data1, serial_port);
                break;
                case 0x00FD:
                    load_string(I_Auto, sets.custom_data2, serial_port);
                break;
                case 0x00FE:
                    load_string(I_Auto, sets.custom_data3, serial_port);
                break;
                case 0x00FF:
                    load_string(I_Auto, sets.custom_data4, serial_port);
                break;
            }
            dodispatch[serial_port] = yes; //if we have at least one variable to display then dispatch.
        }
        else if(varNum[serial_port] == nlNum){
            load_string(I_Auto, "\n\r", serial_port);
            dodispatch[serial_port] = yes; //if we have at least one variable to display then dispatch.
        }
        else if(varNum[serial_port] < varLimit){
            if(varNum[serial_port] != nlNum)load_float(I_Auto, 0.01+dsky.dskyarrayFloat[varNum[serial_port]], serial_port);   //Load the number.
            Buff_index[serial_port] -= 2;  //Subtract 2 from buffer index.
            load_const_string(I_Auto, Vlookup[varNum[serial_port]], serial_port);        //Load the number's text.
            load_string(I_Auto, " ", serial_port);  //Load a space after everything.
            dodispatch[serial_port] = yes; //if we have at least one variable to display then dispatch.
        }
    }
    if (dodispatch[serial_port]){
        dispatch_Serial(serial_port);
    }
}

void displayOut(int serial_port){
    if(sets.PxVenable[serial_port] && !portBSY[serial_port] && Run_Level == All_Sys_Go){
        if(PxVtimer[serial_port] == 0){
            pageOut(PxPage[serial_port], serial_port);
            PxVtimer[serial_port] = sets.pageDelay[serial_port][PxPage[serial_port]] - 1;
            if (PxVtimer[serial_port] < 0) PxVtimer[serial_port] = 0;
            if(PxPage[serial_port] < 4 && sets.page[serial_port][PxPage[serial_port]][0]) PxPage[serial_port]++; //If we get a NULL for first variable then skip go back to page 0
            else PxPage[serial_port] = 0;
        }
        else PxVtimer[serial_port]--;
    }
}

/* Read fault codes to serial port.
 * This takes up about 2% of program space.*/
void fault_read(int serial_port){
    send_string(I_Auto, "\n\rReading Faults.\n\r", serial_port);
    if(vars.fault_count > maxFCodes){
        send_string(I_Auto, "Fault Log Full.\n\r", serial_port);
    }
    if(vars.fault_count == 0){
        send_string(I_Auto, "No fault codes.\n\r", serial_port);
    }
    else{
        for(flt_index[serial_port]=0;flt_index[serial_port]<vars.fault_count;flt_index[serial_port]++){
            port_Busy_Idle(serial_port);  //Check to see if port is ready.
            load_string(I_Auto, "Code: ", serial_port);
            load_hex(I_Auto, vars.fault_codes[0][flt_index[serial_port]],serial_port);
            load_string(I_Auto, " :: Attribute: ", serial_port);
            load_hex(I_Auto, vars.fault_codes[1][flt_index[serial_port]], serial_port);
            load_string(I_Auto, " -> ", serial_port);
            int ecode = vars.fault_codes[0][flt_index[serial_port]];
            if(!ecode || ecode < sizeof(errArray))load_const_string(I_Auto, errArray[ecode-1], serial_port);
            else load_const_string(I_Auto, codeDefault, serial_port);
            send_string(I_Auto, "\n\r", serial_port);
        }
    }
    port_Busy_Idle(serial_port);
    send_string(I_Auto, "\n\r", serial_port);
    send_string(I_Auto, "Flags::|Sets LK||Batt OV||Batt HV|", serial_port);
    send_string(I_Auto, "|Batt UV||Batt OT||Sys OT|\n\r", serial_port);
    send_string(I_Auto, "        ", serial_port);
    unsigned char flagMask = 0x01;
    for(int i=0;i<6;i++){
        if(Flags&flagMask)load_string(I_Auto, "SET      ", serial_port);
        else load_string(I_Auto, "Clear    ", serial_port);
        flagMask*=2; //Shift the bit left by one.
    }
    send_string(I_Auto, "\n\r", serial_port);
}

char load_line(char offset, char flip_line, int serial_port){
    load_string(5, " ", serial_port);
    if(flip_line){load_string(7+offset, "-------------------::", serial_port);flip_line=0;}
    else {load_string(7+offset, "~~~~~~~~~~~~~~~~~~~::", serial_port);flip_line=1;}
    return flip_line;
}

void print_info(char quiet, int set_num, int serial_port){
    if(!quiet)send_string(0, "\n\rIndx: Variable:                    Value:\n\r", serial_port);
    if(set_num<-1 || set_num > 38)set_num=38;   //Set to unknown variable.
    char flip_line = 0;
    int i=0;
    int l_s=22;
    int strt=0;
    if(set_num>-1){i=set_num;l_s=set_num+1;} 
    while(i<l_s){
        if(!quiet){
            load_int(0, i, serial_port);    //Load setting number.
            flip_line = load_line(6, flip_line, serial_port);   //Load alternating lines patterns.
            load_const_string(6, varsNames[i], serial_port);    //Load variables text.
            strt=34;
        }
        if(i<19)load_float(strt, dsky.dskyarrayFloat[varsArray[i]], serial_port);
        else if(i<21)load_float(strt, vars.variablesFloat[varsArray[i]], serial_port);
        else if(i==21)load_float(strt, vars.variablesArray[varsArray[i]], serial_port);
        send_string(I_Auto, "\n\r", serial_port);
        i++;
    }
}

//Check if a setting is locked
int check_setlock(int i){
    if(i>37||(i!=18 && i!=7 && i<34 && (Flags&syslock)))return 1;
    else return 0;
}

void print_settings(char quiet, int set_num, int serial_port){
    if(!quiet)send_string(0, "\n\rIndx: Setting:                     Value: Editable:\n\r", serial_port);
    if(set_num<-1 || set_num > 38)set_num=38;   //Set to unknown variable.
    char flip_line = 0;
    int i=0;
    int l_s=38;
    int strt=0;
    if(set_num>-1){i=set_num;l_s=set_num+1;} 
    while(i<l_s){
        if(!quiet){
            load_int(0, i, serial_port);    //Load setting number.
            flip_line = load_line(6, flip_line, serial_port);   //Load alternating lines patterns.
            load_const_string(6, setsNames[i], serial_port);    //Load settings text.
            strt=34;
        }
        if(i<19)load_float(strt, sets.settingsFloat[setsArray[i]], serial_port);      //Load one of two types of data.
        else if(i<38)load_float(strt, sets.settingsINT[setsArray[i]], serial_port);
        if(!quiet){
            if(check_setlock(i))load_string(41, " LOCKED", serial_port);
            else load_string(41, " UNLOCKED", serial_port);
        }
        send_string(I_Auto, "\n\r", serial_port);
        i++;
    }
}

void edit_settings(char quiet, int set_num, float value, int serial_port){
    send_string(0, "\n\r", serial_port);
    int I_value = value;
    if(set_num<0 || set_num > 37){
        send_string(0, "\n\rInvalid setting index. Nothing changed.", serial_port);
        return;
    }
    if(setsLimits[set_num]!=0)load_string(0, "\n\rLimit is no ", serial_port);
    if(setsLimits[set_num]>0){load_string(I_Auto, "more than:", serial_port);load_float(I_Auto, setsLimits[set_num], serial_port);}
    else if(setsLimits[set_num]<0){load_string(I_Auto, "less than:", serial_port);load_float(I_Auto, setsLimits[set_num]*-1, serial_port);}
    send_string(I_Auto, "\n\r", serial_port);
    if(check_setlock(set_num)){send_string(I_Auto, "\n\rCannot change. Setting LOCKED", serial_port);return;}
    if(setsLimits[set_num]>0 && setsLimits[set_num]<value){send_string(I_Auto, "\n\rOver safe limit. Abort.", serial_port);return;}
    else if(setsLimits[set_num]<0 && (setsLimits[set_num]*-1)>value){send_string(I_Auto, "\n\rUnder safe limit. Abort.", serial_port);return;}
    chargeInhibit(yes); //Stop charge routine for a moment.
    send_string(0, "\n\rSetting was:", serial_port);
    print_settings(quiet, set_num, serial_port);
    if(set_num<19)sets.settingsFloat[setsArray[set_num]]=value;      //Load one of two types of data.
    else if(set_num<38)sets.settingsINT[setsArray[set_num]]=I_value;
    send_string(0, "\n\r-->Is now:", serial_port);
    print_settings(quiet, set_num, serial_port);
    save_sets();
    chargeInhibit(no); //Restart charge routine.
}

void setsLockedErr(int serial_port){
    load_string(I_Auto, "Unable: Settings Locked.\n\r", serial_port);
}

void setsUnlockedErr(int serial_port){
    load_string(I_Auto, "Unable: Settings Need To Be Locked.\n\r", serial_port);
}

void Command_Interp(int serial_port){
    //Get data. Get allll the data.
    while (((serial_port == PORT1 && U1STAbits.URXDA) || (serial_port == PORT2 && U2STAbits.URXDA)) && !cmdRDY[serial_port]){
        C_Point_CHK(serial_port);
        //Data input
        if(serial_port)CMD_buff[serial_port][CMD_Point[serial_port]] = U2RXREG;
        else CMD_buff[serial_port][CMD_Point[serial_port]] = U1RXREG;
        //Data echo. Do not echo Returns, NLs, or Backspace
        if ((CMD_buff[serial_port][CMD_Point[serial_port]] != 0x0D) &&
            (CMD_buff[serial_port][CMD_Point[serial_port]] != 0x0A) &&
            (CMD_buff[serial_port][CMD_Point[serial_port]] != 0x08)){
            if(serial_port==PORT2 && CONDbits.Port2_Echo)U2TXREG = CMD_buff[serial_port][CMD_Point[serial_port]];
            else if(CONDbits.Port1_Echo) U1TXREG = CMD_buff[serial_port][CMD_Point[serial_port]];
        }
        //Check for a RETURN
        char cmdinput = CMD_buff[serial_port][CMD_Point[serial_port]];
        if (cmdinput == 0x0D || cmdinput == 0x0A){
            bufsize[serial_port] = CMD_Point[serial_port];
            CMD_Point[serial_port] = clear;
            cmdRDY[serial_port] = set; //Tell our command handler to process.
        }
        //Check for BACKSPACE
        else if(cmdinput==0x08){
            if(CMD_Point[serial_port]>0){
                CMD_buff[serial_port][CMD_Point[serial_port]] = ' ';    //Actually erase it from the input buffer.
                CMD_Point[serial_port]--;
                //Erase last character and move back by one.
                if((serial_port==PORT1 && CONDbits.Port1_Echo)||(serial_port==PORT2 && CONDbits.Port2_Echo))send_string(0, "\b \b", serial_port);
            }
            else send_string(0, "\a", serial_port);
        }
        //No RETURN or BACKSPACE detected? Store the data.
        else if(CMD_Point[serial_port] < Clength)CMD_Point[serial_port]++;
    }
    //Command Handler.
    if (cmdRDY[serial_port]){
        //load_string(I_Default, "\n\r", serial_port);
        int stat=0;
        int cmd_attrib1=0;
        int cmd_attrib2=0;
        switch(CMD_buff[serial_port][tempPoint[serial_port]]){
            case '\r':
            break;
            case '\n':
            break;
            case 'b':
                List_PD_Options(serial_port);
            break;
            case 'V':
                stat = Set_PD_Option(Get_Highest_PD());
                if(stat==1){
                    load_string(I_Auto, "\n\r Set highest wattage PD success.\n\r", serial_port);
                    Last_PD(serial_port);
                    Max_Charger_Current=PD_Last_Current*charge_Max_Level;   //Don't run charger more than this capacity.
                    Charger_Target_Voltage = PD_Last_Voltage-(10/PD_Last_Current);  //Calculate max heat loss allowed through cable and connections.
                    charge_mode = USB3;
                }
                else if(stat==2) {
                    load_string(I_Auto, "\n\r Set highest wattage PD FAILED. PD-Status: ", serial_port);
                    load_hex(I_Auto, PD_Last_Status, serial_port);
                }
                else load_string(I_Auto, "\n\r Can't talk with PD controller.", serial_port);
            break;
            case 'v':
                stat = Set_PD_Option(Get_Lowest_PD_Voltage());
                if(stat==1){
                    load_string(I_Auto, "\n\r Set lowest voltage PD success.\n\r", serial_port);
                    Last_PD(serial_port);
                    Max_Charger_Current=PD_Last_Current*charge_Max_Level;   //Don't run charger more than this capacity.
                    Charger_Target_Voltage = PD_Last_Voltage-(10/PD_Last_Current);  //Calculate max heat loss allowed through cable and connections.
                    charge_mode = USB3_Wimp;
                }
                else if(stat==2) {
                    load_string(I_Auto, "\n\r Set lowest voltage PD FAILED. PD-Status: ", serial_port);
                    load_hex(I_Auto, PD_Last_Status, serial_port);
                }
                else load_string(I_Auto, "\n\r Can't talk with PD controller.", serial_port);
            break;
            case '#':   //Reset the CPU
                if(Flags&syslock){setsLockedErr(serial_port);break;}
                CMD_Point[serial_port] = clear;
                cmdRDY[serial_port] = clear;
                asm("reset");
            break;
            case '$':
                //Generate flash and chip config checksum and compare it to the old one.
                send_string(I_Auto, "\n\rCalculating program checksum, please wait...", serial_port);
                load_string(I_Auto, "\n\rPRG:\n\rStored:", serial_port);
                load_hex(I_Auto, sets.flash_chksum_old, serial_port);
                load_string(I_Auto, "\n\rCalc:  ", serial_port);
                if(check_prog()==2)load_string(I_Auto, "Mem Busy", serial_port);
                else load_hex(I_Auto, flash_chksum, serial_port);
            break;
            case '%':
                //Generate EEPROM checksum and compare it to the old one.
                load_string(I_Auto, "\n\rNVM:\n\rStored:", serial_port);
                load_hex(I_Auto, eeprom_read(0x01FF), serial_port);
                load_string(I_Auto, "\n\rCalc:  ", serial_port);
                if(check_nvmem()==2)load_string(I_Auto, "Mem Busy", serial_port);
                else load_hex(I_Auto, rom_chksum, serial_port);
            break;
            case '~':
                if(Flags&syslock){setsLockedErr(serial_port);break;}
                default_sets(); //Load default Settings.
                save_sets();    //Save them to EEPROM.
                nvm_chksum_update();    //Update EEPROM checksum.
            break;
            case '!': //Clear variables and restart.
                if(Flags&syslock){setsLockedErr(serial_port);break;}
                eeprom_erase(cfg_space);
                nvm_chksum_update();    //Update EEPROM checksum.
                CMD_Point[serial_port] = clear;
                cmdRDY[serial_port] = clear;
                asm("reset");
            break;
            case 'H':
                vars.heat_cal_stage = initialize;
            break;
            case 'h':
                vars.heat_cal_stage = disabled;
                save_vars();
            break;
            case 'S':
                STINGbits.deep_sleep = set;
            break;
            case 'F':
                fault_read(serial_port);          //Read all fault codes.
            break;
            case 'P':
                load_string(I_Auto, "P On", serial_port);
                CONDbits.Power_Out_EN = on;
            break;
            case 'p':
                load_string(I_Auto, "P Off", serial_port);
                v_test = clear;
                CONDbits.Power_Out_EN = off;
            break;
            case 'O':
                load_string(I_Auto, "\n\rHUD On", serial_port);
                sets.PxVenable[serial_port] = on;
                ram_chksum_update();        //Generate new checksum.
            break;
            case 'o':
                load_string(I_Auto, "\n\rHUD Off", serial_port);
                sets.PxVenable[serial_port] = off;
                ram_chksum_update();        //Generate new checksum.
            break;
            case 't':
                load_string(I_Auto, "Time left: ", serial_port);
                load_float(I_Auto, DeepSleepTimer, serial_port);
                load_string(I_Auto, " minutes and ", serial_port);
                load_float(I_Auto, DeepSleepTimerSec, serial_port);
                load_string(I_Auto, " seconds.", serial_port);
            break;
            case 'C':
                vars.fault_count = clear;
                STINGbits.errLight = clear;
                STINGbits.fault_shutdown = clear;
                if(vars.heat_cal_stage != disabled)
                    vars.heat_cal_stage = notrun;
                STINGbits.osc_fail_event = clear;
                if(!(Flags&syslock))Flags=clear;
                save_vars();
                load_string(I_Auto, "\n\rFaults Cleared.", serial_port);
            break;
            case '&':
                if(Flags&syslock){setsLockedErr(serial_port);break;}
                if(Run_Level == Crit_Err)Run_Level = Heartbeat; //Attempt to bring back from critical error.
            break;
            case 'Z':
                load_string(I_Auto, "\n\rDoing a full charge regardless of settings.", serial_port);
                Full_Charge();
            break;
            case '*':   //Print firmware version.
                load_string(I_Auto, version, serial_port);
            break;
            case 'a':   //Abort Automatice battery evaluation.
                load_string(I_Auto, "Automatic battery evaluation Aborted.\n\r", serial_port);
                load_string(I_Auto, "P Off\n\r", serial_port);
                chargeInhibit(no);
                v_test = clear;
                CONDbits.Power_Out_EN = off;
                Auto_Eval = 0;
            break;
            case 'A':   //Start Automatic battery evaluation.
                if(!(Flags&syslock)){setsUnlockedErr(serial_port);break;}
                load_string(I_Auto, "Automatic battery evaluation started. Make sure a small load is connected to output.\n\r", serial_port);
                load_string(I_Auto, "P Off\n\r", serial_port);
                Full_Charge();
                v_test = clear;
                CONDbits.Power_Out_EN = off;
                Auto_Eval = 5;
            break;
            case 'i':   //Print or edit settings
                ADCON1bits.ADON = on;                // turn ADC on
                for(int i=2;i<Clength;i++)if(CMD_buff[serial_port][i]=='q'){cmd_attrib1=1;break;}
                if(CMD_buff[serial_port][2]!=' ')print_info(cmd_attrib1, Get_Float(2, serial_port), serial_port);
                else print_info(cmd_attrib1, -1, serial_port);
            break;
            case 'e':   //Print settings
                for(int i=2;i<Clength;i++)if(CMD_buff[serial_port][i]=='q'){cmd_attrib1=1;break;}
                if(CMD_buff[serial_port][2]!=' ')print_settings(cmd_attrib1, Get_Float(2, serial_port), serial_port);
                else print_settings(cmd_attrib1, -1, serial_port);
            break;
            case 'E':   //Edit a setting.
                for(int i=2;i<Clength;i++)if(CMD_buff[serial_port][i]=='q'){cmd_attrib1=1;break;}
                for(int i=2;i<Clength;i++)if(CMD_buff[serial_port][i]==' '){cmd_attrib2=i+1;break;}
                if(CMD_buff[serial_port][1]==' ' && CMD_buff[serial_port][2]!=' ' &&
                   CMD_buff[serial_port][cmd_attrib2]>='0' && CMD_buff[serial_port][cmd_attrib2]<='9'){
                    edit_settings(cmd_attrib1, Get_Float(2, serial_port), Get_Float(cmd_attrib2, serial_port), serial_port);
                }
                else load_string(I_Auto, "\n\rSyntax error: Use 'E nn vv.vvvv' Append 'q' for quite mode.", serial_port);
            break;
            case 'l':  //Unlock the system and allow variables to be modified.
                if(CMD_buff[serial_port][2]=='Y'){
                    Batt_IO_OFF();
                    charge_mode = Wait;
                    Flags &= 0xFE;
                    CONDbits.Power_Out_EN = off;
                    STINGbits.CH_Voltage_Present = off;
                    save_vars();
                    load_string(I_Auto, "Sets UnLKD.\n\r", serial_port);
                    CMD_buff[serial_port][2]='N';
                }
                else load_string(I_Auto, "Usage: 'l Y' to unlock.", serial_port);
            break;
            case 'L':  //Lock the system and enable system functionality.
                if(Flags&syslock){setsLockedErr(serial_port);break;}
                send_string(I_Auto, "Wait...", serial_port);
                first_cal = 0;  //Initiate calibration routine
                Flags |= syslock; //Lock the settings so that things can run without disruption.
                while(first_cal!=3)Idle();  //Wait until calibration is done.
                save_vars();
                load_string(I_Auto, "Sets LKD.", serial_port);
            break;
            case 'Q':
                if(Flags&syslock){setsLockedErr(serial_port);break;}
                Volt_Cal(serial_port);
            break;
            case 'm':
                if(CONDbits.Power_Out_EN)load_string(I_Auto, "\n\rPower Out On.", serial_port);
                if(CONDbits.charger_detected)load_string(I_Auto, "\n\rCharge Go.", serial_port);
                load_string(I_Auto, "\n\rRL ", serial_port);
                load_float(I_Auto, Run_Level, serial_port);
                load_string(I_Auto, "\n\rCH ", serial_port);
                load_float(I_Auto, charge_mode, serial_port);
                load_string(I_Auto, "\n\r", serial_port);

            break;
            case '+':
                if(serial_port==PORT1)CONDbits.Port1_Echo=on;
                else CONDbits.Port2_Echo=on;
                load_string(I_Auto, "\n\rEcho ON.", serial_port);
            break;
            case '=':
                if(serial_port==PORT1)CONDbits.Port1_Echo=off;
                else CONDbits.Port2_Echo=off;
                load_string(I_Auto, "\n\rEcho OFF.", serial_port);
            break;
            default:
                load_string(I_Auto, "Unknown Command.", serial_port);
            break;
        }
        CMD_Point[serial_port] = clear;
        cmdRDY[serial_port] = no;
        tempPoint[serial_port] = clear;
        for(int i=0;i<Clength;i++)CMD_buff[serial_port][i]=' ';    //Clear the command buffer.
        //Send command receive "@"
        send_string(I_Auto, "\n\r@", serial_port);
        //Check for faults.
        if(vars.fault_count){
            //Send fault alert "!"
            send_string(I_Auto, "!", serial_port);
        }
        if(Run_Level == Crit_Err){
           //Send fault alert "!"
            send_string(I_Auto, " ->CrE!<-", serial_port);
        }
    }
}

void BAL_Out(char LEDS){
    LED_dir_1 = LED_HiZ_1;
    LED_dir_2 = LED_HiZ_2;
    Mult_SEL = 0;
    Mult_B1 = !(!(LEDS&0x01)); //WTF?? Can't do it without !(!())
    Mult_B2 = !(!(LEDS&0x02)); //Cleaner looking than writing an if()
    Mult_B3 = !(!(LEDS&0x04));
    Mult_B4 = !(!(LEDS&0x08));
    LED_dir_1 = DFLT_1;
    LED_dir_2 = DFLT_2;
    
}

void LED_Out(char LEDS){
    LED_dir_1 = LED_HiZ_1;
    LED_dir_2 = LED_HiZ_2;
    Mult_SEL = 1;
    Mult_B1 = !(LEDS&0x01);
    Mult_B2 = !(LEDS&0x02);
    Mult_B3 = !(LEDS&0x04);
    Mult_B4 = !(LEDS&0x08);
    LED_dir_1 = DFLT_1;
    LED_dir_2 = DFLT_2;
}


void LED_ChrgLVL(float LEVEL){
    if((LEVEL > 90 && !CONDbits.charger_detected) || (LEVEL > 99 && CONDbits.charger_detected))LED_Out(0x0F);
    else if(LEVEL > 74)LED_Out(0x07);
    else if(LEVEL > 49)LED_Out(0x03);
    else if(LEVEL >= 24)LED_Out(0x01);
    else if(LEVEL < 24 && !STINGbits.CH_Voltage_Present){
        if(BlinknLights&0x04)LED_Out(0x03);      //Low battery indication.
        else LED_Out(0x00);
    }
    else LED_Out(0x00);
}

//Gas gauge and ballance circuit output control.
void LED_Mult(char attributes){
    if(attributes >= on){
        //Run multiplexed routine.
        //Debug mode LEDs
        if(attributes == Debug)LED_Out(0x06);
        else if(attributes == Ltest){
            if(CONDbits.LED_test_ch)BAL_Out(LED_Test);
            else LED_Out(LED_Test);
        }
        else if(mult_timer >= LED_Brightness && attributes == on){
            //Display LEDs
            mult_timer = 0;
            //Error blink LED
            if(STINGbits.errLight){
                if(BlinknLights&0x10)LED_Out(0x02); //Slow blink for error light.
                else LED_Out(0x00);
            }
            //Charging level indication.
            else if(CONDbits.charger_detected){
                if(BlinknLights&0x01 && (charge_mode > USB3_Wimp || CONDbits.fastCharge))LED_ChrgLVL(dsky.chrg_percent+25); //Fast charging indication.
                else if(BlinknLights&0x02 && charge_mode < USB3 && !CONDbits.fastCharge)LED_ChrgLVL(dsky.chrg_percent+25);  //Normal charging indication.
                else LED_ChrgLVL(dsky.chrg_percent);
            }
            //Power level indication.
            else LED_ChrgLVL(dsky.chrg_percent);
        }
        else{
            //Balance LEDs
            if(mult_timer<LED_Brightness)mult_timer++;
            BAL_Out(Ballance_LEDS);
        }
    }
    else {
        //Turn all multiplexed outputs off.
        BAL_Out(0x00);
    }
}

#endif
//CONDbits.pwr_detect