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
	port1_state = 0x00;
	port2_state = 0x00;
	port1_mask = 0xFF;
	port2_mask = 0xFF;
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
    TA1CCTL2 |= (OUTMOD_7);
    TA1CCR2 = 200;
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

/*write the given number to the row and column given, only writes the number of digits given by length*/
void LCD_write_integer(int row, int column, int number,unsigned int length){
    const unsigned int powers_of_ten[5] = {10000, 1000, 100, 10, 1};
    static const unsigned int max_length = 5;
    unsigned int i = max_length - length;
    int num_temp = number;
    char temp = 0;

    LCD_cursor_pos(row, column);

    if(num_temp < 0){
        LCD_write_data('-');
        i++;
        num_temp *= -1;
    }

    for(; (num_temp < powers_of_ten[i]) && (i < (max_length - 1) ); i++){
        LCD_write_data(' ');
    }

    for(; i < (max_length - 1); i++){
        temp = num_temp / powers_of_ten[i];
        LCD_write_data(temp + 48);
        num_temp -= temp * powers_of_ten[i];
    }

    LCD_write_data(num_temp + 48);

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
