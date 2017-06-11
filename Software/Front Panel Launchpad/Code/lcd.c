/*
 * lcd.c
 *
 *  Created on: Jun 11, 2017
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
