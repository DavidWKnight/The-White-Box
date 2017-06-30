/*
 * peripherals.c
 *
 *  Created on: Jun 10, 2017
 *      Author: David Knight
 */

#include "peripherals.h"

int PLL_init(){
    CGCR1 |= PLL_PWRDN;
    CGCR1 &= ~PLL_ON;
    CGCR3 = 0x0806;
    CGCR4 &= ~OUTDIVEN;
    CGCR2 |= RDYBYPASS;
    CGCR1 |= (0xBE8);
    CGCR1 |= PLL_ON;
    
    return 0;
}

int I2C_init(){
    ICMDR &= ~0X0010;//RESET
    ICPSC  = 0X14;//config 12MHz clock
    ICCLKL = 0x14;//config clk LOW for 20kHz
    ICCLKH = 0x14;//config clk HIGH for 20kHz

    ICMDR = 0x0420;
    delay_cycles(100);
    return 0;
}

int I2C_write(unsigned int addr, unsigned short *data, unsigned int len){
    long timeout, i;

    ICCNT = len;                    // Set length
    ICSAR = addr;               // Set I2C slave address
    ICMDR = (STT | TRX | MST | IRS | FREE); // Set for Master Write

    delay_cycles(10);

    for(i = 0; i < len; i++){
        ICDXR = data[i];

        timeout = i2c_timeout;
        do{
            if(timeout-- < 0){
                I2C_init();
                return -1;
            }

        }while((ICSTR & ICXRDY) == 0);
    }
    ICMDR |= STP;

    delay_us(100);

    return 0;
}

void delay_cycles(unsigned long long delay){
    unsigned long long i;
    for(i = 0; i < delay; i++){

    }
}

void delay_us(unsigned long long delay){
    delay_cycles(delay*8);
}
