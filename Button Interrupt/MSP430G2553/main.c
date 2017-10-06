//Button Blink
//Button Toggle
//MSP430G2553 On Board
#include <msp430.h>
#include <msp430G2553.h>


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   //Stop Watch Dog Timer


P1DIR |= BIT0;          //LED output
P1DIR &= ~(BIT3);       //Button input
P1OUT |= BIT0;           //Set LED on from the start
P1IE |= BIT3;           //P1.3 interrupt enable
P1IES |= BIT3;          //high low edge
P1REN |= BIT3;          //enable pull up resistor on button
P1IFG &= ~BIT3;          // IFG cleared


__bis_SR_register(LPM4_bits + GIE);

}
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void)
{
P1OUT ^= BIT0;
P1IFG &= ~BIT3;
}



