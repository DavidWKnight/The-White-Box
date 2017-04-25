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
		wait_for_input();/*triggered by interrupts on P1 and P2 (buttons and encoders)*/

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
#ifdef launchpad
            if (current_preset != 0){ /*Preset 0 is reserved*/
                active_preset = current_preset;
                return 2;/*enter menu effect edit*/
            }
#else
            /*do nothing*/
            break;
#endif
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
	unsigned char active_effect = 0;/*effect currently being edited*/

	/*setup menu*/
	effect_edit_load_params(active_effect);
	full_update_DSP();
	update_LED();
	effect_edit_setup(active_effect);

	/*in menu actions*/
	while(1){
		wait_for_input();/*triggered by interrupts on P1 and P2 (buttons and encoders)*/

		/*send input to state machines*/
		switch(user_input_decode()){
        /*port 1*/
        case 0x0001:/*enc1 sw*/
            if (active_effect > 0){
                effect_edit_update_FX(&active_effect, 0x00);
            }
            break;

        case 0x0002:/*enc2 sw*/
            if (active_effect < max_effect_types-1){
                effect_edit_update_FX(&active_effect, 0x01);
            }
            break;

        case 0x0004:/*enc3 sw*/
            effect_edit_save_params(active_effect);
            return 1;

        case 0x0008:/*enc4 sw*/
#ifdef launchpad
            effect_edit_save_params(active_effect);
            return 1;
#else
            break;
#endif
        case 0x0010:/*sw left*/
            if (active_effect > 0){
                effect_edit_update_FX(&active_effect, 0x00);
            }
            break;

        case 0x0020:/*sw right*/
            if (active_effect < max_effect_types-1){
                effect_edit_update_FX(&active_effect, 0x01);
            }
            break;

        case 0x0040:/*sw select*/
            POUT_LED &= ~(1 << active_effect);
            return 1;/*go back to effect menu select*/

        case 0x0080:/*sw settings*/
            menu_effect_name_edit();/*edit name of effect*/
            effect_edit_setup(active_effect);
            break;

        /*port 2*/
        case 0x0100:
            effect_edit_change_param(active_effect, 0, 0);
            break;

        case 0x0200:
            effect_edit_change_param(active_effect, 0, 1);
            break;

        case 0x0400:
            effect_edit_change_param(active_effect, 1, 0);
            break;

        case 0x0800:
            effect_edit_change_param(active_effect, 1, 1);
            break;

        case 0x1000:
            effect_edit_change_param(active_effect, 2, 0);
            break;

        case 0x2000:
            effect_edit_change_param(active_effect, 2, 1);
            break;

        case 0x4000:
            effect_edit_change_param(active_effect, 3, 0);
            break;

        case 0x8000:
            effect_edit_change_param(active_effect, 3, 1);
            break;

        /*no action*/
        default:
            break;
        }

	}
}

