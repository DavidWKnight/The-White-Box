/*
 * effects.h
 *
 *  Created on: Jun 11, 2017
 *      Author: David Knight
 */

#ifndef EFFECTS_H_
#define EFFECTS_H_

#include <stdlib.h>
#include "fixed.h"
#include "FIR_filters_asm.h"

#define circ_buffer_size 39500 //memory corrupted at 39630-39830
#define SAMPLES_PER_SECOND 48000

int effects_init();
void delay_sample(int);
fixed fixdelay(fixed, unsigned long, unsigned int);
fixed fixflange(fixed, fixed, unsigned int);
int vibrato(int, float, unsigned int);
int chorus(int);
int tanh_OD(int, float, float);
int tremolo(int, float, float);
int low_pass(int);

#endif /* EFFECTS_H_ */
