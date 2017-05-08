/*
 * interrupts.c
 *
 *  Created on: Dec 28, 2016
 *      Author: bigbird42
 */

#include "interrupts.h"
#include <msp430.h>
#include "misc.h"

/*pushbutton interrupt*/
#pragma vector=PORT1_VECTOR
__interrupt void port1_ISR(void){
	_BIC_SR(LPM4_EXIT);
	debounce = true;
	port1_interrupt = true;
	P1IFG &= 0x00;
}

/*rotary encoder interrupt*/
#pragma vector=PORT2_VECTOR
__interrupt void port2_ISR(void){
	_BIC_SR(LPM4_EXIT);
	debounce = true;
	port2_interrupt = true;
	P2IFG &= 0x00;
}

/*debounce routine interrupt*/
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void){
    _BIC_SR(LPM4_EXIT);
    if(port1_interrupt){
        port1_debounce();
    }
    else if(port2_interrupt){
        port2_debounce();
    }
    TA0CTL &= ~TAIFG;
}

/*LCD cursor flash interrupt*/
#pragma vector=RTC_VECTOR
__interrupt void RTC_ISR(void){
	_BIC_SR(LPM4_EXIT);
	RTC_interrupt = true;
	RTCIV;
}
