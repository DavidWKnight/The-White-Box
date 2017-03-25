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
void menu_settings();

unsigned int effects[4] = {0,0,0,0};
int current_effect = 0;

#include "misc.h"
#include "menu.h"
#include "lcd.h"
#include "interrupts.h"

extern char menu_settings_values[number_of_settings];

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
			case 0x0001:/*enc1 sw*/
				if (current_effect > 0){
					current_effect--;
					//write effect summary
				}
				break;
			case 0x0002:/*enc2 sw*/
				if (current_effect < max_effect_presets){
					current_effect++;
					//write effect summary
				}
				break;
			case 0x0004:/*enc3 sw*/
				return 2;/*enter menu effect edit*/
			case 0x0008:/*enc4 sw*/
				/*do nothing*/
				break;

			case 0x0010:/*sw left*/
				if (current_effect > 0){
					current_effect--;
					//write effect summary
				}
				break;
			case 0x0020:/*sw right*/
				if (current_effect < max_effect_presets){
					current_effect++;
					//write effect summary
				}
				break;
			case 0x0040:/*sw select*/
				/*enable effect*/
				break;
			case 0x0080:/*sw settings*/
				menu_settings();/*enter settings menu*/
				break;
			/*port 2*/
			case 0x0100:
				if (current_effect > 0){
					current_effect--;
					//write effect summary
				}
				break;
			case 0x0200:
				if (current_effect < max_effect_presets){
					current_effect++;
					//write effect summary
				}
				break;
			case 0x0400:
				break;
			case 0x0800:
				break;
			case 0x1000:
				break;
			case 0x2000:
				break;
			case 0x4000:
				break;
			case 0x8000:
				break;
			/*no action*/
			default:
				user_input = 0x0000;
			}
		user_input = 0;
	}
}

char menu_effect_edit(){
	unsigned int user_input = 0;

	/*setup menu*/
	menu_settings_setup();
	unsigned char active_effect;/*effect currently being edited*/

	/*in menu actions*/
	while(1){
		wait_for_input();
		user_input = user_input_decode();
		switch(user_input){
			/*port 1*/
			case 0x0001:/*enc1 sw*/
				if (active_effect > 0){
					active_effect--;
					/*write new effect data*/
				}
				break;
			case 0x0002:/*enc2 sw*/
			if (active_effect < max_effect_types){
				active_effect++;
				/*write new effect data*/
			}
				break;
			case 0x0004:/*enc3 sw*/
				break;
			case 0x0008:/*enc4 sw*/
				break;
			case 0x0010:/*sw left*/
				if (active_effect > 0){
					active_effect--;
					/*write new effect data*/
				}
				break;
			case 0x0020:/*sw right*/
				if (active_effect < max_effect_types){
					active_effect++;
					/*write new effect data*/
				}
				break;
			case 0x0040:/*sw select*/
				return 1;/*go back to effect menu select*/
			case 0x0080:/*sw settings*/
				menu_settings();/*go to settings menu*/
				break;
			/*port 2*/
			case 0x0100:
				if (effects[0] < 100){
					effects[0]++;
					lcd_write_effects(0);
				}
				break;
			case 0x0200:
				if (effects[0] > 0){
					effects[0]--;
					lcd_write_effects(0);
				}
				break;
			case 0x0400:
				if (effects[1] < 100){
					effects[1]++;
					lcd_write_effects(1);
				}
				break;
			case 0x0800:
				if (effects[1] > 0){
					effects[1]--;
					lcd_write_effects(1);
				}
				break;
			case 0x1000:
				if (effects[2] < 100){
					effects[2]++;
					lcd_write_effects(2);
				}
				break;
			case 0x2000:
				if (effects[2] > 0){
					effects[2]--;
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
				if (effects[3] > 0){
					effects[3]--;
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

void menu_settings(){
	unsigned int user_input = 0;

	/*setup menu*/
	menu_settings_setup();
	unsigned char current_setting = 0;/*current effect being edited*/

	/*in menu actions*/
	while(1){
		wait_for_input();
		user_input = user_input_decode();
		switch(user_input){
			/*port 1*/
			case 0x0001:/*enc1 sw*/
				if (current_setting > 0){
					current_setting++;
					/*write new setting page*/
				}
				break;
			case 0x0002:/*enc2 sw*/
				if (current_setting < number_of_settings){
					current_setting--;
					/*write new setting page*/
				}
				break;
			case 0x0004:/*enc3 sw*/
				if (current_setting < non_bool_settings){/*effects that aren't toggled will be less than compared number*/
					menu_settings_values[current_setting] ^= 0x01;
				}
				break;
			case 0x0008:/*enc4 sw*/
				return;/*go back to previous menu*/
			case 0x0010:/*sw left*/
				if (current_setting > 0){
					current_setting++;
					/*write new setting page*/
				}
				break;
			case 0x0020:/*sw right*/
				if (current_setting < number_of_settings){
					current_setting--;
					/*write new setting page*/
				}
				break;
			case 0x0040:/*sw select*/
				if (current_setting < non_bool_settings){/*effects that aren't toggled will be less than compared number*/
					menu_settings_values[current_setting] ^= 0x01;
				}
				break;
			case 0x0080:/*sw settings*/
				return;/*go back to previous menu*/
			/*port 2*/
			case 0x0100:
				if (current_setting > 0){
					current_setting++;
					/*write new setting page*/
				}
				break;
			case 0x0200:
				if (current_setting < number_of_settings){
					current_setting--;
					/*write new setting page*/
				}
				break;
			case 0x0400:
				if (current_setting >= non_bool_settings){/*effects that are toggled will be bigger than compared number*/
					if(menu_settings_values[current_setting] < setting_max_value){
						menu_settings_values[current_setting]++;
						/*write new setting page*/
					}
				}
				break;
			case 0x0800:
				if (current_setting >= non_bool_settings){/*effects that are toggled will be bigger than compared number*/
					if (menu_settings_values[current_setting] > 0){
						menu_settings_values[current_setting]--;
						/*write new setting page*/
					}
				}
				break;
			case 0x1000:
				break;
			case 0x2000:
				break;
			case 0x4000:
				break;
			case 0x8000:
				break;
			/*no action*/
			default:
				user_input = 0x0000;
			}
		user_input = 0;
	}
}


