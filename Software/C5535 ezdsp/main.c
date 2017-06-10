/*
 * main.c
 */

#include "registers.h"
#include "peripherals.h"
#include "aic3204.h"
#define SAMPLES_PER_SECOND 48000

void main(void) {
	PCGCR1 = 0x0000;
	PCGCR2 = 0x0000;
	EBSR |= PPMODE1;

	PLL_init();
	I2C_init();
	aic3204_init();

	asm(" bclr XF");

	unsigned long int i;
	int left_input, right_input, left_output, right_output;
	for (i = 0; i < SAMPLES_PER_SECOND*600L; i++){
		aic3204_read(&left_input, &right_input);

		left_output = left_input;
		right_output = right_input;

		aic3204_write(left_output, right_output);
	}
	aic3204_disable();

	return;
}



