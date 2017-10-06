//MSP430G2553 
#include <msp430.h>
#include <msp430G2553.h>


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   //Stop Watch Dog Timer
P1SEL &= 0xBE;

P1DIR |= BIT0;          //LED output
P1DIR |= BIT6;

TA0CCTL0 = CCIE;
TA0CTL = TASSEL_2 + MC_1 + ID_3; //SMCLK/8, UP
TA0CCR0 = 25000;				//5Hz

TA1CCTL0 = CCIE;
TA1CTL = TASSEL_2 + MC_1 + ID_3; //SMCLK/8, UP
TA1CCR0 = 12500; 				//10Hz

_BIS_SR(LPM0_bits + GIE);


}
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TA0_ISR(void)
{
P1OUT ^= BIT6;
}
#pragma vector = TIMER1_A0_VECTOR
__interrupt void TA1_ISR(void)
{
P1OUT ^= BIT0;
}


