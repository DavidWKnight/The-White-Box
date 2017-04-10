/*
 * menu.h
 *
 *  Created on: Feb 24, 2017
 *      Author: bigbird42
 */

#ifndef MENU_H_
#define MENU_H_

#include <msp430.h>
#include "menu_support.h"

/*prototypes for functions in menu.c*/
char menu_effect_select();
char menu_effect_edit();
void menu_settings();
void menu_effect_name_edit();

unsigned char effects[max_effect_param];

/*external variables*/
extern char menu_settings_values[number_of_settings];
extern struct effect_data all_effect_data;
extern unsigned int current_preset;

#endif /* MENU_H_ */
