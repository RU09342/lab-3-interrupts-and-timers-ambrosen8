//Button Blink
//Button Toggle
//MSP430FR2311 On Board
#include <msp430.h>
#include <msp430FR2311.h>


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   //Stop Watch Dog Timer

P1DIR |= BIT0;          //LED output
P1DIR &= ~(BIT1);       //Button input
P1OUT |= BIT0;           //Set LED on from the start
P1IE |= BIT1;           //P1.3 interrupt enable
P1IES |= BIT1;          //high low edge
P1REN |= BIT1;          //enable pull up resistor on button
P1IFG &= ~BIT1;          // IFG cleared


__bis_SR_register(LPM4_bits + GIE);

}
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void)
{
P1OUT ^= BIT0;
P1IFG &= ~BIT1;
}


