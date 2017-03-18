/*
 * misc.h
 *
 *  Created on: Dec 27, 2016
 *      Author: bigbird42
 */

#ifndef MISC_H_
#define MISC_H_

#include <msp430.h>
#include <stdbool.h>
#include <string.h>
#include "lcd.h"

#define P1_max_checks 6
//#define P2_max_checks 6//I need to know how long is takes to switch
#define P2_max_checks 3

void init_ports();
void init_misc();
void port1_debounce();
void port2_debounce();
void lcd_write_effects(unsigned int);
void delay_ms(unsigned int);

unsigned char port1_state;
unsigned char port2_state;
unsigned char port1_mask;
unsigned char port2_mask;
extern volatile bool new_user_input;
extern unsigned int effects[4];

#endif /* MISC_H_ */
