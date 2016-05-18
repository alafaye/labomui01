#include <msp430.h>

//Global for anti-rebond
volatile unsigned wait_flag=0;
//Code 3
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


	i = 50000;          // SW Delay

	// Anti-rebond
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
