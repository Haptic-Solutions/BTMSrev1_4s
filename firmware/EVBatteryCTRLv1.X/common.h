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

#ifndef COMMON_H
#define	COMMON_H
#include "defines.h"

extern inline void current_cal(void);
extern inline void open_volt_percent(void);
extern inline void reset_check(void);
extern inline void Deep_Sleep(void);
extern inline float absFloat(float);
extern inline void IsSysReady(void);
extern inline void calcAnalog(void);
extern inline void Volt_Cal(int);
extern void CapacityCalc(void);
extern void OSC_Switch(int);
extern int PORTS_DONE(void);
extern void timer_reset(void);

/* NOTE: Try to keep memory usage below about 75% for the dsPIC30F3011 as the stack can use as much as 15% */
/*****************************/
/* Init vars and stuff. */
/* Temperatures are in C */
/* int's are 16 bit */
typedef int int16_t;    //Make sure our int's are actually only 16 bit rather than assuming.
typedef unsigned int uint16_t;    //Make sure our int's are actually only 16 bit rather than assuming.
/* boot check */
int reset_chk __attribute__((persistent));//Do not initialize this var. Needs to stay the same on a reset.
/*****************************/
#pragma pack(1)
struct Settings{
    //Analog input constants
    int     settingsArray[1];           //This space used for unique ID to determine if settings has been written to at least once.
    float   settingsFloat[1];           //Wasted space but oh well. It's hacky, but seems to work reliably enough for now.
    /*****************************/
    float   R1_resistance;              //R1 resistance in Kohms
    float   R2_resistance;              //R2 resistance in Kohms
    float   S_vlt_adjst[4];             //Cell ratio input compensation.
    float   Ch_vlt_adjst;               //Charge input ratio input compensation.
    /*****************************/
    //Battery Ratings and setpoints
    float   partial_charge;             //Percentage of voltage to charge the battery up to. Set to 0 to disable.
    float   max_battery_voltage;        //Max battery cell voltage before shutdown and flag set.
    float   battery_rated_voltage;      //Target max charge voltage
    float   dischrg_voltage;            //Minimum battery voltage
    float   low_voltage_shutdown;       //Battery Low Total Shutdown Voltage
    float   dischrg_C_rating;           //Discharge C rating
    float   limp_current;               //Limp mode current in amps
    float   chrg_C_rating;              //Charge C rating.
    float   amp_hour_rating;            //Battery amp hour rating.
    float   over_current_shutdown;      //Shutdown current. Sometimes the regulator isn't fast enough and this happens.
    float   absolute_max_current;       //Max regulating current.
    /******************************/
    float   auto_off_watts;
    int     Cell_Count;    //Number of cells.
    int   settingsINT[1];
    int   cycles_to_80;               //Number of charge cycles to 80% capacity.
    //Charge temps.
    int   chrg_min_temp;              //Battery minimum charge temperature. Stop Charging at this temp.
    int   chrg_reduce_low_temp;       //Reduce charge current when lower than this temp.
    int   chrg_max_temp;              //Battery max charge temp. Stop charging at this temp.
    int   chrg_reduce_high_temp;      //Reduce charge current when higher than this temp.
    int   chrg_target_temp;           //Battery heater charge target temp. Keeps us nice and warm in the winter time.
    //Discharge temps.
    int   dischrg_min_temp;           //Battery minimum discharge temperature.
    int   dischrg_reduce_low_temp;    //Reduced current discharge low temperature.
    int   dischrg_max_temp;           //Battery max discharge temperature.
    int   dischrg_reduce_high_temp;   //Battery reduced discharge high temperature.
    int   dischrg_target_temp;        //Battery heater discharge target temp. Keeps us nice and warm in the winter time.
    //Shutdown temps.
    int   battery_shutdown_temp;      //Max battery temp before shutting down everything.
    int   ctrlr_shutdown_temp;        //Max motor or motor controller temp shutdown.
    //Some other stuff.
    int   max_heat;           //Heater watts that you want to use.
    int     DeepSleepAfter;      //Power off the system after this many minutes of not being plugged in or keyed on. 120 minutes is 2 hours. -1 disables timer.
    int     PowerOffAfter;
    unsigned int     flash_chksum_old;   //System Flash Checksum as stored in NV-mem
    char    PWR_SW_MODE;
    char    PxVenable[2];
    char    custom_data1[6];    //4 blocks of 6 chars of custom user text or data, can be terminated by a NULL char. (0xFC - 0xFF)
    char    custom_data2[6];
    char    custom_data3[6];
    char    custom_data4[6];
    char    page[2][4][6];      //Display page holder. (port)(Page#)(Variable to Display: A '0' at the start = Skip Page)
    char    pageDelay[2][4];    //Page delay. (Page#Delay in 1/8 seconds) 0 = full speed.
}sets;

