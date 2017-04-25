/*
 * menu_support.c
 *
 *  Created on: Mar 25, 2017
 *      Author: bigbird42
 */


#include "menu_support.h"


unsigned int encoder_state = 0x00;
const unsigned char encoder_state_decoder[13][4] = {
		{0x00,0x01,0x08,0x00},//0x00
		//CCW
		{0x00,0x01,0x00,0x03},//0x01
		{0x0F,0x00,0x02,0x03},//0x02
		{0x00,0x01,0x02,0x03},//0x03
		//CW
		{0xF0,0x04,0x00,0x0C},/*0x04*/  /*unused*/{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},
		{0x00,0x00,0x08,0x0C},/*0x08*/  /*unused*/{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},
		{0x00,0x04,0x08,0x0C} /*0x0C*/
};

#pragma PERSISTENT(all_effect_data)
struct effect_data all_effect_data[max_effect_presets] = {
		{.name = "      No Effect     ", .name_short = "No FX "},/*Preset 0 is reserved as the default no effect preset*/
		{.name = "      Preset    1   ", .name_short = "PR   1", .effect_value[0][0] = 1},
		{.name = "      Preset    2   ", .name_short = "PR   2", .effect_value[1][0] = 1},
		{.name = "      Preset    3   ", .name_short = "PR   3", .effect_value[2][0] = 1},
		{.name = "      Preset    4   ", .name_short = "PR   4", .effect_value[3][0] = 1},
		{.name = "      Preset    5   ", .name_short = "PR   5", .effect_value[4][0] = 1},
		{.name = "      Preset    6   ", .name_short = "PR   6", .effect_value[5][0] = 1},
		{.name = "      Preset    7   ", .name_short = "PR   7", .effect_value[6][0] = 1},
		{.name = "      Preset    8   ", .name_short = "PR   8", .effect_value[7][0] = 1},
		{.name = "      Preset    9   ", .name_short = "PR   9", .effect_value[7][0] = 1, .effect_value[7][0] = 1, .effect_value[6][0] = 1, .effect_value[5][0] = 1, .effect_value[4][0] = 1, .effect_value[3][0] = 1, .effect_value[2][0] = 1, .effect_value[1][0] = 1, .effect_value[0][0] = 1},
		};

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

/*settings menu*/
const char menu_settings_header[1][LCD_line_length] = {"   Settings Menu    "};
const char menu_settings_names[number_of_settings][setting_name_length] = {"setting 1     ", "setting 2     ", "setting 3     ", "LED brightness", "LCD Brightness"};
#pragma PERSISTENT(menu_settings_values)
unsigned char menu_settings_values[number_of_settings] = {1,1,1,20,20};

/*takes debounced inputs and runs them through state machines*/
unsigned int user_input_decode(){
	if (port1_state > 0){
		/*port 1*/
		switch (port1_state){
			case 0x01:
				return port1_statemachine(0x0001);
			case 0x02:
				return port1_statemachine(0x0002);
			case 0x04:
				return port1_statemachine(0x0004);
			case 0x08:
				return port1_statemachine(0x0008);
			case 0x10:
				return port1_statemachine(0x0010);
			case 0x20:
				return port1_statemachine(0x0020);
			case 0x40:
				return port1_statemachine(0x0040);
			case 0x80:
				return port1_statemachine(0x0080);
			default:
				port1_state = 0x00;
				/*This should reset all of port 1, IES mask .. everything*/
				break;
		}
	}
	else if (port2_state > 0){
		/*port 2*/
		switch (port2_state){
			case 0x01:
				return port2_statemachine(0x01, 0x00);
			case 0x02:
				return port2_statemachine(0x02, 0x00);
			case 0x04:
				return port2_statemachine(0x04, 0x04);
			case 0x08:
				return port2_statemachine(0x08, 0x04);
			case 0x10:
				return port2_statemachine(0x10, 0x08);
			case 0x20:
				return port2_statemachine(0x20, 0x08);
			case 0x40:
				return port2_statemachine(0x40, 0x0C);
			case 0x80:
				return port2_statemachine(0x80, 0x0C);
			default:
				port2_state = 0x00;
				break;
		}
	}

	return 0;
}

/*state machine for pushbutton*/
unsigned int port1_statemachine(unsigned int pin){
	__disable_interrupt();
	port1_state &= ~pin;
	if ((port1_mask & pin) == pin){
		port1_mask &= ~pin;
		P1IES &= ~pin;
	}
	else if((port1_mask & pin) == 0x00){
		port1_mask |= pin;
		P1IES |= pin;
		P1IFG &= ~pin;
		__enable_interrupt();
		return pin;
	}
	else{
		port1_mask |= pin;
		P1IES |= pin;
	}
	P1IFG &= ~pin;
	__enable_interrupt();
	return 0;
}

