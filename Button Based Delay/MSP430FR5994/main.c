//MSP430FR5994
#include <msp430.h>
#include <msp430FR5994.h>


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
    P1DIR |= BIT1;          //Test LED Output
    P1OUT = BIT1;
    //--------------------- Button 1 --------------------------

    P5DIR &= ~(BIT5);       //Button input
    P5IE |= BIT5;           //P1.3 interrupt enable
    P5IES |= BIT5;          //high low edge
    P5REN |= BIT5;          //enable pull up resistor on button
    P5IFG &= ~(BIT5);          // IFG cleared
    P5OUT |= BIT5;

    //--------------------- Button 2 -----------------------
/*
    P5DIR &= ~(BIT6);       //Button input
    P5IE |= BIT6;           //P1.3 interrupt enable
    P5IES |= BIT6;          //high low edge
    P5REN |= BIT6;          //enable pull up resistor on button
    P5IFG &= ~BIT6;          // IFG cleared
    P5OUT |= BIT6;
    */
    //---------------------------TIMER 0---------------------------------------------
    TA0CCTL0 = CCIE;
    TA0CTL = TASSEL_2 + MC_1 + ID_3;//SMCLK/8, UP
    TA0CCR0 = 125000/freq;               // 100 Hz divided by the frequency

    //---------------------------TIMER 1---------------------------------------------
    TA1CCTL0 = CCIE;
    TA1CTL = TASSEL_2 + MC_0 + ID_3;//SMCLK/8, STOP
    TA1CCR0 = 12500;               // 10 Hz

    _BIS_SR(GIE);


    }
    //---------------------------Interrupts---------------------------------------
    #pragma vector = TIMER1_A0_VECTOR           //Timer counts
    __interrupt void TA1_ISR(void)
    {
    count ++;
    P1OUT ^= BIT1;     //Test LED
    }
    #pragma vector = TIMER0_A0_VECTOR           //Flip LED
    __interrupt void TA0_ISR(void)
    {
    P1OUT ^= BIT0;
    }

    #pragma vector = PORT5_VECTOR               //Button Delay
    __interrupt void Port_5(void)
    {
    //    P4OUT ^= BIT7;     //Test LED
     if((P5IN & BIT5) == BIT5)                  //button released
     {
        // P4OUT ^= BIT7;     //Test LED
         TA1CTL = MC_0;                         //stop the second clock

         if(count >= 30 )                       //when the button is quickly released
         {
                 TA0CCR0=count*125;
                 freq = count/100;
         }
         else
         {
             freq++;
             TA0CCR0 = 125000/freq;
         }
     }
    else                                        //Button is  Fully Pressed
        {
       //P4OUT ^= BIT7; //Test LED
        TA1R = 0;
        count = 0;
        TA1CTL = TASSEL_2 + MC_1 + ID_3;        //Starts the clock
        }
        P5IES ^= BIT5;
        P5IFG &= ~(BIT5);

     }





