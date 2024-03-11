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

#ifndef ERRORCODES_H
#define	ERRORCODES_H

const char code01[] = "Heater too small";
const char code02[] = "No heater detected";
const char code03[] = "Heater too large";
const char code04[] = "Low Batt V";
const char code05[] = "Batt OC";
const char code06[] = "Chrg OC";
const char code07[] = "Batt OV";
const char code08[] = "Batt OT";
const char code09[] = "B-Flag(s) Set";
const char code0A[] = "Self OT";
const char code0B[] = "Sys Shutdown";
const char code0C[] = "PWM excep";
const char code0D[] = "Osc excep";
const char code0E[] = "Addr excep";
const char code0F[] = "STK excep";
const char code10[] = "MTH excep";
const char code11[] = "Res7 excep";
const char code12[] = "blank";
const char code13[] = "BrnOut";
const char code14[] = "WDT rst";
const char code15[] = "un-handled exception rst";
const char code16[] = "Opcode rst";
const char code17[] = "MCLR rst";
const char code18[] = "Illegal Inst";
const char code19[] = "Sys Rst";
const char code1A[] = "Inval prt";
const char code1B[] = "USB Ch Flt";
const char code1C[] = "PChg > 100%";
const char code1D[] = "VH ChV";
const char code1E[] = "VL ChV";
const char code1F[] = "VH ChC";
const char code20[] = "VL ChC";
const char code21[] = "VH BTmp";
const char code22[] = "VL BTmp";
const char code23[] = "VH BC";
const char code24[] = "VL BC";
const char code25[] = "VH SM";
const char code26[] = "VL SM";
const char code27[] = "PORT1 BSY err";
const char code28[] = "PORT2 BSY err";
const char code29[] = "Pgm Chk Err";
const char code2A[] = "NVM Chk Err";
const char code2B[] = "Sets Chk Err";
const char code2C[] = "NVS Chk Err";
const char code2D[] = "PORT1 ERR";
const char code2E[] = "PORT2 ERR";
const char code2F[] = "Soft OC";
const char code30[] = "VH S1";
const char code31[] = "VL S1";
const char code32[] = "VH S2";
const char code33[] = "VL S2";
const char code34[] = "VH S3";
const char code35[] = "VL S3";
const char code36[] = "VH S4";
const char code37[] = "VL S4";
const char code38[] = "Chrg in OV";
const char code39[] = "EXT OC: Please Reset";
const char code3A[] = "EXT OV: Batt Fuse Tripped";
const char code3B[] = "Batt UV";
const char code3C[] = "CH cyc-limit";
const char code3D[] = "Sys Safe Mode";
const char codeDefault[] = "Unknown";

const char * const errArray[] = {code01,code02,code03,code04,code05,code06,code07,code08,code09,code0A,code0B,code0C
                         ,code0D,code0E,code0F,code10,code11,code12,code13,code14,code15,code16,code17,code18
                         ,code19,code1A,code1B,code1C,code1D,code1E,code1F,code20,code21,code22,code23,code24
                         ,code25,code26,code27,code28,code29,code2A,code2B,code2C,code2D,code2E,code2F,code30
                         ,code31,code32,code33,code34,code35,code36,code37,code38,code39,code3A,code3B,code3C
                         ,code3D,codeDefault};

#endif	/* ERRORCODES_H */

