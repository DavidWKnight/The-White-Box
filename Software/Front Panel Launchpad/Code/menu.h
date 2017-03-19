/*
 * menu.h
 *
 *  Created on: Feb 24, 2017
 *      Author: bigbird42
 */

#ifndef MENU_H_
#define MENU_H_

#include <msp430.h>
#include <string.h>
#include "misc.h"
#include "lcd.h"

unsigned int user_input_decode();
unsigned int port1_statemachine(unsigned int);
unsigned int port2_statemachine(unsigned int, unsigned char);
void wait_for_input();
void menu_effect_select_setup();
void menu_settings_setup();

extern unsigned char port1_state;
extern unsigned char port2_state;
volatile bool port1_interrupt;
volatile bool port2_interrupt;
extern unsigned char port1_mask;
extern unsigned char port2_mask;
volatile bool new_user_input;

#endif /* MENU_H_ */
