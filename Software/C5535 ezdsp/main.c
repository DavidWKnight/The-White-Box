/*
 * main.c
 * Author: David Knight
 */

#define TMS320C5535

#include "registers.h"
#include "effects.h"
#include "peripherals.h"
#include "aic3204.h"
#include "fixed.h"

void main(void) {
    PCGCR1 = 0x0000;
    PCGCR2 = 0x0000;
    EBSR |= PPMODE1;

    //PLL_init();
    effects_init();
    I2C_init();
    aic3204_init();
    asm(" bclr XF");

    static int left_input, right_input;
    static fixed left_output = 0, right_output = 0;

    while(1){

        aic3204_read(&left_input, &right_input);
        delay_sample(left_input);
        /*
        left_output = left_input;
        right_output = right_input;
        //left_output = delay(left_output, SAMPLES_PER_SECOND/2, 1);
        //left_output = .5*tanh_OD(left_output, 50, .5);
        //left_output = low_pass(left_output);
        aic3204_write(left_output/4, right_output/4);
        */
        left_output = iTofix(left_input);
        left_output = fixflange(left_output, 0x10000, 50);

        aic3204_write(fixToi(left_output>>2), 0);

    }

}