/*This function is untested for encoder 4 because I don't have access to it on the MSP430FR4133 Launchpad*/
unsigned int port2_statemachine(unsigned int pin, unsigned char encoder_shift){
	__disable_interrupt();
	port2_state &= ~pin;

	unsigned char encoder_number2 = (encoder_shift >> 1);//encoder number multiplied by 2
	unsigned int encoder_state_last = (encoder_state >> encoder_shift) & 0x000F;//previous state for encoder being processed
	unsigned int encoder_state_new = 0x00;

	/*calculate new encoder state*/
	if (encoder_state_last > 3){//right adjust encoder_state_new
		encoder_state_new = encoder_state_last >> 2;
	}
	else{
		encoder_state_new = encoder_state_last;
	}
	encoder_state_new ^= (pin >> encoder_number2);

	unsigned int encoder_state_temp = encoder_state_decoder[encoder_state_last][encoder_state_new];//process new state

	if(encoder_state_temp == 0x00){//invalid state/reset: reset encoder, return 0
		encoder_state &= ~(0x000F << encoder_shift);
		port2_mask |= (0x03 << encoder_number2);
		P2IES |= (0x03 << encoder_number2);
		P2IFG &= ~(0x03 << encoder_number2);
		__enable_interrupt();
		return 0x0000;
	}

	else if(encoder_state_temp == 0xF0 || encoder_state_temp == 0x0F){//successful rotation: reset encoder, return pin
		encoder_state &= ~(0x000F << encoder_shift);
		port2_mask |= (0x03 << encoder_number2);
		P2IES |= (0x03 << encoder_number2);
		P2IFG &= ~(0x03 << encoder_number2);
		__enable_interrupt();
		return (pin << 8);
	}

	/*between states: save updated encoder state, toggle mask and edge select, return 0*/
	encoder_state = (encoder_state_temp << encoder_shift);
	port2_mask ^= pin;
	P2IES ^= pin;
	P2IFG &= ~pin;
	__enable_interrupt();
	return 0x0000;
}

/*waits for user input or an interrupt from a peripheral; goes into low power mode if there is no input*/
void wait_for_input(){
	while(1){
		bool waiting = true;
		if(port1_interrupt){
			waiting = false;
			TA0CTL |= MC_1;//start timer for debouncing
			port1_interrupt = false;
		}
		if (port2_interrupt){
			waiting = false;
			TA1CTL |= MC_1;//start timer for debouncing
			port2_interrupt = false;
		}
		if(new_user_input){
			waiting = false;
			new_user_input = false;
			return;
		}
		if(RTC_interrupt){
			waiting = false;
			new_user_input = false;
			return;
		}
		if (waiting){
			//go into sleep mode
			_BIS_SR(LPM4_bits + GIE);
		}
	}
}

/*does a full update of the DSP*/
void full_update_DSP(){
	unsigned int i, j;

	for (i = 0; i < max_effect_types; i++){
		for (j = 0; j < max_effect_param; j++){
			update_DSP(i,j);
			/*wait for SPI to finish transmitting*/
		}
	}

	return;
}

/*updates the DSP with a single effect and a single parameter*/
void update_DSP(unsigned int effect, unsigned int param){
	unsigned int temp = 0;
	temp |= (effect << 10) + (param << 8) + (all_effect_data[active_preset].effect_value[effect][param]);
	/*write temp to SPI TX then return*/

	/* add a small pattern of 1's that show a new effect is being sent; 3 bits like 101
	 * 3 bits - effect #
	 * 2 bits - parameter #
	 * 8 bits - parameter value
	 */
	return;
}

/*does a full update of the LED's*/
void update_LED(){
	unsigned int i, j;
	unsigned char leds = 0x00;
	for (i = 0; i < max_effect_types; i++){
		unsigned int temp = 0x00;
		for (j = 0; j < max_effect_param; j++){
			temp |= all_effect_data[current_preset].effect_value[i][j];
		}
		/*set bit i if that effect is active*/
		if (temp > 0){
			leds |= (1 << i);
		}
	}
	POUT_LED = leds;
	return;
}

/*alternates between cursor_char and flash_char being displayed on screen*/
void flash_cursor(unsigned int *flash_delay, char cursor_char, char flash_char){
    static unsigned char flashing = 0;

    if (flashing == 0x00){
        if ((*flash_delay) > flash_delay_max) {
            (*flash_delay) = flash_delay_short;
            LCD_write_data(flash_char);
            flashing ^= 0xFF;
        }
        else{
            (*flash_delay)++;
        }
    }
    else {
        LCD_write_data(cursor_char);
        flashing ^= 0xFF;
    }
    RTC_interrupt = false;

    return;
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

