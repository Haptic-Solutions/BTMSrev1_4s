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

#ifndef IRQS_H
#define	IRQS_H
extern void __attribute__((interrupt, no_auto_psv)) _INT0Interrupt (void);
extern void __attribute__((interrupt, no_auto_psv)) _INT1Interrupt (void);
extern void __attribute__((interrupt, no_auto_psv)) _ADCInterrupt (void);
extern void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt (void);
extern void __attribute__((interrupt, no_auto_psv)) _T1Interrupt (void);
extern void __attribute__((interrupt, no_auto_psv)) _T2Interrupt (void);
extern void __attribute__((interrupt, no_auto_psv)) _T3Interrupt (void);
extern void __attribute__((interrupt, no_auto_psv)) _FLTAInterrupt (void);
extern void __attribute__((interrupt, no_auto_psv)) _OscillatorFail (void);
extern void __attribute__((interrupt, no_auto_psv)) _AddressError (void);
extern void __attribute__((interrupt, no_auto_psv)) _StackError (void);
extern void __attribute__((interrupt, no_auto_psv)) _MathError (void);
extern void __attribute__((interrupt, no_auto_psv)) _ReservedTrap7 (void);
extern void __attribute__((interrupt, no_auto_psv)) _MI2CInterrupt (void);
extern void __attribute__((interrupt, no_auto_psv)) _SI2CInterrupt (void);


#endif	/* IRQS_H */

