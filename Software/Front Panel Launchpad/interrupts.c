/*
 * interrupts.c
 *
 *  Created on: Jun 11, 2017
 *      Author: David Knight
 */

#include "interrupts.h"

/*debounce routine interrupt*/
#pragma vector=TIMER0_A0_VECTOR // call every 1-5ms
__interrupt void TIMER0_A0_ISR(void){
    _BIC_SR(LPM4_EXIT);
    
    char mask, it;
	static signed char integrator_1[8] = {0,0,0,0,0,0,0,0};// carries running average of pin value
    char last_button_value = button_value;
    char pins = buttons_port;
    pins |= 0x01;//launchpad is weird
    
    if(button_value ^ (~pins & 0x00FF)){// if something changed
	    for(mask = 1, it = 0; mask; mask <<= 1, it++){
	    	// check if button is pressed right now
	    	if(pins & mask){
	            integrator_1[it]--;
	            if(integrator_1[it] < integrator_min){
	                button_value &= ~mask;
	                integrator_1[it] = integrator_min;
	            }
	    	}
	    	else{
	            integrator_1[it]++;
	            // check if button moved to new state
	            if(integrator_1[it] >= integrator_max){
	                button_value |= mask;
	                integrator_1[it] = integrator_max;
	            }
	    	}
	    	if(last_button_value != button_value){
	    		port_change = 1;
				TA0CTL &= ~TAIFG;
	    		return;// only one transition per interrupt
	    	}
	    }
	}

    static signed char integrator_2[8] = {0,0,0,0,0,0,0,0};// carries running average of pin value
    char last_encoder_value = encoder_value;
    pins = encoder_port;

    if(encoder_value ^ (~pins & 0x00FF)){// if something changed
        for(mask = 1, it = 0; mask; mask <<= 1, it++){
            // check if button is pressed right now
            if(pins & mask){
                integrator_2[it]--;
                if(integrator_2[it] < integrator_min){
                    encoder_value &= ~mask;
                    integrator_2[it] = integrator_min;
                }
            }
            else{
                integrator_2[it]++;
                // check if button moved to new state
                if(integrator_2[it] > integrator_max){
                    encoder_value |= mask;
                    integrator_2[it] = integrator_max;
                }
            }
            if(last_encoder_value != encoder_value){
                port_change = 2;
                TA0CTL &= ~TAIFG;
                return;// only one transition per interrupt
            }
        }
    }

    TA0CTL &= ~TAIFG;
}


/*LCD cursor flash interrupt*/
#pragma vector=RTC_VECTOR
__interrupt void RTC_ISR(void){
	_BIC_SR(LPM4_EXIT);
	RTC_interrupt = true;
	RTCIV;
}

