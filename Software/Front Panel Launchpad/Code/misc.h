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
#include "lcd.h"

#define P1_max_checks 6 /*how many times to check port 1 during debounce*/
#define P2_max_checks 3	/*how many times to check port 2 during debounce*/
#define POUT_LED P3OUT

/*prototypes for functions in misc.c*/
void init_ports();
void init_misc();
void port1_debounce();
void port2_debounce();
void delay_ms(unsigned int);

unsigned char port1_state;
unsigned char port2_state;
unsigned char port1_mask;
unsigned char port2_mask;
static unsigned int current_preset;
static unsigned int active_preset;
extern volatile bool new_user_input;

#endif /* MISC_H_ */
