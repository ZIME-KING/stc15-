#include "main.h"
void Delay_ms(unsigned int n) {
    unsigned char i, j;
    while(n--) {
        _nop_();
        _nop_();
        _nop_();
        i = 11;
        j = 190;
        do
        {
            while (--j);
        } while (--i);
    }
}

void Delay_us(unsigned int n) {
    while(n--);
}



void Delay_150us(void) {
    unsigned char i, j;

    _nop_();
    _nop_();
    _nop_();
    i = 2;
    j = 153;
    do
    {
        while (--j);
    } while (--i);
}