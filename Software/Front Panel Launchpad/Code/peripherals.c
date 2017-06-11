/*
 * peripherals.c
 *
 *  Created on: Jun 11, 2017
 *      Author: bigbird42
 */

#include "peripherals.h"

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

//unsigned int port_state = 0xFFFF;
unsigned char P1_check = 0xFF;
unsigned char P2_check = 0xFF;
unsigned char port1_state = 0x00;
unsigned char port2_state = 0x00;
unsigned char port1_mask = 0xFF;
unsigned char port2_mask = 0xFF;
volatile bool new_user_input = false;

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

void init_ports(){
	/*Port 1*/
	P1DIR = 0x00;
	P1REN = 0xFF;
	P1SEL0 = 0x00;
	P1OUT = 0xFF; //Pull up resistors
	P1IE  = 0xFF; //Interrupts on all ports
	P1IES = 0xFF; //Interrupt on high to low transition
	P1IFG = 0x00;

	/*Port 2*/
	P2DIR = 0x00;
	P2REN = 0xFF;
	P2SEL0 = 0x00;
	P2OUT = 0xFF; //Pull up resistors
	P2IE  = 0xFF; //Interrupts on all ports
	P2IES = 0xFF; //Interrupt on high to low transition
	P2IFG = 0x00;

	/*Port 3*/
	P3DIR = 0xFF;
	P3SEL0 = 0x00;
	P3OUT = 0x00;

	/*Port 4*/
	P4DIR = 0xFF;
	P4SEL0 = 0x01;
	P4OUT = 0x00;

	/*Port 5*/
	P5DIR = 0xFF;
	P5SEL0 = 0x00;
	P5OUT = 0x00;

	/*Port 6*/
	P6DIR = 0xFF;
	P6SEL0 = 0x00;
	P6OUT = 0x00;

	/*Port 7*/
	P7DIR = 0xFF;
	P7SEL0 = 0x00;
	P7OUT = 0x00;

	/*Port 8*/
	P8DIR = 0xF;
	P8SEL0 = 0xF;
	P8OUT = 0x0;
}


void init_misc(){
	/*init flags*/
	port1_interrupt = false;
	port2_interrupt = false;
	debounce = false;
	new_user_input = false;
	RTC_interrupt = false;

	/*init other variables*/
	current_preset = 0;
	active_preset = 0;

	/*FRAM write protection*/
	SYSCFG0 &= ~DFWP;
	SYSCFG0 &= ~PFWP;

	/*Debounce timer, TA0*/
	TA0R = 0x00;
	TA0CCR0 = 0xFA;
	TA0CCTL0 &= !CCIE;
	TA0CTL |= (TASSEL_2 + ID_1 + MC_1);

	/*Brightness control, TA1*/
    TA1CCR0 = 1000;
    //LED Brightness
    TA1CCTL2 |= (OUTMOD_7);
    TA1CCR2 = menu_settings_values[setting_LED_brightness] * 10;
    //LCD Brightness
    TA1CCTL1 |= (OUTMOD_7);
    TA1CCR1 = menu_settings_values[setting_LCD_brightness] * 10;

    TA1CTL |= (TASSEL_2 + ID_2 + MC_1);
    TA1CTL |= TACLR;

	/*RTC counter*/
	RTCIV;
	RTCCTL &= ~RTCIE;
	RTCCTL |= (RTCSS_3);
	RTCMOD = 0x1000;
	RTCCTL |= RTCSR;
}

/*debounces pushbutton interrupts on port 1*/
void port1_debounce(){
	static int i = 0;
	char temp = P1IN;
	temp ^= port1_mask;
	P1_check = (P1_check & temp);
	i++;
	if (i >= P1_max_checks){
		i = 0;

		P1_check &= 0xFE;//This is because pin 1 is always low in the launchpad; change on prototype board

		if (P1_check > 0){
			port1_state |= P1_check;
			new_user_input = true;
		}
		P1_check = 0xFF;
		port1_interrupt = false;
		TA0CCTL0 &= ~CCIE;
	}
}

/*debounces rotary encoder interrupts on port 2*/
void port2_debounce(){
	static int i = 0;
	char temp = P2IN;
	temp ^= port2_mask;
	P2_check = (P2_check & temp);
	i++;
	if (i >= P2_max_checks){
		i = 0;
		if (P2_check > 0){
			port2_state |= P2_check;
			new_user_input = true;
		}

		P2_check = 0xFF;
		port2_interrupt = false;
		TA0CCTL0 &= ~CCIE;
	}
}

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
		if(debounce){
			waiting = false;
			TA0CCTL0 |= CCIE;
			debounce = false;
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

void delay_ms(unsigned int delay){
	for (; delay > 0; delay--){
		__delay_cycles(1000);
	}
}

void delay_us(unsigned int delay){
	for (; delay > 0; delay--){
		__delay_cycles(1);
	}
}
