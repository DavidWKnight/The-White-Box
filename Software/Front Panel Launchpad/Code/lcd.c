/*
 * lcd.c
 *
 *  Created on: Dec 27, 2016
 *      Author: bigbird42
 */

#include "lcd.h"

void init_LCD(){
	LCD_cmd_out = 0x00;
	delay_ms(100);
	LCD_write_cmd(0x30);//wake up
	delay_ms(30);
	LCD_write_cmd(0x30);
	delay_ms(10);
	LCD_write_cmd(0x30);
	delay_ms(10);
	LCD_write_cmd(0x38);//8-bit/2-line
	LCD_write_cmd(0x10);//set cursor
	LCD_write_cmd(0x0C);//display on, cursor on
	LCD_write_cmd(0x06);//entry mode

	LCD_write_cmd(0x01);//clear display
	LCD_write_cmd(0x02);//return cursor to home

	return;
}

/*send data to LCD screen*/
void LCD_write_data(char buffer){
	char temp = POUT_LED;
	LCD_data_out = 0x00;
	LCD_data_out |= buffer;
	LCD_cmd_out = 0x00;
	LCD_cmd_out |= LCD_RS;
	LCD_cmd_out &= ~LCD_RW;
	LCD_cmd_out |= LCD_E;
	delay_us(100);
	LCD_cmd_out &= ~LCD_E;
	POUT_LED = temp;
	return;
}

/*send command to LCD screen*/
void LCD_write_cmd(char buffer){
	char temp = POUT_LED;
	LCD_data_out = 0x00;
	LCD_data_out |= buffer;
	LCD_cmd_out = 0x00;
	LCD_cmd_out &= ~LCD_RS;
	LCD_cmd_out &= ~LCD_RW;
	LCD_cmd_out |= LCD_E;
	if ((buffer & 0x80) > 0){
		delay_us(300);
	}
	else{
	delay_ms(2);
	}
	LCD_cmd_out &= ~LCD_E;
	POUT_LED = temp;
	return;
}

/*set cursor position for LCD, 1 indexed*/
void LCD_cursor_pos(int row, int column){
	char pos = 0x80;

	if (row == 4){
		pos += 0x54;
	}
	else if (row == 3){
		pos += 0x14;
	}
	else if (row == 2){
		pos += 0x40;
	}
	else if (row == 1){
	}
	else{
		//return exception or something?
	}
	pos += (column - 1);

	LCD_write_cmd(pos);//write DDRAM address
	return;
}