struct Variables{
    int     variablesArray[1];          //This space used for unique ID to determine if vars has been written to at least once.
    float   variablesFloat[1];          //More wasted space.
// Calculated Battery Ratings
    float   battery_capacity;           //Calculated total battery capacity in ah
    float   absolute_battery_usage;     //Max total power used from battery since last power cycle.
    float   voltage_percentage_old[4];     //Voltage percentage from the last time we where on.
    float   battery_usage;              //Calculated Ah usage in/out of battery
    float   battery_remaining;          //Calculated remaining capacity in battery.
    float   chargeCycleLevel;           //% of a charge cycle completed. Rolls over to 0 once it reaches capacity of battery (for 100%) and increments 'TotalChargeCycles' by 1.
    unsigned int     TotalChargeCycles;  //Total number of charge cycles this battery has been through.
    // Fault Codes.
    unsigned int     fault_codes[2][maxFCodes] __attribute__((persistent));
    unsigned int     fault_count __attribute__((persistent));
    // Other stuff.
    unsigned int     partial_chrg_cnt;           //How many times have we plugged in the charger since the last full charge?
    char     heat_cal_stage;             //0 - 4, stage 0 = not run, set 1 to start, stage 2 = in progress, stage 3 = completed, 4 is Error. 5 is disable heater.
    char     testBYTE;
}vars;

const char VSPC[] = " ";
const char V01[] = "%";
const char V02[] = "V";
const char V03[] = "TV";
const char V04[] = "PW";
const char V05[] = "AV";
const char V06[] = "CV";
const char V07[] = "CA";
const char V08[] = ":S1";
const char V09[] = ":S2";
const char V0A[] = ":S3";
const char V0B[] = ":S4";
const char V0C[] = "W";
const char V0D[] = "CW";
const char V0E[] = "A";
const char V0F[] = "CB";
const char V10[] = "CM";
const char V11[] = "AA";
const char V12[] = "OCV";
const char V13[] = "MC";
const char V14[] = "\n\r";  //Newline + Return

const char * const Vlookup[] = {VSPC,V01,V02,V03,V04,
                                     V05,V06,V07,V08,
                                     V09,V0A,V0B,V0C,V0D,
                                     V0E,V0F,V10,V11,
                                     V12,V13,V14};

//Variables that can be sent out the serial port.
struct dskyvars{
    int     dskyarray[1];           //For sending raw data
    float   dskyarrayFloat[1];      //For sending float data to display
    float   chrg_percent;           //01: 6char 00.0% Percentage of battery charge
    float   pack_voltage;           //02: 6char 00.0V Battery pack voltage
    float   chrg_voltage;           //03: 7char 00.0TV Charge Target Voltage per cell.
    float   peak_power;             //04: 7char 00.0PW Peak output power
    float   pack_vltg_average;      //05: 7char 00.0AV Battery average voltage
    float   Cin_voltage;            //06: 7char 00.0CV Charger input voltage
    float   Cin_current;            //07: 7char 00.0CA Charger input current
    float   Cell_Voltage[4];     //08-0B: 8char 00.0S1 Cell voltage S1-S4
    float   watts;                  //0C: 7char -0000W watts in or out of battery.
    float   Cwatts;                 //0D: 8char -0000CW watts in from charger.
    float   battery_current;        //0E: 7char -00.0A Battery charge/discharge current
    float   battery_temp;           //0F: 8char -00.0CB Battery Temperature
    float   my_temp;                //10: 8char -00.0CM Controller board Temperature
    float   battery_crnt_average;   //11: 8char -00.0AA Battery charge/discharge average current
    float   open_voltage;           //12: 9char -00.0OCV Battery Open Circuit Voltage
    float   max_current;            //13: 8char -00.0MC Max allowable battery current.
}dsky;
#define varLimit 0x0015
#define signStart 0x000C
#define wattsNum 0x000C
#define nlNum 0x0014

// Calculated battery values. These don't need to be saved on shutdown.
volatile float   chrge_rate = 0;             //calculated charge rate based off temperature
volatile float   resistor_divide_const = 0;              //Value for calculating the ratio of the input voltage divider.

