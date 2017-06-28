/*
 * menu_effect_select.h
 *
 *  Created on: Jun 11, 2017
 *      Author: bigbird42
 */

#ifndef MENU_EFFECT_SELECT_H_
#define MENU_EFFECT_SELECT_H_

#include "peripherals.h"
#include "lcd.h"

char menu_effect_select();
static void effect_select_setup();
static void effect_select_update_active();
static void effect_select_write_effects();
void menu_settings();
static void settings_setup();
static void settings_write_settings(unsigned char);

extern unsigned int current_preset;
extern unsigned int active_preset;
extern struct effect_data all_effect_data[max_effect_presets];

#endif /* MENU_EFFECT_SELECT_H_ */
