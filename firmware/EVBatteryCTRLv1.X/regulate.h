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

#ifndef REGULATE_H
#define	REGULATE_H

extern void temperatureCalc(void);
extern void outputReg(void);
extern void chargeReg(void);
extern void heat_control(float);

#define crnt_proportion 70000
#define vltg_proportion 70000
#define temp_proportion 70000

float dischrg_current = 0;
float chrg_current = 0;
float dischrg_read = 0;
float analog_smpl_time = 0;
float crnt_error = 0;
float crnt_integral = 0;
float current_output = 0;
float voltage_output = 0;
float temp_dischrg_rate;      //calculated discharge rate based off temp and capacity remaining. Is in %
float temp_chrg_rate;         //calculated discharge rate based off temp and capacity remaining. Is in %
float max_chrg_current;       //calculated charge rate based off temp and capacity remaining. Is in %
float percentOut;
float chrg_remaining;
int  chrg_check = 0;
int soft_OVC_Countdown = SOC_Cycles;

#endif	/* SUBS_H */

