#include "fixed.h"

#define angles_size 8
#define cordic_iterations 5

fixed angles[angles_size] = {
    0xC90F, // fixed binary representation of arctan(1)
    0x76B1, // fixed binary representation of arctan(1/2)
    0x3EB6, // fixed binary representation of arctan(1/4)
    0x1FD5, // fixed binary representation of arctan(1/8)
    0x0FFA, // fixed binary representation of arctan(1/16)
    0x07FF, // fixed binary representation of arctan(1/32)
    0x03FF, // fixed binary representation of arctan(1/64)
    0x01FF  // fixed binary representation of arctan(1/128)
};

fixed kvals[angles_size] = {
    0xB794,
    0xA1E8,
    0x9B13,
    0x9BBC,
    0x9B8E,
    0x9B7B,
    0x9B76,
    0x9B75 
};

int fixToi(fixed num){
    int n = num >> 16;

    if( num & (1<<15) ) { //round up
        n++;
    }
    return n;
}

void cordic(fixed phi, fixed *c, fixed *s){
    int sigma;
    fixed x, y;
    fixed poweroftwo = 0x10000;
    fixed angle = angles[0];
    *c = 0x10000;
    *s = 0;
    if(phi < -fixPI/2 || phi > fixPI/2){
        if(phi < 0){
            cordic(phi + fixPI, c, s);
        }
        else{
            cordic(phi - fixPI, c, s);
        }
        *c *= -1;
        *s *= -1;
        return;
    }

    int i;
    for(i = 0; i < cordic_iterations; i++){
        angle = angles[i];
        if(phi < 0){
            sigma = -1;
        }
        else{
            sigma = 1;
        }
        x = (*c) - sigma * ((*s)>>i);
        y = (*s) + sigma * ((*c)>>i);
        *c = x;
        *s = y;
        phi = phi - sigma*angle;
        poweroftwo = poweroftwo>>1;

    }
    //*c = fixmul(*c, kvals[cordic_iterations]);
    *c = fixmul(*c, kvals[cordic_iterations-1]);
    *s = fixmul(*s, kvals[cordic_iterations-1]);
    return;
}

fixed fixcos(fixed phi){
    fixed c, s;
    cordic(phi, &c, &s);
    return c;
}

fixed fixsin(fixed phi){
    fixed c, s;
    cordic(phi, &c, &s);
    return s;
}

fixed fixtan(fixed phi){
    fixed c, s;
    cordic(phi, &c, &s);
    return fixdiv(s, c);
}

void printfix(fixed num){
    printf("%f", (num>>16) + (num & 0xFFFF)/65536.0 );
    return;
}
