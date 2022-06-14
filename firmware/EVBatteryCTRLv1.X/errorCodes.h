/* 
 * File:   errorCodes.h
 * Author: User
 *
 * Created on January 2, 2022, 2:46 PM
 */

#ifndef ERRORCODES_H
#define	ERRORCODES_H

const char code01[] = "Heater too small";
const char code02[] = "No heater detected";
const char code03[] = "Heater too large";
const char code04[] = "Low Batt";
const char code05[] = "Dischrg OC";
const char code06[] = "Chrg OC";
const char code07[] = "Batt OV";
const char code08[] = "Batt OT";
const char code09[] = "MCtl OT";
const char code0A[] = "Self OT";
const char code0B[] = "Sys Shutdown";
const char code0C[] = "PWM Err";
const char code0D[] = "Osc Fail";
const char code0E[] = "Addr Err";
const char code0F[] = "STK Err";
const char code10[] = "MTH Err";
const char code11[] = "Res 7";
const char code12[] = "PLL UL";
const char code13[] = "BrnOut";
const char code14[] = "WDT rst";
const char code15[] = "TRAP rst";
const char code16[] = "Opcode rst";
const char code17[] = "MCLR rst";
const char code18[] = "Illegal Instruct";
const char code19[] = "Sys Reset";
const char code1A[] = "Invalid port";
const char code1B[] = "No chrg crnt";
const char code1C[] = "PChg > 100%";
const char code1D[] = "VH BV";
const char code1E[] = "VL BV";
const char code1F[] = "VH BC";
const char code20[] = "VL BC";
const char code21[] = "VH BT";
const char code22[] = "VL BT";
const char code23[] = "VH MCT";
const char code24[] = "VL MCT";
const char code25[] = "VH SM";
const char code26[] = "VL SM";
const char code27[] = "PORT1 BSY err";
const char code28[] = "PORT2 BSY err";
const char code29[] = "Prgm Chksum Err";
const char code2A[] = "NVmem Chksum Err";
const char code2B[] = "Sets Chksum Err";
const char code2C[] = "NVsets Chksum Mismatch";
const char code2D[] = "PORT1 ERR";
const char code2E[] = "PORT2 ERR";
const char codeDefault[] = "Unknown";

const char * const errArray[] = {code01,code02,code03,code04,code05,code06,code07,code08,code09,code0A,code0B,code0C
                         ,code0D,code0E,code0F,code10,code11,code12,code13,code14,code15,code16,code17,code18
                         ,code19,code1A,code1B,code1C,code1D,code1E,code1F,code20,code21,code22,code23,code24
                         ,code25,code26,code27,code28,code29,code2A,code2B,code2C,code2D,code2E};
#define numOfCodes 0x2D

#endif	/* ERRORCODES_H */