void menu_settings(){
	/*setup menu*/
    static unsigned char current_setting = 4;/*current setting being edited*/
	settings_setup();
	settings_next_setting(current_setting);

    /*enabled RTC interrupt to cause cursor to flash onscreen*/
	unsigned int flash_delay = flash_delay_short;/*number of times to skip flash*/
    RTCIV;
    RTCCTL |= RTCIE;

	/*in menu actions*/
	while(1){
		wait_for_input();/*triggered by interrupts on P1 and P2 (buttons and encoders)*/

		/*send input to state machines*/
		switch(user_input_decode()){
		/*port 1*/
		case 0x0001:/*enc1 sw*/
            if (current_setting > 0){
                flash_delay = flash_delay_short;
                current_setting--;
                settings_next_setting(current_setting);
            }
            break;

        case 0x0002:/*enc2 sw*/
            if (current_setting < number_of_settings-1){
                flash_delay = flash_delay_short;
                current_setting++;
                settings_next_setting(current_setting);
            }
            break;

        case 0x0004:/*enc3 sw*/
            if (current_setting < non_bool_settings){/*effects that aren't toggled will be less than compared number*/
                flash_delay = flash_delay_reset;
                menu_settings_values[current_setting] ^= 0x01;
            }
            break;

        case 0x0008:/*enc4 sw*/
            return;/*go back to previous menu*/

        case 0x0010:/*sw left*/
            if (current_setting > 0){
                flash_delay = flash_delay_short;
                current_setting--;
                settings_next_setting(current_setting);
            }
            break;

        case 0x0020:/*sw right*/
            if (current_setting < number_of_settings-1){
                flash_delay = flash_delay_short;
                current_setting++;
                settings_next_setting(current_setting);
            }
            break;

        case 0x0040:/*sw select*/
            if (current_setting < non_bool_settings){/*effects that aren't toggled will be less than compared number*/
                menu_settings_values[current_setting] ^= 0x01;
                LCD_write_integer(3, 16, menu_settings_values[current_setting], 4);
            }
            break;

        case 0x0080:/*sw settings*/
            RTCCTL &= ~RTCIE;
            return;/*go back to previous menu*/

        /*port 2*/
        case 0x0100:
            if (current_setting > 0){
                flash_delay = flash_delay_short;
                current_setting--;
                settings_next_setting(current_setting);
            }
            break;

        case 0x0200:
            if (current_setting < number_of_settings-1){
                flash_delay = flash_delay_short;
                current_setting++;
                settings_next_setting(current_setting);
            }
            break;

        case 0x0400:
            if (current_setting >= non_bool_settings){/*effects that are toggled will be bigger than compared number*/
                if (menu_settings_values[current_setting] > 0){
                    menu_settings_values[current_setting]--;
                    LCD_write_integer(3, 16, menu_settings_values[current_setting], 4);
                }
            }
            break;

        case 0x0800:
            if (current_setting >= non_bool_settings){/*effects that are toggled will be bigger than compared number*/
                if(menu_settings_values[current_setting] < setting_max_value){
                    menu_settings_values[current_setting]++;
                    LCD_write_integer(3, 16, menu_settings_values[current_setting], 4);
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
		/*flashing black rectangle to display cursor location*/
        if (RTC_interrupt){
            LCD_cursor_pos(3,20);
            flash_cursor(&flash_delay, ' ', '<');
        }

	}
}

void menu_effect_name_edit(){
	unsigned char current_char = 0;/*current letter being changed*/
	unsigned char current_name = 0;/*0 for name_temp, 1 for name_short_temp*/
	/*setup menu*/


    struct effect_data *current_effect_ptr;

    current_effect_ptr = &all_effect_data + current_preset;

    char name_temp[2][LCD_line_length] = {"                    ","                    "};/*0 is name, 1 is name_short*/
    char name_temp_length[2] = {LCD_line_length-1,max_length_name_short-1};/*the last 14 characters of name_temp[0] are unused*/

    memcpy(name_temp[0], current_effect_ptr->name, LCD_line_length);
    memcpy(name_temp[1], current_effect_ptr->name_short, max_length_name_short);



	effect_name_edit_setup(name_temp);
	
	/*enabled RTC interrupt to cause cursor to flash onscreen*/
	unsigned int flash_delay = flash_delay_short;/*number of times to skip flash*/
    RTCIV;
    RTCCTL |= RTCIE;

	/*in menu actions*/
	while(1){
		wait_for_input();/*triggered by interrupts on P1 and P2 (buttons and encoders)*/

		/*send input to state machines*/
		switch(user_input_decode()){
        /*port 1*/
        case 0x0001:/*enc1 sw*/
            /*move cursor left*/
            if (current_char > 0){
                flash_delay = flash_delay_short;
                LCD_cursor_pos(2*current_name+2,current_char+1);
                LCD_write_data(name_temp[current_name][current_char]);
                current_char--;
            }
            break;

        case 0x0002:/*enc2 sw*/
            /*move cursor right*/
            if (current_char < name_temp_length[current_name]){
                flash_delay = flash_delay_short;
                LCD_cursor_pos(2*current_name+2,current_char+1);
                LCD_write_data(name_temp[current_name][current_char]);
                current_char++;
            }
            break;

        case 0x0004:/*enc3 sw*/
            /*toggle selected name*/
            flash_delay = flash_delay_short;
            LCD_cursor_pos(2*current_name+2,current_char+1);
            LCD_write_data(name_temp[current_name][current_char]);
            current_char = 0;
            current_name ^= 0x01;
            break;

        case 0x0008:/*enc4 sw*/
            /*toggle selected name*/
            flash_delay = flash_delay_short;
            LCD_cursor_pos(2*current_name+2,current_char+1);
            LCD_write_data(name_temp[current_name][current_char]);
            current_char = 0;
            current_name ^= 0x01;
            break;

        case 0x0010:/*sw left*/
            break;

        case 0x0020:/*sw right*/
            break;

        case 0x0040:/*sw select*/
            /*save new effect name*/
            RTCCTL &= ~RTCIE;
            memcpy(current_effect_ptr->name, name_temp[0], LCD_line_length);
            memcpy(current_effect_ptr->name_short, name_temp[1], max_length_name_short);
            return;

        case 0x0080:/*sw settings*/
            /*dont save new effect name*/
            RTCCTL &= ~RTCIE;
            return;

        /*port 2*/
        case 0x0100:
            /*move cursor left*/
            if (current_char > 0){
                flash_delay = flash_delay_short;
                LCD_cursor_pos(2*current_name+2,current_char+1);
                LCD_write_data(name_temp[current_name][current_char]);
                current_char--;
            }
            break;

        case 0x0200:
            /*move cursor right*/
            if (current_char < name_temp_length[current_name]){
                flash_delay = flash_delay_short;
                LCD_cursor_pos(2*current_name+2,current_char+1);
                LCD_write_data(name_temp[current_name][current_char]);
                current_char++;
            }
            break;

        case 0x0400:
            if (name_temp[current_name][current_char] > 0x20){
                /*decrement selected character*/
                flash_delay = flash_delay_reset;
                name_temp[current_name][current_char]--;
                LCD_cursor_pos(2*current_name+2,current_char+1);
                LCD_write_data(name_temp[current_name][current_char]);
            }
            break;

        case 0x0800:
            /*increment selected character*/
            if (name_temp[current_name][current_char] < 0x7F){
                flash_delay = flash_delay_reset;
                name_temp[current_name][current_char]++;
                LCD_cursor_pos(2*current_name+2,current_char+1);
                LCD_write_data(name_temp[current_name][current_char]);
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
		/*flashing black rectangle to display cursor location*/
	    if (RTC_interrupt){
	        LCD_cursor_pos(2*current_name+2,current_char+1);
	        flash_cursor(&flash_delay, name_temp[current_name][current_char], 0xFF);
	    }

	}
}
