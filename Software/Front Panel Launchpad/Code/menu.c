/*
 * menu.c
 *
 *  Created on: Feb 24, 2017
 *      Author: bigbird42
 */


#include "menu.h"

/*variables defined in menu.c*/
unsigned int effects[4] = {0,0,0,0};

char menu_effect_select(){
	unsigned int user_input = 0;

	/*setup menu*/
	effect_select_setup();
	effect_select_write_effects();

	/*in menu actions*/
	while(1){
		wait_for_input(); /*triggered by interrupts on P1 and P2 (buttons and encoders)*/
		user_input = user_input_decode();//send input to state machines
		switch(user_input){
			/*port 1*/
			case 0x0001:/*enc1 sw*/
				if (current_preset > 0){
					current_preset--;
					//write effect summary
				}
				break;
			case 0x0002:/*enc2 sw*/
				if (current_preset < max_effect_presets){
					current_preset++;
					//write effect summary
				}
				break;
			case 0x0004:/*enc3 sw*/
				return 2;/*enter menu effect edit*/
			case 0x0008:/*enc4 sw*/
				/*do nothing*/
				break;

			case 0x0010:/*sw left*/
				if (current_preset > 0){
					current_preset--;
					//write effect summary
				}
				break;
			case 0x0020:/*sw right*/
				if (current_preset < max_effect_presets){
					current_preset++;
					//write effect summary
				}
				break;
			case 0x0040:/*sw select*/
				/*enable effect*/
				break;
			case 0x0080:/*sw settings*/
				menu_settings();/*enter settings menu*/
				/*setup menu again*/
				break;
			/*port 2*/
			case 0x0100:
				if (current_preset > 0){
					current_preset--;
					//write effect summary
				}
				break;
			case 0x0200:
				if (current_preset < max_effect_presets){
					current_preset++;
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
	settings_setup(); /*triggered by interrupts on P1 and P2 (buttons and encoders)*/
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
				menu_effect_name_edit();/*edit name of effect*/
				/*setup menu again*/
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
	settings_setup(); /*triggered by interrupts on P1 and P2 (buttons and encoders)*/
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

/*need to add supprot to edit name_short in this menu, can be just done on another line*/
void menu_effect_name_edit(){
	unsigned int user_input = 0;

	/*setup menu*/
	struct effect_data *current_effect_ptr;
	current_effect_ptr = (&all_effect_data + (sizeof(struct effect_data) * current_preset));
	char name_temp[LCD_line_length];
	memcpy(name_temp, current_effect_ptr->name, LCD_line_length);

	unsigned char current_char = 0;/*current letter being changed*/

	/*in menu actions*/
	while(1){
		wait_for_input(); /*triggered by interrupts on P1 and P2 (buttons and encoders)*/
		user_input = user_input_decode();//send input to state machines
		switch(user_input){
			/*port 1*/
			case 0x0001:/*enc1 sw*/
				if (current_char > 0){
					current_char--;
				}
				break;
			case 0x0002:/*enc2 sw*/
				if (current_char < 19){
					current_char++;
				}
				break;
			case 0x0004:/*enc3 sw*/
				if (name_temp[current_char] > 0x20){
					name_temp[current_char]++;
				}
				break;
			case 0x0008:/*enc4 sw*/
				if (name_temp[current_char] < 0x78){
					name_temp[current_char]--;
				}
				break;
			case 0x0010:/*sw left*/
				break;
			case 0x0020:/*sw right*/
				break;
			case 0x0040:/*sw select*/
				/*save new effect name*/
				memcpy(current_effect_ptr->name, name_temp, LCD_line_length);
				return;
			case 0x0080:/*sw settings*/
				/*dont save new effect name*/
				return;
			/*port 2*/
			case 0x0100:
				if (current_char > 0){
					current_char--;
				}
				break;
			case 0x0200:
				if (current_char < 19){
					current_char++;
				}
				break;
			case 0x0400:
				if (name_temp[current_char] > 0x20){
					name_temp[current_char]++;
				}
				break;
			case 0x0800:
				if (name_temp[current_char] < 0x78){
					name_temp[current_char]--;
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
