
#ifndef _CONFIG_H_
#define _CONFIG_H_
/* Configuration Bit settings
 * SYSCLK = 80 MHz (8MHz Crystal / FPLLIDIV * FPLLMUL / FPLLODIV)
 * PBCLK = 80 MHz (SYSCLK / FPBDIV)
 * Primary Osc w/PLL (XT+,HS+,EC+PLL)
 * WDT OFF
 * Other options are don't care
 * */
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1




#endif
