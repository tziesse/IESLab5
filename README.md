# IESLab5

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

//question 2
#include "msp430G2553.h"

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;  // Stop WDT
     P1DIR |= BIT6;             // P1.6 set for output
     P1OUT = 0x00;
     P1SEL |= BIT6;             // select TA0.1 output signal
     TACCR0 = 62500-1;             // PWM Time Period/ frequency
     TACCTL1 = OUTMOD_7;          // reset/set mode 7 for output signal
     TACCR1 = 6250-1;                // PWM Duty cycle is 10%
     TACTL = TASSEL_2 + ID_3 + MC_1;   // SMCLK and Up Mode, 

     while(1){
         P1OUT ^= BIT6; //display on led and on pin 1.6
     }
}

//question 3
#include "msp430G2553.h"
void main(void)
{
 WDTCTL = WDTPW + WDTHOLD;  // Stop WDT
 P1DIR |= BIT6;             // P1.6 to output
 TA0CTL = TASSEL_2 + MC_1 + ID_3 + TACLR;//+TACLR;
 TA0CCR0 = 31250; // Set maximum count value (PWM Period)
 TA0CCR1 = 6200; // initialize counter compare value
 TA0CCTL0 |= CCIE;
 TA0CCTL1 |= CCIE;
 TA0CCTL0 &=~CCIFG;
 TA0CCTL1 &=~CCIFG;
 _enable_interrupts(); // Enter LPM0
}
#pragma vector = TIMER0_A0_VECTOR       //define the interrupt service vector
__interrupt void TA0_ISR (void)    // interrupt service routine
    {
    P1OUT |=BIT6;
    TA0CCTL0 &=~CCIFG;
    }
#pragma vector = TIMER0_A1_VECTOR       //define the interrupt service vector
__interrupt void TA1_ISR (void)    // interrupt service routine
    {
    P1OUT &=~BIT6;
    TA0CCTL1 &=~CCIFG;
    }
