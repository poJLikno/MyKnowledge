#include "LedStrip.h"

#include "../F_CPU.h"

#include <avr/io.h>
#include <util/delay.h>

void setLedStripColor(RGB color, uint8_t led_count)
{
	uint8_t ports = PORTB;
	RGB save_color = { 0 };
	
	uint8_t l = 0, i = 0;
	for (l = 0; l < led_count; l++)
	{
		save_color = color;
		// Green byte
		for (i = 128; i > 0; i /=2)
		{
			if (save_color.g >= i)
			{
				PORTB = 2;
				_delay_us(0.7375);
				PORTB = 0;
				_delay_us(0.3875);
				
				save_color.g -= i;
			}
			else
			{
				PORTB = 2;
				_delay_us(0.3375);
				PORTB = 0;
				_delay_us(0.7875);
			}
		}
		// Red byte
		for (i = 128; i > 0; i /=2)
		{
			if (save_color.r >= i)
			{
				PORTB = 2;
				_delay_us(0.7375);
				PORTB = 0;
				_delay_us(0.3875);
				
				save_color.r -= i;
			}
			else
			{
				PORTB = 2;
				_delay_us(0.3375);
				PORTB = 0;
				_delay_us(0.7875);
			}
		}
		// Blue byte
		for (i = 128; i > 0; i /=2)
		{
			if (save_color.b >= i)
			{
				PORTB = 2;
				_delay_us(0.7375);
				PORTB = 0;
				_delay_us(0.3875);
				
				save_color.b -= i;
			}
			else
			{
				PORTB = 2;
				_delay_us(0.3375);
				PORTB = 0;
				_delay_us(0.7875);
			}
		}
	}
	PORTB = ports;
}

void ledStripOFF(uint8_t led_count)
{
	uint8_t ports = PORTB;
	
	uint16_t i = 0;
	for (i = 0; i < led_count * 24; i++)
	{
		PORTB = 2;
		_delay_us(0.3375);
		PORTB = 0;
		_delay_us(0.7875);
	}
	PORTB = ports;
}