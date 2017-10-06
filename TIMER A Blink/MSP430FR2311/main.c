//MSP430FR2311
#include <msp430.h>
#include <msp430FR2311.h>


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   //Stop Watch Dog Timer
    PM5CTL0 &= ~LOCKLPM5;       //Stop Default High-Impedance Mode


P1DIR |= BIT0;          //LED output
P2DIR |= BIT0;

TB0CCTL0 = CCIE;
TB0CTL = TBSSEL_2 + MC_1 + ID_3;//SMCLK/8, UP
TB0CCR0= 25000;					//5Hz

TB1CCTL0 = CCIE;
TB1CTL = TBSSEL_2 + MC_1 + ID_3;//SMCLK/8, UP
TB1CCR0 = 12500;				//10Hz

_BIS_SR(GIE);


}
#pragma vector = TIMER0_B0_VECTOR
__interrupt void TB0_ISR(void)
{
P2OUT ^= BIT0;
}

#pragma vector = TIMER1_B0_VECTOR
__interrupt void TB1_ISR(void)
{
P1OUT ^= BIT0;
}



