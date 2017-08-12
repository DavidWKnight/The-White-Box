/*
 * main.c
 *
 *  Created on: Jun 11, 2017
 *      Author: David Knight
 */


/*
 * Cant use following pins on msp430fr4133 launchpad:
 * P1 bit 0 output
 * P8 bit 0,1,2 outputs
 */

/* Things to change for prototype
 * misc.c remove line port1_check &= 0xFFFE; in port1_debounce
 * edit #define's in lcd.h for the bits and ports used for the lcd
 *
 */

#include <msp430.h>
#define launchpad
#include "menu_effect_select.h"
#include "menu_effect_edit.h"
#include "interrupts.h"

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5;
	__disable_interrupt();

	init_ports();
	init_misc();
	init_LCD();
	__enable_interrupt();
	char menu_select = 1;
	while (1){
		switch (menu_select){
		case 1:
			menu_select = menu_effect_select();
			break;
		case 2:
			menu_select = menu_effect_edit();
			break;

		}
	}
}
