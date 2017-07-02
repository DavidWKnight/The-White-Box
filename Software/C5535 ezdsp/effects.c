/*
 * effects.c
 *
 *  Created on: Jun 11, 2017
 *      Author: David Knight
 */

#include "effects.h"

#define TMS320C5535

static int circ_buffer_sig[circ_buffer_size];
static unsigned long buffer_sig_it = circ_buffer_size - 1;
static const float __PI__ = 3.14159;
static const float max_sample_size = 32767;

int effects_init(){
    unsigned long i;
    for(i = 0; i < circ_buffer_size; i++){
        circ_buffer_sig[i] = 0;
    }
    return 0;
}

void delay_sample(int sample){
    if(buffer_sig_it == 0){
        buffer_sig_it = circ_buffer_size - 1;
    }
    else{
        buffer_sig_it--;
    }
    circ_buffer_sig[buffer_sig_it] = sample;
}


int delay(int sample, unsigned long frames){
    unsigned long delay_ref = buffer_sig_it + frames;
    if (delay_ref >= circ_buffer_size){
        delay_ref -= circ_buffer_size;
    }

    return (sample + circ_buffer_sig[delay_ref])/2;
}

int flange(int sample, float speed, unsigned int depth){
    static unsigned long ref = 0;
    unsigned long time_delay = SAMPLES_PER_SECOND/200;
    float omega, t, A, temp, delay_wo_depth;

    omega = (2*__PI__*speed);
    t = ((float)ref/SAMPLES_PER_SECOND);
    A = depth*6;
    delay_wo_depth = sin(omega*t);
    temp = abs(A*delay_wo_depth);

    //unsigned float temp = depth*3*sin( (2*__PI__*speed) * ((float)ref/SAMPLES_PER_SECOND) );
    time_delay += (unsigned long)temp;
    ref++;
    if(ref > (SAMPLES_PER_SECOND/4)/speed){
        ref = 1;
    }
    return delay(sample, time_delay);
}

int tanh_OD(int sample_in, float gain, float mix){
    float sample = ((float)(sample_in)/max_sample_size);
    float clean_sample = sample;
    sample = (exp(sample*gain) - exp(sample*-gain)) / (exp(sample*gain) + exp(sample*-gain));

    sample *= 1-mix;
    sample += clean_sample*mix;

    return (int)(sample*max_sample_size*.05);
}
