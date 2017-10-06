//MSP430FR2311
#include <msp430.h>
#include <msp430FR2311.h>

int count = 0;
int freq = 10;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   //Stop Watch Dog Timer
    PM5CTL0 &= ~LOCKLPM5;       //Stop Default High-Impedance Mode

//-----------------------Set I/O-------------------------------------
//P1SEL &= ~BIT0;
//P4SEL &= ~BIT7;
//------------------------Set Direction--------------------------------
P1DIR |= BIT0;          //LED output
P2DIR |= BIT0;          //Test LED Output
P2OUT = BIT0;
//--------------------- Button 1 --------------------------

P1DIR &= ~(BIT1);       //Button input
P1IE |= BIT1;           //P1.3 interrupt enable
P1IES |= BIT1;          //high low edge
P1REN |= BIT1;          //enable pull up resistor on button
P1IFG &= ~(BIT1);          // IFG cleared
P1OUT |= BIT1;
//--------------------- Button 2 -----------------------
/*
P1DIR &= ~(BIT1);       //Button input
P1IE |= BIT1;           //P1.3 interrupt enable
P1IES |= BIT1;          //high low edge
P1REN |= BIT1;          //enable pull up resistor on button
P1IFG &= ~BIT1;          // IFG cleared
*/
//---------------------------TIMER 0---------------------------------------------
TB0CCTL0 = CCIE;
TB0CTL = TBSSEL_2 + MC_1 + ID_3;//SMCLK/8, UP
TB0CCR0 = 125000/freq;               // 100 Hz divided by the frequency

//---------------------------TIMER 1---------------------------------------------
TB1CCTL0 = CCIE;
TB1CTL = TBSSEL_2 + MC_0 + ID_3;//SMCLK/8, STOP
TB1CCR0 = 12500;               // 10 Hz

_BIS_SR(GIE);


}
//---------------------------Interrupts---------------------------------------
#pragma vector = TIMER1_B0_VECTOR           //Timer counts
__interrupt void TB1_ISR(void)
{
count ++;
P2OUT ^= BIT0;     //Test LED
}
#pragma vector = TIMER0_B0_VECTOR           //Flip LED
__interrupt void TB0_ISR(void)
{
P1OUT ^= BIT0;
}

#pragma vector = PORT1_VECTOR               //Button Delay
__interrupt void Port_1(void)
{

 if((P1IN & BIT1) == BIT1)                  //button released
 {

     TB1CTL = MC_0;                         //stop the second clock

     if(count >= 30 )                       //when the button is quickly released
     {
             TB0CCR0=count*125;
             freq = count/100;
     }
     else
     {
         freq++;
         TB0CCR0 = 125000/freq;
     }
 }
else                                        //Button is  Fully Pressed
{
    TB1R = 0;
    count = 0;
    TB1CTL = TBSSEL_2 + MC_1 + ID_3;        //Starts the clock
    }
    P1IES ^= BIT1;
    P1IFG &= ~(BIT1);

 }

/*
#pragma vector = PORT1_VECTOR               //Reset
__interrupt void Port_1(void)
{
    TA0CCR0 = 12500; //10Hz
P1IFG &= ~(BIT1);
}
*/


