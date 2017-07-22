/*
 * aic3204.h
 *
 *  Created on: Jun 10, 2017
 *      Author: David Knight
 */

#ifndef AIC3204_H_
#define AIC3204_H_

#include "registers.h"
#include "peripherals.h"

#define aic3204_addr 0x18

int aic3204_init();
int aic3204_disable();
int aic3204_rset(unsigned int, unsigned int);
void aic3204_read(int*, int*);
void aic3204_write(int, int);

#endif /* AIC3204_H_ */
