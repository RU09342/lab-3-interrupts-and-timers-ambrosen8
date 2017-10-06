//MSP430F5529
#include <msp430.h> 
#include <msp430f5529.h>
int main(void)
	{
    WDTCTL = WDTPW | WDTHOLD;// Stop watchdog timer
    P1DIR |= BIT0; //LED output
    P1DIR &= ~(BIT1); //Button input
    P1REN |= BIT1; //enable pull-up resistor
    P1OUT |= BIT0; //Set LED on from the start
    P1IE |= BIT1; //enable interrupt
    P1IES |= BIT1; //falling edge
    P1IFG &= ~(BIT1);//clear interrupt flag

    _BIS_SR(LPM4_bits + GIE); // Set low power mode
   }

    #pragma vector=PORT1_VECTOR
    __interrupt void PORT_1(void)
    {
    P1OUT ^= BIT0;
    P1IFG &= ~(BIT1);
    }
