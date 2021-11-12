//question 1
#include <msp430.h>
#define RedLED BIT6
#define GreenLED BIT0
#define ToggleLeds (P1OUT ^= RedLED|GreenLED)
#define Button BIT3
void main(void)
{
BCSCTL2 |= DIVS_3;
WDTCTL = WDT_MDLY_32;
IE1 |= WDTIE;
P1DIR = RedLED|GreenLED;
P1OUT = RedLED;
_enable_interrupts();
LPM1;
}
#pragma vector = WDT_VECTOR
__interrupt void WDT(void)
{
P1OUT = ToggleLeds;
}
