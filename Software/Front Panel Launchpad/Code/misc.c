/*
 * misc.c
 *
 *  Created on: Dec 27, 2016
 *      Author: bigbird42
 */

#include "misc.h"

//unsigned int port_state = 0xFFFF;
unsigned char P1_check = 0xFF;
unsigned char P2_check = 0xFF;

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
	P4SEL0 = 0x00;
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
	P8OUT = 0xF;
	P8SEL0 = 0x0;
	P8OUT = 0x0;
}


void init_misc(){
	/*init flags*/
	volatile bool port1_interrupt = false;
	volatile bool port2_interrupt = false;
	volatile bool new_user_input = false;

	/*init other variables*/
	port1_state = 0x00;
	port2_state = 0x00;
	port1_mask = 0xFF;
	port2_mask = 0xFF;

	/*Port 1 debounce routine timer*/
	TA0R = 0x00;//start counter at 0
	TA0CCR0 = 0x3E8;//trigger interrupt every .5ms
	TA0CCTL0 |= CCIE;
	TA0CTL |= TASSEL_2|ID_3|MC_0;//SMCLK, divide clock by 8, stop mode

	/*Port 2 debounce routine timer*/
	TA1R = 0x00;//start counter at 0
	TA1CCR0 = 0x1F4;//trigger interrupt every
	TA1CCTL0 |= CCIE;
	//SMCLK might be 1MHz not 16MHz
	TA1CTL |= TASSEL_2|ID_0|MC_0;//SMCLK, divide clock by 1, stop mode
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
		TA0CTL &= 0xFFCF;
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
		TA1CTL &= 0xFFCF;
	}
}

/*writes a number onto the bottom row of the LCD screen in the pattern < FX1|FX2|FX3|FX4> */
void lcd_write_effects(unsigned int effect_num){
	LCD_cursor_pos(LCD_line_count,(effect_num*(LCD_line_length/4)) + 1);
	unsigned int temp = effects[effect_num];
	unsigned int temp2 = 0;
	const unsigned int remove_zeros[(LCD_line_length/4) - 2] = {999,99,9};
	const unsigned int power_ten[LCD_line_length/4-1] = {1000,100,10,1};
	unsigned int i = 0;

	/*remove leading zeros*/
	for (temp2 = remove_zeros[i]; i < 3; temp2 = remove_zeros[i]){
		if (temp > temp2){
			break;
		}
		else {
			LCD_write_data(' ');
			i++;
		}
	}

	for (temp2 = 0; i < (LCD_line_length/4) - 1; i++){
		temp2 = temp / power_ten[i];
		LCD_write_data(temp2+48);
		temp -= temp2 * power_ten[i];
	}

}

void delay_ms(unsigned int delay){
	for (; delay > 0; delay--){
		__delay_cycles(1000);
	}
}
