/*
 * interrupts.h
 *
 *  Created on: Dec 28, 2016
 *      Author: bigbird42
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include <stdbool.h>

extern volatile bool port1_interrupt;
extern volatile bool port2_interrupt;
extern volatile bool debounce;
extern volatile bool RTC_interrupt;

#endif /* INTERRUPTS_H_ */
