//***************************************************************************************
//  Labo01 Micro Informatique
//
//
//
//***************************************************************************************

#include <msp430.h>


//Code 1
volatile unsigned wait_flag=0;
/*
int main(void) {
  WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer

  P1DIR |= (BIT1 + BIT2 + BIT3 + BIT5);  // Set P1.1 to P1.5 to output direction
  P1DIR &= ~BIT7;          // Set P1.7 as input
  P2DIR &= ~BIT2;          // Set P2.2 as input

  P1REN |=BIT7; // Enable P1.7 internal resistance
  P2REN |= BIT2; // Enable P2.2 internal resistance

  P1OUT |= BIT7; // Set P1.7 as pull-Up resistance
  P2OUT |= BIT2; // Set P2.2 as pull-Up resistance

  P1IES |= BIT7; // P1.7 Hi/Lo edge
  P2IES |= BIT2; // P2.2 Hi/Lo edge

  P1IFG &= ~BIT7; // P1.7 IFG cleared
  P2IFG &= ~BIT2; // P2.2 IFG cleared

  P1IE |= BIT7;  // Enable interrupt for S1  P1.7
  P2IE |= BIT2;  // Enable interrupt for S2  P2.2

   __bis_SR_register(GIE); // Enable general interrupt


  for(;;) {
    volatile unsigned int i;  // volatile to prevent optimization

    P1OUT ^= BIT5; // Toggle P1.5 using exclusive-OR

    // Anti-rebond


    i = 50000;          // SW Delay

    while(i != 0) {
      i--;
      if(wait_flag != 0){
            wait_flag--;
          }
    }
  }
  return 0;
}

//Interrupt for P1.7 -> Switch P1.4 state
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
    if (wait_flag == 0)
    P1OUT ^= BIT3;
  wait_flag = 5000;
  P1IFG &= ~BIT7;
}

//Interrupt for P2.2 -> Switch P1.4 state
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void){
      if (wait_flag == 0)
    P1OUT ^= BIT3;
  wait_flag = 5000;
  P2IFG &= ~BIT2;
}
*/


//Code 2
volatile unsigned int up=0;
int main(void) {
  WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer
  P1DIR |= (BIT1 + BIT2 + BIT3 + BIT5);  // Set P1.1 to P1.3 to output direction
  P1DIR &= ~BIT7;          // Set P1.7 as input
  P1DIR &= ~BIT7;

  P1REN |= BIT7;  // Enable P1.7 internal resistance
  P1OUT |= BIT7;  // Set P1.7 as pull-Up resistance
  P1IES |= BIT7;  // P1.7 Hi/Lo edge
  P1IFG &= ~BIT7; // P1.7 IFG cleared
  P1IE |= BIT7;   // Enable interrupt for S1  P1.7

   __bis_SR_register(GIE);

  for(;;) {
    volatile unsigned int i;  // volatile to prevent optimization

    P1OUT ^= BIT5; // Toggle P1.5 using exclusive-OR

    // Anti-rebond

    i = 50000;          // SW Delay

    while(i != 0) {
      i--;
      if(wait_flag != 0){
            wait_flag--;
          }
      }
  if(P1IN & BIT7){
    P1OUT &= ~(BIT1 + BIT2 + BIT3);
  }
  }
  return 0;
}


//Interrupt for P1.7 -> Switch P1.4 state
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
  if(P1IN & ~BIT7){
    if (wait_flag == 0)
      P1OUT |= (BIT1 | BIT2 | BIT3);
    wait_flag = 5000;
  }
  P1IFG &= ~BIT7;
}



/*
//Code 3
int main(void) {
  WDTCTL = WDTPW | WDTHOLD;             // Stop watchdog timer
  P1DIR |= (BIT1 + BIT2 + BIT3 + BIT5); // Set P1.1 to P1.5 to output direction
  P1DIR &= ~BIT7;                       // Set P1.7 as input

  P1REN |= BIT7;  // Enable P1.7 internal resistance
  P1OUT |= BIT7;  // Set P1.7 as pull-Up resistance
  P1IES |= BIT7;  // P1.7 Hi/Lo edge
  P1IFG &= ~BIT7; // P1.7 IFG cleared

  P1IE |= BIT7;   // Enable interrupt for S1  P1.7

   __bis_SR_register(GIE);

  for(;;) {
    volatile unsigned int i;  // volatile to prevent optimization

    P1OUT ^= BIT5; // Toggle P1.5 using exclusive-OR

    // Anti-rebond


    i = 50000;          // SW Delay

    while(i != 0) {
      i--;
      if(wait_flag != 0){
            wait_flag--;
          }
    }
  }
  return 0;
}

//Interrupt for P1.7 -> Switch P1.4 state
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
  if (wait_flag == 0)
    P1OUT ^= (BIT1 + BIT2 + BIT3);
  wait_flag = 5000;
  P1IFG &= ~BIT7;
}

*/
