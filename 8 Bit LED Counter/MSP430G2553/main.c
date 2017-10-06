// 8 bit counter
//MSP430G2553 On Board
#include <msp430.h>
#include <msp430G2553.h>

long int count = 0;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   //Stop Watch Dog Timer


P1DIR = 0xFF;           //LED output
P2DIR = 0xFF;
P1DIR &= ~(BIT3);       //Button input
P1OUT = 0x00;           //Set LED off from the start
P1IE |= BIT3;           //P1.3 interrupt enable
P1IES |= BIT3;          //high low edge
P1REN |= BIT3;          //enable pull up resistor on button
P1IFG &= ~BIT3;          // IFG cleared


__bis_SR_register(GIE);

}
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void)
{
count++;
if(count % 1 == 0)
{
    P1OUT ^= BIT0;
}
if(count % 2 == 0)
{
    P1OUT ^= BIT1;
}
if(count % 4 == 0)
{
    P1OUT ^= BIT2;
}

if(count % 8 == 0)
{
    P2OUT ^= BIT3;
}
if(count % 16 == 0)
{
    P1OUT ^= BIT4;
}
if(count % 32 == 0)
{
    P1OUT ^= BIT5;
}
if(count % 64 == 0)
{
    P1OUT ^= BIT6;
}
if(count % 128 == 0)
{
    P1OUT ^= BIT7;
}

P1IFG &= ~BIT3;
}




