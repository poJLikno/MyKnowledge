#ifndef LED_STRIP_H
#define LED_STRIP_H

#include <stdio.h>

#define PORTx PORTB
#define M_DAT 0b00000010

typedef struct
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} RGB;

void setLedStripColor(RGB color, uint8_t led_count);

void ledStripOFF(uint8_t led_count);

// Additional functions
void setLedStripColorsArray(RGB *colors_array, uint8_t *counts_array, uint8_t elements_count, uint8_t leds_per_tick, uint8_t led_count);

void setLedStripArray(RGB *colors_array, uint16_t size, uint8_t led_count);

#endif