#ifndef AVR_PINS_H
#define AVR_PINS_H

#include <stdio.h>

typedef enum
{
	B
} PinLetters;

typedef enum
{
	INPUT,
	OUTPUT,
	INPUT_PULLUP
} PinModes;

typedef enum
{
	LOW,
	HIGH
} PinStates;

void pinMode(PinLetters pin_letter, uint8_t pin_number, PinModes pin_mode);

void digitalWrite(PinLetters pin_letter, uint8_t pin_number, PinStates pin_state);

uint8_t digitalRead(PinLetters pin_letter, uint8_t pin_number);

#endif