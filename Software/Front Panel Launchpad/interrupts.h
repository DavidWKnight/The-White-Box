/*
 * interrupts.h
 *
 *  Created on: Jun 11, 2017
 *      Author: David Knight
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include <stdbool.h>
#include <msp430.h>
#include "peripherals.h"

#define integrator_max 4
#define integrator_min 0
#define buttons_port P1IN
#define encoder_port P2IN

volatile char button_value;// carries current value of button
volatile char encoder_value;
volatile char port_change;

#endif /* INTERRUPTS_H_ */
