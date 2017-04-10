/*
 * menu.c
 *
 *  Created on: Feb 24, 2017
 *      Author: bigbird42
 */


#include "menu.h"



char menu_effect_select(){
	/*setup menu*/
	effect_select_setup();
	effect_select_write_effects();

	/*in menu actions*/
	while(1){
		wait_for_input(); /*triggered by interrupts on P1 and P2 (buttons and encoders)*/
		/*send input to state machines*/
		switch(user_input_decode()){
			/*port 1*/
			case 0x0001:/*enc1 sw*/
				if (current_preset > 0){
					current_preset--;
					effect_select_write_effects();
				}
				break;
			case 0x0002:/*enc2 sw*/
				if (current_preset < max_effect_presets-1){
					current_preset++;
					effect_select_write_effects();
				}
				break;
			case 0x0004:/*enc3 sw*/
				if (current_preset != 0){ /*Preset 0 is reserved*/
					active_preset = current_preset;
					return 2;/*enter menu effect edit*/
				}
			case 0x0008:/*enc4 sw*/
				/*do nothing*/
				break;

			case 0x0010:/*sw left*/
				if (current_preset > 0){
					current_preset--;
					effect_select_write_effects();
				}
				break;
			case 0x0020:/*sw right*/
				if (current_preset < max_effect_presets-1){
					current_preset++;
					effect_select_write_effects();
				}
				break;
			case 0x0040:/*sw select*/
				active_preset = current_preset;
				full_update_DSP();
				update_LED();
				effect_select_update_active();
				break;
			case 0x0080:/*sw settings*/
				menu_settings();/*enter settings menu*/
				effect_select_setup();
				effect_select_write_effects();
				break;
			/*port 2*/
			case 0x0100:
				if (current_preset > 0){
					current_preset--;
					effect_select_write_effects();
				}
				break;
			case 0x0200:
				if (current_preset < max_effect_presets-1){
					current_preset++;
					effect_select_write_effects();
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
				break;
			}
	}
}

char menu_effect_edit(){
	unsigned int temp = 0;
	unsigned int i = 0;
	unsigned char active_effect = 0;/*effect currently being edited*/

	/*setup menu*/
	effect_edit_load_params(active_effect);
	full_update_DSP();
	update_LED();
	effect_edit_setup(active_effect);

	/*in menu actions*/
	while(1){
		wait_for_input();

		switch(user_input_decode()){
			/*port 1*/
			case 0x0001:/*enc1 sw*/
				if (active_effect > 0){
					effect_edit_save_params(active_effect);
					active_effect--;
					effect_edit_load_params(active_effect);
					effect_edit_setup(active_effect);
				}
				break;

			case 0x0002:/*enc2 sw*/
				if (active_effect < max_effect_types){
					effect_edit_save_params(active_effect);
					active_effect++;
					effect_edit_load_params(active_effect);
					effect_edit_setup(active_effect);
				}
				break;

			case 0x0004:/*enc3 sw*/
				effect_edit_save_params(active_effect);
				return 1;

			case 0x0008:/*enc4 sw*/
				break;

			case 0x0010:/*sw left*/
				if (active_effect > 0){
					effect_edit_save_params(active_effect);
					active_effect--;
					effect_edit_load_params(active_effect);
					effect_edit_setup(active_effect);
				}
				break;

			case 0x0020:/*sw right*/
				if (active_effect < max_effect_types){
					effect_edit_save_params(active_effect);
					active_effect++;
					effect_edit_load_params(active_effect);
					effect_edit_setup(active_effect);
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
				if (effects[0] > 0){
					effects[0]--;
					effect_edit_write_FX(0);
					update_DSP(active_effect, 0);
				}
				break;

			case 0x0200:
				if (effects[0] < 100){
					effects[0]++;
					effect_edit_write_FX(0);
					update_DSP(active_effect, 0);
				}
				break;

			case 0x0400:
				if (effects[1] > 0){
					effects[1]--;
					effect_edit_write_FX(1);
					update_DSP(active_effect, 1);
				}
				break;

			case 0x0800:
				if (effects[1] < 100){
					effects[1]++;
					effect_edit_write_FX(1);
					update_DSP(active_effect, 1);
				}
				break;

			case 0x1000:
				if (effects[2] > 0){
					effects[2]--;
					effect_edit_write_FX(2);
					update_DSP(active_effect, 2);
				}
				break;

			case 0x2000:
				if (effects[2] < 100){
					effects[2]++;
					effect_edit_write_FX(2);
					update_DSP(active_effect, 2);
				}
				break;

			case 0x4000:
				if (effects[3] > 0){
					effects[3]--;
					effect_edit_write_FX(3);
					update_DSP(active_effect, 3);
				}
				break;

			case 0x8000:
				if (effects[3] > 0){
					effects[3]--;
					effect_edit_write_FX(3);
					update_DSP(active_effect, 3);
				}
				break;

			/*no action*/
			default:
				break;
			}
		/*update leds*/
		for (i = 0; i < max_effect_param; i++){
			temp += effects[i];
		}
		if (temp > 0){
			POUT_LED |= (1 << active_effect);
		}
		else {
			POUT_LED &= ~(1 << active_effect);
		}

	}

}

void menu_settings(){
	/*setup menu*/
	settings_setup(); /*triggered by interrupts on P1 and P2 (buttons and encoders)*/
	unsigned char current_setting = 0;/*current effect being edited*/

	/*in menu actions*/
	while(1){
		wait_for_input();
		switch(user_input_decode()){
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
				break;
			}

	}
}

/*need to add support to edit name_short in this menu, can be just done on another line*/
void menu_effect_name_edit(){
	/*setup menu*/
	struct effect_data *current_effect_ptr;
	current_effect_ptr = (&all_effect_data + (sizeof(struct effect_data) * current_preset));
	char name_temp[LCD_line_length];
	memcpy(name_temp, current_effect_ptr->name, LCD_line_length);

	unsigned char current_char = 0;/*current letter being changed*/

	/*in menu actions*/
	while(1){
		wait_for_input(); /*triggered by interrupts on P1 and P2 (buttons and encoders)*/
		switch(user_input_decode()){
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
				break;
			}

	}
}
