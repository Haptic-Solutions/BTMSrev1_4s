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
#define Clength 16   //Command Buff Length
//Example: 'Q 1 xxxx.xxx' is 12 characters
unsigned int CMD_Point[2] = {0,0};  //Command Pointer
unsigned int bufsize[2] = {0,0};
char CMD_buff[2][Clength];              //Command Buffer
char cmdRDY[2] = {0,0};
char cmdOVFL[2] = {0,0};
char Terr[2] = {0,0};

unsigned int tempPoint[2] = {0,0};
unsigned int flt_index[2] = {0,0};
unsigned int PxPage[2] = {0,0};
unsigned int pageVar[2] = {0,0};
unsigned int varNum[2] = {0,0};
unsigned int dodispatch[2] = {0,0};
char PxVtimer[2] = {0,0};

const char set_R1[] = "ADC V-Input R1";             // 00
const char set_R2[] = "ADC V-Input R2";             // 01
const char set_SC1[] = "ADC V_Comp 1";              // 02
const char set_SC2[] = "ADC V_Comp 2";              // 03
const char set_SC3[] = "ADC V_Comp 3";              // 04
const char set_SC4[] = "ADC V_Comp 4";              // 05
const char set_CHC[] = "ADC CH_Comp";               // 06
const char set_PCH[] = "Partial Charge % 100X";     // 07
const char set_MxCV[] = "Max Cell Volts";           // 08
const char set_RCV[] = "Rated Cell Volts";          // 09
const char set_MnCV[] = "Min Cell Volts";           // 10
const char set_LVCS[] = "Low-V Cell Shutdown";      // 11
const char set_DC[] = "Discharge C";                // 12
const char set_LC[] = "Limp Current";               // 13
const char set_CC[] = "Charge C";                   // 14
const char set_PAHR[] = "Pack AH Rating";           // 15
const char set_OVSD[] = "Over Current Shutdown";    // 16
const char set_AMA[] = "Absolute Max Amps";         // 17
const char set_AOMW[] = "Auto-Off Min Watts";       // 18
const char set_R25C[] = "Batt Therm Res At 25C";    // 19
const char set_RCOEF[] = "B Therm Coefficient";     // 20
const char set_SC[] = "S-Config";                   // 21 If pointer is < 21 then variables are floating point.
const char set_CT8[] = "Cycles to 80% Capacity";    // 22
const char set_CMnT[] = "Charge Min-Temp";          // 23
const char set_CRLT[] = "Charge Reduce Low-Temp";   // 24
const char set_CMxT[] = "Charge Max-Temp";          // 25
const char set_CRHT[] = "Charge Reduce High-Temp";  // 26
const char set_CTT[] = "Charge Target Temp";        // 27
const char set_DMnT[] = "Disch Min-Temp";           // 28
const char set_DRLT[] = "Disch Reduce Low-Temp";    // 29
const char set_DMxT[] = "Disch Max-Temp";           // 30
const char set_DRHT[] = "Disch Reduce High-Temp";   // 31
const char set_DTT[] = "Disch Target Temp";         // 32
const char set_PST[] = "Pack Shutdown Temp";        // 33
const char set_CST[] = "Controller Shutdown Temp";  // 34
const char set_HW[] = "Heater Running Watts";       // 35
const char set_DSTM[] = "Deep Sleep Time Minutes";  // 36 If pointer is < 36 then variables can only be written when settings are unlocked
const char set_POTM[] = "Power Off Time Minutes";   // 37
const char set_SM[] = "Power Switch Mode";          // 38
const char set_AD[] = "Auto-Display";               // 39
const char varset_Default[] = "Unknown Variable";   // 40/3

