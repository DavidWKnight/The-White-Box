/*
 * effects.h
 *
 *  Created on: Jun 11, 2017
 *      Author: David Knight
 */

#ifndef EFFECTS_H_
#define EFFECTS_H_

#include <math.h>

#define circ_buffer_size 39500 //memory corrupted at 39630-39830
#define SAMPLES_PER_SECOND 48000

int effects_init();
void delay_sample(int);
int delay(int, unsigned long);
int flange(int, float, unsigned int);
int tanh_OD(int, float, float);

#endif /* EFFECTS_H_ */
