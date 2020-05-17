#ifndef __key_H
#define __key_H	

//#include "reg51.h"
sbit key_1 = P1^0;
sbit key_2 = P1^1;
sbit key_3 = P1^2;
sbit key_4 = P1^3;
//sbit key_5 = P0^6;
//sbit key_6 = P0^7;
unsigned char scan_key();

#endif