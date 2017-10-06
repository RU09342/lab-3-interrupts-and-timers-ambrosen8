//Button Blink
//Button Toggle
//MSP430FR5994 On Board
#include <msp430.h>
#include <msp430FR5994.h>


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   //Stop Watch Dog Timer
    PM5CTL0 &= ~LOCKLPM5;       //Stop Default High-Impedance Mode

P1DIR |= BIT0;          //LED output
P5DIR &= ~(BIT6);       //Button input
P1OUT |= BIT0;           //Set LED on from the start
P5IE |= BIT6;           //P1.3 interrupt enable
P5IES |= BIT6;          //high low edge
P5REN |= BIT6;          //enable pull up resistor on button
P5IFG &= ~(BIT6);          // IFG cleared


__bis_SR_register(LPM4_bits + GIE);

}
#pragma vector = PORT5_VECTOR
__interrupt void Port_5(void)
{
P1OUT ^= BIT0;
P5IFG &= ~(BIT6);
}


