#ifndef MAX6675_H
#define MAX6675_H

#include <stdio.h>

#define DDRx DDRD
#define PORTx PORTD
#define PINx PIND
#define M_CLK 2
#define M_CS 3
#define M_DAT 4

void MAX6675_Init(void);

uint8_t MAX6675_ReadTemp(void);

float MAX6675_GetTemp(void);

#endif