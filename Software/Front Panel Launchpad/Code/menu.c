/*
 * menu.c
 *
 *  Created on: Feb 24, 2017
 *      Author: bigbird42
 */


#include "menu.h"


unsigned char encoder_state = 0x00;
unsigned char encoder_rotation = 0x00;
unsigned char encoder_state_machine[13][4] = {
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

const char menu_effect_select_header[2][20] = {" Effect Select Menu ","   Effect Select    "};
const char menu_settings_header[1][20] = {"   Settings Menu    "};
const char effects_available[8][20] = {"        Wah         ", "      Ring Mod      ", "       Phaser       ",
		"     Drive/Fuzz     ", "       Flange       ", "    Pitch Shift     ", "       Delay        ", "    Trem/Vibrato    "};

struct current_effect{
	int preset_number;
	char name[20];
	int effect_value[8][4];
};

/*takes debounced inputs and runs them through state machines*/ //This will be refactored soon to allow holding down a button for something to happen
unsigned int user_input_decode(){
	switch(port_state_last){
		/*port 1*/
		case 0x0001:
			return port1_statemachine(0x0001);
		case 0x0002:
			return port1_statemachine(0x0002);
		case 0x0004:
			return port1_statemachine(0x0004);
		case 0x0008:
			return port1_statemachine(0x0008);
		case 0x0010:
			return port1_statemachine(0x0010);
		case 0x0020:
			return port1_statemachine(0x0020);
		case 0x0040:
			return port1_statemachine(0x0040);
		case 0x0080:
			return port1_statemachine(0x0080);
		/*port 2*/
		case 0x0100:
			return port2_statemachine(0x01, 0x01);
		case 0x0200:
			return port2_statemachine(0x02, 0x01);
		case 0x0400:
			return port2_statemachine(0x04, 0x02);
		case 0x0800:
			return port2_statemachine(0x08, 0x02);
		case 0x1000:
			return port2_statemachine(0x10, 0x03);
		case 0x2000:
			return port2_statemachine(0x20, 0x03);
		case 0x4000:
			return port2_statemachine(0x40, 0x04);
		case 0x8000:
			return port2_statemachine(0x80, 0x04);
		/*port 1 or no action*/
		default:
			port_state_last = 0x0000;
		}

	return 0;
}

/*state machine for pushbutton*/
unsigned int port1_statemachine(unsigned int pin){
	__disable_interrupt();
	port_state_last &= ~pin;
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
/*state machine for rotary encoders with A on even numbered pins and B on odd numbered pins*/ //This will be rafactored to simplify some parts
unsigned int port2_statemachine(unsigned int pin, unsigned char encoder_number){
	__disable_interrupt();
	port_state_last &= ~pin << 8;
	unsigned char encoder_mask = (0x03 << (encoder_number - 1));//used to mask values from other encoders

	unsigned char encoder_state_temp;
	encoder_state_temp = encoder_state_machine[(encoder_state & encoder_mask) << (encoder_rotation & encoder_mask)][((encoder_state & encoder_mask) ^ pin) >> (encoder_number-1 >> 2)];

	if (encoder_state_temp == 0x00){//invalid state, reset everything
		encoder_state &= ~encoder_mask;
		encoder_rotation &= ~encoder_mask;
		P2IES |= encoder_mask;
		port2_mask |= encoder_mask;
		__enable_interrupt();
		return 0;
	}
	else if (encoder_state_temp == 0xF0 || encoder_state_temp == 0x0F){//encoder turned successfully, reset everything
		encoder_state &= ~encoder_mask;
		encoder_rotation &= ~encoder_mask;
		port2_mask |= encoder_mask;
		P2IES |= encoder_mask;
		P2IFG &= ~pin;
		__enable_interrupt();
		return (pin << 8);
	}
	else if (encoder_state_temp == 0x08){//when the encoder turns CW
		encoder_rotation |= (0x02 << ((encoder_number - 1) << 1));//put a 1 in the leading bit for the respective encoder_rotation place, ie encoder_number = 2 -> encoder_rotation = 0x00001000
	}

	if ((encoder_rotation & encoder_mask) == 0){//encoder state needs to be shifted right if moving CW
		encoder_state = (encoder_state_temp << ((encoder_number - 1) << 1));//depends on encoder; << 2 for enc2, << 4 for enc 3
	}
	else{
		encoder_state = (encoder_state_temp << ((encoder_number - 1) << 1)) >> 2;
	}

	port2_mask ^= pin;
	P2IES ^= pin;
	P2IFG &= ~pin;
	__enable_interrupt();
	return 0x00;
}

/*waits for user input on port 1 or port 2; goes into low power mode if there is no input*/
void wait_for_input(){
	bool waiting = true;
	while(1){
		waiting = true;
		if(port1_check){
			waiting = false;
			TA0CTL |= MC_1;//start timer for debouncing
			port1_check = false;
		}
		if (port2_check){
			waiting = false;
			TA1CTL |= MC_1;//start timer for debouncing
			port2_check = false;
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
	unsigned int i;
	unsigned int j;
	for (i = 0, j = 2; j > 0; j--){
		LCD_cursor_pos(j,1);
		for (i = 0; i < LCD_line_length; i++){
			LCD_write_data(menu_effect_select_header[j-1][i]);
		}
	}

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
