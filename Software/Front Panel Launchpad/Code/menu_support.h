/*
 * menu_support.h
 *
 *  Created on: Mar 25, 2017
 *      Author: bigbird42
 */

#ifndef MENU_SUPPORT_H_
#define MENU_SUPPORT_H_

#include <msp430.h>
#include <stdbool.h>
#include "misc.h"
#include "lcd.h"

#define number_of_settings 3 /*number of settings in settings menu*/
#define non_bool_settings 1 /*point in settings menu where settings are not boolean values*/
#define setting_max_value 100 /*highest value a setting can have*/
#define max_effect_presets 10 /*number of presets available to user*/
#define max_effect_types 8 /*number of effect types available to user*/

/*prototypes for functions in menu_support.c*/
unsigned int user_input_decode();
unsigned int port1_statemachine(unsigned int);
unsigned int port2_statemachine(unsigned int, unsigned char);
void wait_for_input();
void effect_select_setup();
void effect_select_write_effects();
void settings_setup();

/*declarations for variables defined in menu.c*/
struct effect_data{
	const int preset_number;
	char name[LCD_line_length];
	char name_short[6];
	int effect_value[max_effect_types][4];
};

volatile bool port1_interrupt;
volatile bool port2_interrupt;
volatile bool new_user_input;
static unsigned int current_preset;

/*external varaibles*/
extern unsigned char port1_state;
extern unsigned char port2_state;
extern unsigned char port1_mask;
extern unsigned char port2_mask;

#endif /* MENU_SUPPORT_H_ */
