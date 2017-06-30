/*
 * aic3204.c
 *
 *  Created on: Jun 10, 2017
 *      Author: David Knight
 */

#include "aic3204.h"

int aic3204_init(){
    aic3204_rset( 0, 0 );      // Select page 0
    aic3204_rset( 1, 1 );      // Reset codec
    aic3204_rset( 0, 1 );      // Point to page 1
    aic3204_rset( 1, 8 );      // Disable crude AVDD generation from DVDD
    aic3204_rset( 2, 1 );      // Enable Analog Blocks, use LDO power
    aic3204_rset( 0, 0 );
    //PLL and Clocks config and Power Up
    aic3204_rset( 27, 0x1d );  // BCLK and WCLK is set as o/p to AIC3204(Master)
    aic3204_rset( 28, 0x00 );  // Data ofset = 0
    aic3204_rset( 4, 3 );      // PLL setting: PLLCLK <- MCLK, CODEC_CLKIN <-PLL CLK
    aic3204_rset( 6, 7 );      // PLL setting: J=7
    aic3204_rset( 7, 0x06 );   // PLL setting: HI_BYTE(D)
    aic3204_rset( 8, 0x90 );   // PLL setting: LO_BYTE(D)
    aic3204_rset( 30, 0x88 );  // For 32 bit clocks per frame in Master mode ONLY
                               // BCLK=DAC_CLK/N =(12288000/8) = 1.536MHz = 32*fs
    aic3204_rset( 5, 0x91 );   //PLL setting: Power up PLL, P=1 and R=1
    aic3204_rset( 13, 0 );     // Hi_Byte(DOSR) for DOSR = 128 decimal or 0x0080 DAC oversamppling
    aic3204_rset( 14, 0x80 );  // Lo_Byte(DOSR) for DOSR = 128 decimal or 0x0080
    aic3204_rset( 20, 0x80 );  // AOSR for AOSR = 128 decimal or 0x0080 for decimation filters 1 to 6
    aic3204_rset( 11, 0x87 );  // Power up NDAC and set NDAC value to 7
    aic3204_rset( 12, 0x82 );  // Power up MDAC and set MDAC value to 2
    aic3204_rset( 18, 0x87 );  // Power up NADC and set NADC value to 7
    aic3204_rset( 19, 0x82 );  // Power up MADC and set MADC value to 2
    //DAC ROUTING and Power Up 
    aic3204_rset( 0, 1 );      // Select page 1
    aic3204_rset( 0x0c, 8 );   // LDAC AFIR routed to HPL
    aic3204_rset( 0x0d, 8 );   // RDAC AFIR routed to HPR
    aic3204_rset( 0, 0 );      // Select page 0
    aic3204_rset( 64, 2 );     // Left vol=right vol
    aic3204_rset( 65, 0 );     // Left DAC gain to 0dB VOL; Right tracks Left
    aic3204_rset( 63, 0xd4 );  // Power up left,right data paths and set channel
    aic3204_rset( 0, 1 );      // Select page 1
    aic3204_rset( 0x10, 10 );  // Unmute HPL , 10dB gain
    aic3204_rset( 0x11, 10 );  // Unmute HPR , 10dB gain
    aic3204_rset( 9, 0x30 );   // Power up HPL,HPR
    aic3204_rset( 0, 0 );      // Select page 0
    delay_cycles(100);
    //ADC ROUTING and Power Up
    aic3204_rset( 0, 1 );      // Select page 1
    aic3204_rset( 0x34, 0x30 );// STEREO 1 Jack
		                       // IN2_L to LADC_P through 40 kohm
    aic3204_rset( 0x37, 0x30 );// IN2_R to RADC_P through 40 kohmm
    aic3204_rset( 0x36, 3 );   // CM_1 (common mode) to LADC_M through 40 kohm
    aic3204_rset( 0x39, 0xc0 );// CM_1 (common mode) to RADC_M through 40 kohm
    aic3204_rset( 0x3b, 0 );   // MIC_PGA_L unmute
    aic3204_rset( 0x3c, 0 );   // MIC_PGA_R unmute
    aic3204_rset( 0, 0 );      // Select page 0
    aic3204_rset( 0x51, 0xc0 );// Powerup Left and Right ADC
    aic3204_rset( 0x52, 0 );   // Unmute Left and Right ADC
    
    aic3204_rset( 0, 0 );    
    delay_cycles(100);

    //I2S settings
    I2S2SRATE = 0x00;
    I2S2SCTRL = 0x8010; //16-bit word, slave, enable I2C
    I2S2INTMASK = 0x3F; //Enable interrupts

    return 0;
}

int aic3204_disable(){
    aic3204_rset( 1, 1 );
    I2S2SCTRL = 0x00;
    return 0;
}

int aic3204_rset(unsigned int regnum, unsigned int regval){
    unsigned short cmd[2];
    cmd[0] = regnum & 0x007F;
    cmd[1] = regval;

    return I2C_write(aic3204_addr, cmd, 2);
}

void aic3204_read(int *left_input, int *right_input){
    volatile int dummy;
    unsigned int counter1 = 0;

    while(!(I2S2INTFL & (1<<RCVSTFL))){
        counter1++;
    }
    *left_input = I2S2RXLT1;
    dummy = I2S2RXLT0;
    *right_input = I2S2RXRT1;
    dummy = I2S2RXRT0;
}

void aic3204_write(int left_input, int right_input){
    unsigned int counter2 = 0;

    while(!(I2S2INTFL & (1<<XMITSTFL))){
        counter2++;
    }
    I2S2TXLT1 = left_input;
    I2S2TXLT0 = 0;
    I2S2TXRT1 = right_input;
    I2S2TXRT0 = 0;
}
