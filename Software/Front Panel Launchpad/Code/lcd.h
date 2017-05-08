/*
 * lcd.h
 *
 *  Created on: Dec 27, 2016
 *      Author: bigbird42
 */

#ifndef LCD_H_
#define LCD_H_

#include <msp430.h>

#define LCD_line_count 4
#define LCD_line_length 20

#define LCD_RS BIT7
#define LCD_RW BIT6
#define LCD_E  BIT5
#define LCD_cmd_out P5OUT
#define LCD_data_out P3OUT

void init_LCD();
void LCD_write_data(char);
void LCD_write_cmd(char);
void LCD_cursor_pos(int, int);

#endif /* LCD_H_ */
