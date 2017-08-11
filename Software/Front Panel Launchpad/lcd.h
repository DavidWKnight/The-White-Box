/*
 * lcd.h
 *
 *  Created on: Jun 11, 2017
 *      Author: David Knight
 */

#ifndef LCD_H_
#define LCD_H_

#include <msp430.h>
#include "peripherals.h"

#define LCD_RS BIT7
#define LCD_RW BIT6
#define LCD_E  BIT5
#define LCD_cmd_out P5OUT
#define LCD_data_out P3OUT

void init_LCD();
void LCD_write_data(char);
void LCD_write_cmd(char);
void LCD_cursor_pos(int, int);
void LCD_write_integer(int, int, int,unsigned int);

#endif /* LCD_H_ */
