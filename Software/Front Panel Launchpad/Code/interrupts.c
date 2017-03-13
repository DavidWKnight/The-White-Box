/*
 * interrupts.c
 *
 *  Created on: Dec 28, 2016
 *      Author: bigbird42
 */

#include "interrupts.h"

/*pushbutton interrupt*/
#pragma vector=PORT1_VECTOR
__interrupt void port1_ISR(void){
	_BIC_SR(LPM4_EXIT);
	port1_check = true;
	P1IFG &= 0x00;
}

/*rotary encoder interrupt*/
#pragma vector=PORT2_VECTOR
__interrupt void port2_ISR(void){
	_BIC_SR(LPM4_EXIT);
	port2_check = true;
	P2IFG &= 0x00;
}

/*pushputton/port1 debounce routine interrupt*/
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void){
	_BIC_SR(LPM4_EXIT);
	port1_debounce();
	TA0CTL &= ~TAIFG;
}

/*rotary encoder/port2 debounce routine interrupt*/
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER0_A1_ISR(void){
	_BIC_SR(LPM4_EXIT);
	port2_debounce();
	TA1CTL &= ~TAIFG;
}
