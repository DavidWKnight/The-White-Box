/*
 * menu_effect_edit.c
 *
 *  Created on: Jun 11, 2017
 *      Author: bigbird42
 */

#include "menu_effect_edit.h"

 const char effects_available[max_effect_types][LCD_line_length] = {"        Wah         ", "      Ring Mod      ", "       Phaser       ",
        "     Drive/Fuzz     ", "       Flange       ", "    Pitch Shift     ", "       Delay        ", "    Trem/Vibrato    "};

static const int effect_min_max_val[max_effect_types][max_effect_param*2] = {
        {0,0,0,0,100,100,100,100},
        {0,0,0,0,100,100,100,100},
        {0,0,0,0,100,100,100,100},
        {0,0,0,0,100,100,100,100},
        {0,0,0,0,100,100,100,100},
        {0,0,0,0,100,100,100,100},
        {0,0,0,0,100,100,100,100},
        {0,0,0,0,100,100,100,100}
};



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
            POUT_LED ^= (1 << active_effect);
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

void effect_edit_setup(unsigned char active_effect){
	const char line_3[LCD_line_length] = "  FX1| FX2| FX3| FX4";
	unsigned int i;

	LCD_write_cmd(0x01);//clear display

	/*line 1*/
	LCD_cursor_pos(1,1);
	for (i = 0; i < LCD_line_length; i++){
		LCD_write_data(all_effect_data[current_preset].name[i]);
	}
	/*line 2*/
	LCD_cursor_pos(2,1);
	for (i = 0; i < LCD_line_length; i++){
		LCD_write_data(effects_available[active_effect][i]);
	}
	/*line 3*/
	LCD_cursor_pos(3,1);
	for (i = 0; i < LCD_line_length; i++){
		LCD_write_data(line_3[i]);
	}
	/*line 4*/
	for (i = 0; i < max_effect_param; i++){
		effect_edit_write_FX(i);
		if(i < 3){
			LCD_write_data('|');
		}
	}


	return;
}

/*saves the data currently in effects[]*/
void effect_edit_save_params(unsigned char active_effect){
	unsigned int i = 0;
	for (i = 0; i < max_effect_param; i++){
		all_effect_data[current_preset].effect_value[active_effect][i] = effects[i];
	}
	return;
}

/*loads the parameters of the current effect being edited*/
void effect_edit_load_params(unsigned char active_effect){
	unsigned int i = 0;
	for (i = 0; i < max_effect_param; i++){
		effects[i] = all_effect_data[current_preset].effect_value[active_effect][i];
	}
	return;
}

/*writes the value of a give parameter of the current active effect onto the bottom row of the LCD*/
void effect_edit_write_FX(unsigned int effect_param){
	LCD_write_integer(4, ( (effect_param * (LCD_line_length / 4)) + 2), effects[effect_param], 4);
}

/*update screen for new effect info*/
void effect_edit_update_FX(unsigned char *active_effect, unsigned char increment){
	unsigned int i, temp;

	effect_edit_save_params(*active_effect);

	/*update current LED*/
	for (i = 0, temp = 0; i < max_effect_param; i++){
		temp += effects[i];
	}
	if (temp > 0){
		POUT_LED |= (1 << (*active_effect) );
	}
	else {
		POUT_LED &= ~(1 << (*active_effect) );
	}

	/*increment/decrement active effect*/
	if(increment == 1){
		(*active_effect)++;
	}
	else{
		(*active_effect)--;
	}

	effect_edit_load_params(*active_effect);

	/*update new LED*/
	for (i = 0, temp = 0; i < max_effect_param; i++){
		temp += effects[i];
	}
	if (temp > 0){
		POUT_LED |= (1 << (*active_effect) );
	}
	else {
		POUT_LED &= ~(1 << (*active_effect) );
	}

	/*update LCD line 2*/
	LCD_cursor_pos(2,1);
	for (i = 0; i < LCD_line_length; i++){
	    LCD_write_data(effects_available[*active_effect][i]);
	}
	/*line 4*/
	for (i = 0; i < max_effect_param; i++){
        effect_edit_write_FX(i);
    }

	return;
}

/*increment or decrement active_effect parameter*/
void effect_edit_change_param(unsigned char active_effect, unsigned char param, unsigned char increment){
    if(increment == 1){
        if(effects[param] < effect_min_max_val[active_effect][param+4]){
            effects[param]++;
            effect_edit_write_FX(param);
            update_DSP(active_effect, param);
            effect_edit_update_leds(active_effect);
        }
    }
    else if(increment == 0){
        if(effects[param] > effect_min_max_val[active_effect][param]){
            effects[param]--;
            effect_edit_write_FX(param);
            update_DSP(active_effect, param);
            effect_edit_update_leds(active_effect);
        }
    }
    else{
        //error
        return;
    }
    return;
}

/*update LEDs after effect parameter change*/
void effect_edit_update_leds(unsigned char active_effect){
    unsigned int i, temp;

    for (i = 0, temp = 0; i < max_effect_param; i++){
        temp += effects[i];
    }
    if (temp > 0){
        POUT_LED |= (1 << active_effect);
    }
    else {
        POUT_LED &= ~(1 << active_effect);
    }
    return;
}

void menu_effect_name_edit(){
	unsigned char current_char = 0;/*current letter being changed*/
	unsigned char current_name = 0;/*0 for name_temp, 1 for name_short_temp*/

	/*setup menu*/
    struct effect_data *current_effect_ptr;

    current_effect_ptr = &all_effect_data[0] + current_preset;

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
            RTC_interrupt != RTC_interrupt;
            memcpy(current_effect_ptr->name, name_temp[0], LCD_line_length);
            memcpy(current_effect_ptr->name_short, name_temp[1], max_length_name_short);
            return;

        case 0x0080:/*sw settings*/
            /*dont save new effect name*/
            RTCCTL &= ~RTCIE;
            RTC_interrupt != RTC_interrupt;
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

void effect_name_edit_setup(char name[2][LCD_line_length]){
	const char edit_name_header[2][LCD_line_length] = {"Edit Effect Name:   ", "Effect Nickname:    "};
	unsigned int i,j;

	LCD_write_cmd(0x01);//clear display

	for (i = 0; i < 2; i++){
		LCD_cursor_pos(i * 2 + 1,1);
		for (j = 0; j < LCD_line_length; j++){
			LCD_write_data(edit_name_header[i][j]);
		}
	}
	for (i = 0; i < 2; i++){
		LCD_cursor_pos(i * 2 + 2,1);
		for (j = 0; j < LCD_line_length; j++){
			LCD_write_data(name[i][j]);
		}
	}
	LCD_cursor_pos(4,7);
	LCD_write_data('|');

	return;
}
