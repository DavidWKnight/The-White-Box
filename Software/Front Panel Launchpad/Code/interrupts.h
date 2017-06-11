/*
 * interrupts.h
 *
 *  Created on: Jun 11, 2017
 *      Author: bigbird42
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include <stdbool.h>
#include <msp430.h>
#include "peripherals.h"

extern volatile bool port1_interrupt;
extern volatile bool port2_interrupt;
extern volatile bool debounce;
extern volatile bool RTC_interrupt;

#endif /* INTERRUPTS_H_ */
