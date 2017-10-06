//MSP430FR5994
#include <msp430.h>
#include <msp430FR5994.h>


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   //Stop Watch Dog Timer
    PM5CTL0 &= ~LOCKLPM5;       //Stop Default High-Impedance Mode


P1DIR |= BIT0;          //LED output
P1DIR |= BIT1;

TA0CCTL0 = CCIE;
TA0CTL = TBSSEL_2 + MC_1 + ID_3;//SMCLK/8, UP
TA0CCR0= 25000;					//5Hz

TA1CCTL0 = CCIE;
TA1CTL = TBSSEL_2 + MC_1 + ID_3;//SMCLK/8, UP
TA1CCR0 = 12500;				//10Hz

_BIS_SR(GIE);


}
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TB0_ISR(void)
{
P1OUT ^= BIT1;
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void TB1_ISR(void)
{
P1OUT ^= BIT0;
}



