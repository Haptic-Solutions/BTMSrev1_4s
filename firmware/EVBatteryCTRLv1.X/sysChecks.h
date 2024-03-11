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

#ifndef SYSCHKS_H
#define	SYSCHKS_H

#define fCalReady 3
#define fCalTimer fCalReady - 1

extern inline void explody_preventy_check(void);
extern inline void currentCheck(void);
extern inline void heater_calibration(void);
extern void fault_log(int);
extern inline void ALL_shutdown(void);
extern inline void Batt_IO_OFF(void);
extern inline void reset_check(void);
extern inline void main_power_check(void);
extern inline void first_check(void);
extern inline void analog_sanity(void);
extern inline void death_loop(void);
extern inline void initialCal(void);
extern inline void chargeDetect(void);
extern inline int D_Flag_Check();
extern void Exception_Check(void);

/*****************************/
/* Init vars and stuff. */
/* Temperatures are in C */
/******************************/
int heat_set = 0;               //Calculated heater output for wattage chosen by user.
int oc_shutdown_timer = 0;
int shutdown_timer = 0;
char CHwaitTimer = 0;

#endif	/* SUBS_H */