const char * const setsNames[] = {set_R1, set_R2, set_SC1, set_SC2, set_SC3, set_SC4, 
                                 set_CHC, set_PCH, set_MxCV, set_RCV, set_MnCV, set_LVCS,
                                 set_DC, set_LC, set_CC, set_PAHR, set_OVSD, set_AMA,
                                 set_AOMW, set_R25C, set_RCOEF, set_SC, set_CT8, set_CMnT, set_CRLT, set_CMxT,
                                 set_CRHT, set_CTT, set_DMnT, set_DRLT, set_DMxT, set_DRHT,
                                 set_DTT, set_PST, set_CST, set_HW, set_DSTM, set_POTM,
                                 set_SM, set_AD, varset_Default};

const unsigned int setsArray[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
                                 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 19, 20};

//Negative numbers means lower limits. Zero means no limits.
                          //0  1  2  3  4  5  6  7  8     9     10    11  12 13 14 15 16 17   18 19 20 21 22    23  24  25  26  27 28  29  30  31  32 33  34  35  36 37 38 39 
const float setsLimits[] = {0, 0, 0, 0, 0, 0, 0, 1, 4.28, 4.25, -2.2, -2, 0, 0, 0, 0, 9, 9.5, 0, 0, 0, 4, 9999, -5, -5, 60, 50, 0, -0, -5, 70, 60, 0, 80, 90, 10, 0, 0, 0, 0};

const char Var_Prcnt[] = "Battery % ";                  //00
const char Var_PkVLT[] = "Pack Voltage";                //01
const char Var_PkTrgtVLT[] = "Pack Target Voltage";     //02
const char Var_PkWatts[] = "Peak Watts";                //03
const char Var_PkVltAvrg[] = "Pack Average Voltage";    //04
const char Var_ChrgInputVLT[] = "Charge Voltage";       //05
const char Var_ChrgInputCRNT[] = "Charge Current";      //06
const char Var_S1VLT[] = "S1 Voltage";                  //07
const char Var_S2VLT[] = "S2 Voltage";                  //08
const char Var_S3VLT[] = "S3 Voltage";                  //09
const char Var_S4VLT[] = "S4 Voltage";                  //10
const char Var_BattWatts[] = "Battery Watts";           //11
const char Var_ChrgWatts[] = "Charge Watts";            //12
const char Var_BattCRNT[] = "Battery Current";          //13
const char Var_BattTemp[] = "Battery Temp";             //14
const char Var_CtrlTemp[] = "Controller Temp";          //15
const char Var_BCRNTAvrg[] = "Batt Average CRNT";       //16
const char Var_OpenVLTG[] = "Open Circuit Voltage";     //17
const char Var_MaxBCRNT[] = "Max Battery Current";      //18
const char var_PAC[] = "Predicted Ah Capacity";         //19 If pointer is >= 19 then read from 'vars' struct, these are read-only and all are floating point
const char var_AhR[] = "Ah Remaining";                  //20 except for total charge cycles which is an int.
const char var_CClcs[] = "Total Charge Cycles";         //21

const char * const varsNames[] = {Var_Prcnt, Var_PkVLT, Var_PkTrgtVLT, Var_PkWatts, Var_PkVltAvrg, Var_ChrgInputVLT,
                                Var_ChrgInputCRNT, Var_S1VLT, Var_S2VLT, Var_S3VLT, Var_S4VLT, Var_BattWatts, Var_ChrgWatts,
                                Var_BattCRNT, Var_BattTemp, Var_CtrlTemp, Var_BCRNTAvrg, Var_OpenVLTG, Var_MaxBCRNT,
                                var_PAC, var_AhR, var_CClcs, varset_Default};

const unsigned int varsArray[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 1, 4, 13};


//Auto Evaluation Messages.
const char Eval_Charging[] = "P Off, Charging. Please Wait...\n\r";
const char Eval_Discharging[] = "P On, discharging. Please Wait...\n\r";
const char Eval_Error[] = "Something went wrong with battery evaluation. Aborting. Please check faults.\n\r";
const char Eval_Finished[] = "Battery Evaluation Complete. :D Please wait for recharge...\n\r";

#endif	/* DATAIO_H */

