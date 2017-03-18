/*
 * Cant use following pins on msp430fr4133 launchpad:
 * P1 bit 0 output
 * P8 bit 0,1,2 outputs
 */

/* Things to change for prototype
 * misc.c remove line port_state &= 0xFFFE; in port1_debounce and port2_debounce
 * edit #define's in lcd.h for the bits and ports used for the lcd
 *
 */


#include <msp430.h> 
#include <stdbool.h>
#include <string.h>

char menu_effect_select();
char menu_effect_edit();
char menu_settings();

unsigned int effects[4] = {0,0,0,0};

#include "misc.h"
#include "menu.h"
#include "lcd.h"
#include "interrupts.h"

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5;
	__disable_interrupt();

	init_ports();
	init_misc();
	init_LCD();

	P1IFG = 0x00;
	P2IFG = 0x00;
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
		case 3:
			menu_select = menu_settings();
			break;
		}

	}
}

char menu_effect_select(){
	unsigned int user_input = 0;

	/*setup menu*/
	menu_effect_select_setup();

	/*in menu actions*/
	while(1){
		wait_for_input();
		user_input = user_input_decode();//send input to state machines
		//do actions for this menu relative to user input
		switch(user_input){
			/*port 1*/
			case 0x0001:
				break;
			case 0x0002:
				if (effects[1] < 100){
					effects[1]++;
					lcd_write_effects(1);
				}
				break;
			case 0x0004:
				break;
			case 0x0008:
				if (effects[1] > 0){
					effects[1]--;
					lcd_write_effects(1);
				}
				break;
			case 0x0010:
				break;
			case 0x0020:
				break;
			case 0x0040:
				break;
			case 0x0080:
				break;
			/*port 2*/
			case 0x0100:
				if (effects[0] > 0){
					effects[0]--;
					lcd_write_effects(0);
				}
				break;
			case 0x0200:
				if (effects[0] < 100){
					effects[0]++;
					lcd_write_effects(0);
				}
				break;
			case 0x0400:
				if (effects[1] > 0){
					effects[1]--;
					lcd_write_effects(1);
				}
				break;
			case 0x0800:
				if (effects[1] < 100){
					effects[1]++;
					lcd_write_effects(1);
				}
				break;
			case 0x1000:
				if (effects[2] > 0){
					effects[2]--;
					lcd_write_effects(2);
				}
				break;
			case 0x2000:
				if (effects[2] < 100){
					effects[2]++;
					lcd_write_effects(2);
				}
				break;
			case 0x4000:
				if (effects[3] > 0){
					effects[3]--;
					lcd_write_effects(3);
				}
				break;
			case 0x8000:
				if (effects[3] < 100){
					effects[3]++;
					lcd_write_effects(3);
				}
				break;
			/*no action*/
			default:
				user_input = 0x0000;
			}
		user_input = 0;
	}
}

/*this menu is not being used yet*/
char menu_effect_edit(){
	unsigned int user_input = 0;

	/*setup menu*/
	menu_settings_setup();

	/*in menu actions*/
	while(1){
		wait_for_input();
		user_input = user_input_decode();
		//do actions for this menu relative to user input
	}

}

/*this menu is not being used yet*/
char menu_settings(){
	unsigned int user_input = 0;

	/*setup menu*/
	menu_settings_setup();

	/*in menu actions*/
	while(1){
		wait_for_input();
		user_input = user_input_decode();
		//do actions for this menu relative to user input
	}
}


