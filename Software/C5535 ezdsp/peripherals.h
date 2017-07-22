/*
 * peripherals.h
 *
 *  Created on: Jun 10, 2017
 *      Author: David Knight
 */

#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

#include "registers.h"

#define i2c_timeout 0x7fff
#define ClOCKS_PER_SAMPLE 2000

int PLL_init();
int I2C_init();
int I2C_write(unsigned int, unsigned short*, unsigned int);
void delay_cycles(unsigned long long);
void delay_us(unsigned long long);

#endif /* PERIPHERALS_H_ */