/*****************************/
/* General Vars */
volatile float voltage_percentage[4];     //Battery Open Circuit Voltage Percentage.
volatile float temp_Cell_Voltage_Average[4];
volatile float Cell_Voltage_Average[4];
volatile float pack_target_voltage = 0;
volatile float Bcurrent_compensate = 0;     //Battery Current compensation.
volatile float Ccurrent_compensate = 0;      //Charger Current compensation.
volatile float CavgVolt = 0;     //averaged voltage from charger
volatile float BavgVolt[4];     //averaged voltage from battery
volatile float BavgCurnt = 0;    //averaged current input for battery
volatile float CavgCurnt = 0;    //averaged current input from charger
volatile float CavgCurnt_temp = 0;
volatile float avgBTemp = 0;    //averaged battery temperature
volatile float avgSTemp = 0;    //averaged self temperature
volatile float bt_crnt_avg_temp = 0;
volatile float bt_vltg_avg_temp = 0;
volatile float Max_Charger_Current = 0;
volatile float Charger_Target_Voltage = 0;
volatile float Half_ref = 0;
volatile float analog_const = 0;
volatile int   OV_Timer[4];
volatile int  gas_gauge_timer = gauge_timer;
volatile unsigned int PWM_MaxBoost = 0;
volatile char soft_OVC_Timer = 0;
volatile char precharge_timer = 0;
volatile char charge_mode = Wait;
volatile char avg_cnt = 0;
volatile char avg_rdy = 0;
volatile char analog_avg_cnt = 0;
volatile char Bcurnt_cal_stage = 0;
volatile char Ccurnt_cal_stage = 0;
volatile char LED_Test = 1;
/* 0 - 4, stage 0 = not run, set 1 to start, stage 2 = in progress, stage 3 = completed, 4 is Error.
 */
volatile char power_session = 1;
volatile char DeepSleepTimer = 0;
volatile char DeepSleepTimerSec = 59;      //default state.
volatile char PowerOffTimer = 0;
volatile char PowerOffTimerSec = 59;      //default state.
volatile char cfg_space = 0;
volatile char vr_space = 0;
volatile char dsky_space = 0;
volatile char v_test = 0;
volatile char first_cal = 0;
volatile char Run_Level = 0;
volatile char ch_cycle = 0;
volatile char slowINHIBIT_Timer = 0;
volatile char button_timer = 0;
/*****************************/
//Control Output
volatile unsigned int     charge_power = 0; //charge rate
volatile unsigned int     ch_boost_power = 0; //charge rate
volatile unsigned int     heat_power = 0;   //heater power
/*****************************/

/* Boolean Variables */
//Conditions.
#define COND COND
volatile unsigned int COND = 0;
typedef struct tagCONDBITS {
  unsigned Power_Out_EN:1;
  unsigned output_ON:1;
  unsigned Power_Out_Lock:1;
  unsigned charger_detected:1; //Used for when the charger is plugged in.
  unsigned diagmode:1;
  unsigned got_open_voltage:1;
  unsigned failSave:1;
  unsigned fastCharge:1;
  unsigned V_Cal:1;
  unsigned LED_test_ch:1;
  unsigned IRQ_RESTART:1;
  unsigned clockSpeed:1;
  unsigned slowINHIBIT:1;
  unsigned IC_RW:1;
  unsigned IC_ACK:1;
  //unsigned MemInUse:1;
} CONDBITS;
volatile CONDBITS CONDbits;

#define STING STING
volatile unsigned int STING = 0;
typedef struct tagSTINGBITS {
  unsigned lw_pwr_init_done:1;
  unsigned deep_sleep:1;
  unsigned zero_current:1;
  unsigned adc_sample_burn:1; //Burn it. Don't touch this var it will burn you.
  unsigned adc_valid_data:1;
  unsigned init_done:1;
  unsigned fault_shutdown:1; //General shutdown event.
  unsigned osc_fail_event:1;
  unsigned p_charge:1;
  unsigned sw_off:1;
  unsigned errLight:1;
  unsigned CH_Voltage_Present:1;
  unsigned OverCRNT_Fault:1;
  unsigned Force_Max_Cnt_Limit:1;
} STINGBITS;
volatile STINGBITS STINGbits;


#define Tfaults Tfaults
volatile unsigned int Tfaults __attribute__((persistent));
typedef struct tagTfaultsBITS {
  unsigned OSC:1;
  unsigned STACK:1;
  unsigned ADDRESS:1;
  unsigned MATH:1;
  unsigned FLTA:1;
  unsigned RESRVD:1;
  unsigned CHK_BSY:1;
} TFAULTSBITS;
volatile TFAULTSBITS Tfaultsbits;


volatile unsigned int Flags = 0;
#define syslock 0x01
#define OverVLT_Fault 0x02
#define HighVLT 0x04
#define LowVLT 0x08
#define BattOverheated 0x10
#define SysOverheated 0x20


//LED stuff used for gas gauge and cell ballance control.
volatile unsigned char BlinknLights = 0;
volatile char mult_timer = 0;
volatile char Ballance_LEDS = 0;

#endif	/* SUBS_H */

