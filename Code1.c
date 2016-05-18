#include <msp430.h>

//Code 1
int main(void) {

    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer

    P1DIR |=  BIT5;  // Set P1.1 to P1.5 to output direction

    for(;;) {
	volatile unsigned int i;  // volatile to prevent optimization

	P1OUT ^= BIT5; // Toggle P1.5 using exclusive-OR


	i = 50000;     // SW Delay

	do i--;
	while(i != 0);
    }
    return 0;
}
