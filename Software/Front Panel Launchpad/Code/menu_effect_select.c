/*
 * menu_effect_select.c
 *
 *  Created on: Jun 11, 2017
 *      Author: bigbird42
 */

#include "menu_effect_select.h"

/*settings menu*/
const char menu_settings_header[1][LCD_line_length] = {"   Settings Menu    "};
const char menu_settings_names[number_of_settings][setting_name_length] = {"setting 1     ", "setting 2     ", "setting 3     ", "LED brightness", "LCD Brightness"};
#pragma PERSISTENT(menu_settings_values)
unsigned char menu_settings_values[number_of_settings] = {1,1,1,20,20};

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

void effect_select_setup(){
	const char menu_effect_select_header[LCD_line_length] = {" Effect Select Menu "};
	unsigned int i;

	LCD_write_cmd(0x01);//clear display

	/*line 1*/
	LCD_cursor_pos(1,1);
	for (i = 0; i < LCD_line_length; i++){
		LCD_write_data(menu_effect_select_header[i]);
	}
	/*line 2*/
	effect_select_update_active();

	/*put | on bottom 2 lines*/
	LCD_cursor_pos(3,6);
	LCD_write_data('|');
	LCD_cursor_pos(3,15);
	LCD_write_data('|');
	LCD_cursor_pos(4,6);
	LCD_write_data('|');
	LCD_cursor_pos(4,15);
	LCD_write_data('|');

	return;
}

/*write the name of the active effect to line 2*/
void effect_select_update_active(){
	unsigned int i;

	LCD_cursor_pos(2,1);
	for (i = 0; i < LCD_line_length; i++){
		LCD_write_data(all_effect_data[active_preset].name[i]);
	}

	return;
}

/*writes the summary of current effect preset in menu_effect_select*/
void effect_select_write_effects(){
	const unsigned int start[4] = {1,8,16};
	const unsigned int length[4] = {5,6,5};
	unsigned int i;
	unsigned int j;

	/*write to line 3, string*/
	for (i = 0; i < 3; i++){
		LCD_cursor_pos(3,start[i]);

		if (current_preset+i == 0 || current_preset+i == max_effect_presets+1){
			for (j = 0; j < length[i]; j++){
				LCD_write_data(' ');
			}
		}
		else{
			for (j = 0; j < length[i]; j++){
				LCD_write_data(all_effect_data[current_preset+i-1].name_short[j]);
			}
		}
	}

	/*write to line 4, string*/
	for (i = 0; i < 3; i++){
		LCD_cursor_pos(4,start[i]);

		if (current_preset+i == 0 || current_preset+i == max_effect_presets+1){
			for (j = 0; j < length[i]; j++){
				LCD_write_data(' ');
			}
		}
		else{
			for (j = 0; j < length[i]; j++){
				LCD_write_data(all_effect_data[current_preset+i-1].name_short[j]);
			}
		}
	}

	return;
}

void menu_settings(){
	/*setup menu*/
    static unsigned char current_setting = 4;/*current setting being edited*/
	settings_setup();
	settings_write_settings(current_setting);

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
                settings_write_settings(current_setting);
            }
            break;

        case 0x0002:/*enc2 sw*/
            if (current_setting < number_of_settings-1){
                flash_delay = flash_delay_short;
                current_setting++;
                settings_write_settings(current_setting);
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
                settings_write_settings(current_setting);
            }
            break;

        case 0x0020:/*sw right*/
            if (current_setting < number_of_settings-1){
                flash_delay = flash_delay_short;
                current_setting++;
                settings_write_settings(current_setting);
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
            RTC_interrupt != RTC_interrupt;
            return;/*go back to previous menu*/

        /*port 2*/
        case 0x0100:
            if (current_setting > 0){
                flash_delay = flash_delay_short;
                current_setting--;
                settings_write_settings(current_setting);
            }
            break;

        case 0x0200:
            if (current_setting < number_of_settings-1){
                flash_delay = flash_delay_short;
                current_setting++;
                settings_write_settings(current_setting);
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
        /*implement current setting values*/
        TA1CCR2 = 10*menu_settings_values[setting_LED_brightness];
        TA1CCR1 = 10*menu_settings_values[setting_LCD_brightness];
	}
}

void settings_setup(){
	unsigned int i;

	LCD_write_cmd(0x01);//clear display

	LCD_cursor_pos(1,1);
	for (i = 0; i < LCD_line_length; i++){
		LCD_write_data(menu_settings_header[0][i]);
	}

	return;
}

/*Writes the setting currently being edited to the LCD*/
void settings_write_settings(unsigned char current_setting){
    unsigned int j, row;
    int i;

    for(i = current_setting - 1, row = 2; i < (current_setting + 2); i++, row++){
        LCD_cursor_pos(row, 1);
        if( (i < 0) || (i > number_of_settings-1) ){
            for(j = 0; j < LCD_line_length; j++){
                LCD_write_data(' ');
            }
            continue;
        }

        for(j = 0; j < setting_name_length; j++){
            LCD_write_data(menu_settings_names[i][j]);
        }
        LCD_write_integer(row, 16, menu_settings_values[i], 4);
    }


    return;
}
