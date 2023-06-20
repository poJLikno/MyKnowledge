#ifndef LED_STRIP_H
#define LED_STRIP_H

#include <stdio.h>

typedef struct
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} RGB;

void ledStripInit(uint8_t led_count);

void ledStripON(RGB color);

void ledStripOFF(void);

void ledStripRainbow(void);

#endif