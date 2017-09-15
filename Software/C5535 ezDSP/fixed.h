#ifndef FIXED_H_
#define FIXED_H_

#include <stdlib.h>
#include <stdio.h>

#define iTofix(n) ((fixed)n)<<16
#define fixTofloat(n) (n>>16) + (n&0xFFFF)/65536.0
#define fixmul(x,y) (x>>8)*(y>>8) // might overflow on DSP
#define fixdiv(x,y) y!=0 ? (x<<8)/(y<<8) : 0
#define fixPI 0x3243F

typedef signed long fixed;
typedef unsigned long ufixed;

int fixToi(fixed);
void cordic(fixed beta, fixed *c, fixed *s);
fixed fixcos(fixed);
fixed fixsin(fixed);
fixed fixtan(fixed);

void printfix(fixed num);

#endif //FIXED_H_
