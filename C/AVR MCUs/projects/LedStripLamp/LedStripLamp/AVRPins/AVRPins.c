#include "AVRPins.h"

#include <avr/io.h>

void pinMode(PinLetters pin_letter, uint8_t pin_number, PinModes pin_mode)
{
	if (pin_letter == B)
	{
		switch (pin_mode)
		{
			case INPUT:
				DDRB &= ~(1<<pin_number);
				PORTB &= ~(1<<pin_number);
				break;
			
			case OUTPUT:
				DDRB |= (1<<pin_number);
				PORTB &= ~(1<<pin_number);
				break;
			
			case INPUT_PULLUP:
				DDRB &= ~(1<<pin_number);
				PORTB |= (1<<pin_number);
				break;
			
			default:
				break;
		}
	}
}

void digitalWrite(PinLetters pin_letter, uint8_t pin_number, PinStates pin_state)
{
	if (pin_letter == B)
	{
		switch (pin_state)
		{
			case LOW:
				PORTB &= ~(1<<pin_number);
				break;
			
			case HIGH:
				PORTB |= (1<<pin_number);
				break;
			
			default:
				break;
		}
	}
}

uint8_t digitalRead(PinLetters pin_letter, uint8_t pin_number)
{
	if (pin_letter == B)
	{
		return PINB & (1<<pin_number);
	}
	else
	{
		return 0;
	}
}