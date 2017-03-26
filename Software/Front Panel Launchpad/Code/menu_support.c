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

/*effect edit menu*/
const char effects_available[8][LCD_line_length] = {"        Wah         ", "      Ring Mod      ", "       Phaser       ",
		"     Drive/Fuzz     ", "       Flange       ", "    Pitch Shift     ", "       Delay        ", "    Trem/Vibrato    "};

#pragma PERSISTENT(all_effect_data)
struct effect_data all_effect_data[max_effect_presets] = {
		{.preset_number = 0, .name = "Preset 1"},
		{.preset_number = 1, .name = "Preset 2"},
		{.preset_number = 2, .name = "Preset 3"},
		{.preset_number = 3, .name = "Preset 4"},
		{.preset_number = 4, .name = "Preset 5"},
		{.preset_number = 5, .name = "Preset 6"},
		{.preset_number = 6, .name = "Preset 7"},
		{.preset_number = 7, .name = "Preset 8"},
		{.preset_number = 8, .name = "Preset 9"},
		{.preset_number = 9, .name = "Preset 10"}
		/*use memcpy to change name in program*/
		/* Python script to generate above:
		 * for i in range (0,10,1):
		 * 	   print("{.preset_number = " + str(i) + ", .name = \"Preset " + str(i+1) + "\"},")
		 */
};

/*settings menu*/
const char menu_settings_header[1][LCD_line_length] = {"   Settings Menu    "};
const char menu_settings_names[number_of_settings][14] = {"setting 1", "LED brightness", "LCD Brightness"};
char menu_settings_values[number_of_settings] = {0,0,0};

/*takes debounced inputs and runs them through state machines*/
unsigned int user_input_decode(){
	if (port1_state > 0){
		/*port 1*/
		switch (port1_state){
			case 0x0001:
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

/*This function is untested for encoders 2,3 and 4 because I don't have access to them on the MSP430FR4133 Launchpad*/
unsigned int port2_statemachine(unsigned int pin, unsigned char encoder_shift){
	__disable_interrupt();
	port2_state &= ~pin;

	unsigned char encoder_number2 = (encoder_shift >> 1);//encoder number multiplied by 2
	unsigned int encoder_state_last = (encoder_state  >> encoder_shift) & 0x000F;//previous state for encoder being processed
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

	//between states: save updated encoder state, toggle mask and edge select, return 0
	encoder_state = (encoder_state_temp << encoder_shift);
	port2_mask ^= pin;
	P2IES ^= pin;
	P2IFG &= ~pin;
	__enable_interrupt();
	return 0x0000;
}

/*waits for user input on port 1 or port 2; goes into low power mode if there is no input*/
void wait_for_input(){
	bool waiting = true;
	while(1){
		waiting = true;
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


		if (waiting){
			//go into sleep mode
			_BIS_SR(LPM4_bits + GIE);
		}
	}
}

void menu_effect_select_setup(){
	/*effect select menu*/
	const char menu_effect_select_header[2][LCD_line_length] = {" Effect Select Menu ","   Effect Select    "};
	unsigned int i;
	unsigned int j;
	for (i = 0, j = 2; j > 0; j--){
		LCD_cursor_pos(j,1);
		for (i = 0; i < LCD_line_length; i++){
			LCD_write_data(menu_effect_select_header[j-1][i]);
		}
	}

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

void menu_settings_setup(){
	unsigned int i;
	LCD_cursor_pos(1,1);
	for (i = 0; i < LCD_line_length; i++){
		LCD_write_data(menu_settings_header[0][i]);
	}

	return;
}

