/*
 * peripherals.c
 *
 *  Created on: Jun 11, 2017
 *      Author: David Knight
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
	
	/*Port 2*/
	P2DIR = 0x00;
	P2REN = 0xFF;
	P2SEL0 = 0x00;
	P2OUT = 0xFF; //Pull up resistors

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
	RTC_interrupt = false;

	/*init other variables*/
	current_preset = 0;
	active_preset = 0;

	/*FRAM write protection*/
	SYSCFG0 &= ~DFWP;
	SYSCFG0 &= ~PFWP;

	/*Debounce timer, TA0*/
	TA0R = 0x00;
	TA0CCR0 = debounce_interval;
	TA0CTL |= (TASSEL_2 + ID_1 + MC_1);
	TA0CCTL0 |= CCIE;

	/*Brightness control, TA1*/
    TA1CCR0 = 1000;
    //LED Brightness
    TA1CCTL2 |= (OUTMOD_7);
    TA1CCR2 = settings_values[setting_LED_brightness] * 10;
    //LCD Brightness
    TA1CCTL1 |= (OUTMOD_7);
    TA1CCR1 = settings_values[setting_LCD_brightness] * 10;

    TA1CTL |= (TASSEL_2 + ID_2 + MC_1);
    TA1CTL |= TACLR;

	/*RTC counter*/
	RTCIV;
	RTCCTL &= ~RTCIE;
	RTCCTL |= (RTCSS_3);
	RTCMOD = 0x1000;
	RTCCTL |= RTCSR;
}


/*waits for user input or an interrupt from a peripheral; goes into low power mode if there is no input*/
int wait_for_input(){
	while(1){
		char waiting = 1;
		if(port_change){
			waiting = 0;
			return state_machine();
		}
		if (waiting){
			_BIS_SR(LPM4_bits + GIE);
		}
	}
}

static int state_machine(){
	if(port_change == 1){
	    port_change = 0;
		return button_state_machine();
	}
	else if(port_change == 2){
	    port_change = 0;
		return encoder_state_machine();
	}
	return 0;
}

static int button_state_machine(){
	static char last_state = 0x00;
	char state_change = button_value ^ last_state;
	last_state = button_value;

	if(button_value & state_change){
		// low to high transition
		return ~state_change;
	}
	else{
		// high to low transition
		return state_change;
	}
	/*
	last = 11000100
	bval = 11100000
	chng = 00100000->low to high
	return ~0x0020
	
	last = 11000100
	bval = 10000000
	chng = 01000000->high to low
	return 0x0020
	*/
	
}

static int encoder_state_machine(){
	static char last_state = 0x00;
	static int decoder_state = 0x00;
	char state_change = encoder_value ^ last_state;
	last_state = encoder_value;

	if(state_change & 0x03){
		return encoder_decode(&decoder_state, encoder_value, 0);
	}
	else if(state_change & 0x0C){
		return encoder_decode(&decoder_state, encoder_value, 4);
	}
	else if(state_change & 0x30){
		return encoder_decode(&decoder_state, encoder_value, 8);
	}
	else if(state_change & 0xC0){
		return encoder_decode(&decoder_state, encoder_value, 12);
	}
	
	return 0x00;
}

static int encoder_decode(int *decoder_state, char new_state, char shift){
	int temp = encoder_state_decoder[(*decoder_state>>shift) & 0x0F][(new_state>>(shift>>1)) & 0x03];

	*decoder_state = (temp<<shift);
	if(temp == 0xF0){// CW rotation
		return 0x100<<(shift>>1);
	}
	else if(temp == 0x0F){// CCW rotation
		return 0x200<<(shift>>1);
	}
	
	return 0x00;
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
