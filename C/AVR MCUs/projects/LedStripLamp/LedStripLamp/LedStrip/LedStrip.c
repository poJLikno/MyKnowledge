#include "LedStrip.h"

#include "../F_CPU.h"

#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>

uint8_t ledCount;

void errorFunc(void);

void sendBit(uint8_t bit);

void setByte(uint8_t simple_color, uint8_t start_index, uint8_t *buffer);

void setLedColor(RGB color, uint8_t *buffer);

void ledStripInit(uint8_t led_count)
{
	ledCount = led_count;
}

void ledStripON(RGB color)
{
	uint8_t *color_buffer = (uint8_t *)malloc((size_t)24);
	if (color_buffer)// color_buffer not NULL
	{
		memset(color_buffer, 0, (size_t)24);
		
		// Set color in buffer
		setLedColor(color, color_buffer);
		
		// Send message
		uint8_t l = 0, i = 0;
		for (l = 0; l < ledCount; l++)
		{
			for (i = 0; i < 24; i++)
			{
				sendBit(color_buffer[i]);
			}
		}
		
		// Clean up
		free(color_buffer);
		color_buffer = NULL;
	}
	else if (!color_buffer) // Error
	{
		errorFunc();
	}	
}

void ledStripOFF(void)
{		
	// Send message
	uint16_t i = 0;
	for (i = 0; i < ledCount * 24; i++)
	{
		sendBit(0);
	}
}

void ledStripRainbow(void)
{
	uint8_t l = 0, i = 0;
	for (l = 0; l < ledCount; l += 7)
	{
		// Red
		for (i = 0; i < 8; i++)
		{
			sendBit(0);
		}
		for (i = 0; i < 8; i++)
		{
			sendBit(1);
		}
		for (i = 0; i < 8; i++)
		{
			sendBit(0);
		}
		
		// Orange
		sendBit(1);
		for (i = 0; i < 7; i++)
		{
			sendBit(0);
		}
		for (i = 0; i < 8; i++)
		{
			sendBit(1);
		}
		for (i = 0; i < 8; i++)
		{
			sendBit(0);
		}
		
		// Yellow
		for (i = 0; i < 8; i++)
		{
			sendBit(1);
		}
		for (i = 0; i < 8; i++)
		{
			sendBit(1);
		}
		for (i = 0; i < 8; i++)
		{
			sendBit(0);
		}
		
		// Green
		for (i = 0; i < 8; i++)
		{
			sendBit(1);
		}
		for (i = 0; i < 8; i++)
		{
			sendBit(0);
		}
		for (i = 0; i < 8; i++)
		{
			sendBit(0);
		}
		
		// Cyan
		for (i = 0; i < 8; i++)
		{
			sendBit(1);
		}
		for (i = 0; i < 8; i++)
		{
			sendBit(0);
		}
		for (i = 0; i < 8; i++)
		{
			sendBit(1);
		}
		
		// Blue
		for (i = 0; i < 8; i++)
		{
			sendBit(0);
		}
		for (i = 0; i < 8; i++)
		{
			sendBit(0);
		}
		for (i = 0; i < 8; i++)
		{
			sendBit(1);
		}
		
		// Purple
		for (i = 0; i < 8; i++)
		{
			sendBit(0);
		}
		sendBit(1);
		for (i = 0; i < 7; i++)
		{
			sendBit(0);
		}
		for (i = 0; i < 8; i++)
		{
			sendBit(1);
		}
	}
}

void setLedColor(RGB color, uint8_t *buffer)
{
	setByte(color.g, 0, buffer);
	setByte(color.r, 8, buffer);
	setByte(color.b, 16, buffer);
}

void setByte(uint8_t simple_color, uint8_t start_index, uint8_t *buffer)
{
	uint8_t i = start_index + 7;
	while (simple_color != 1 && simple_color > 0)
	{
		buffer[i] = simple_color % 2;
		simple_color /= 2;
		i--;
	}
	buffer[i] = simple_color;
}

void sendBit(uint8_t bit)
{
	if (!bit)
	{
		PORTB = 2;
		_delay_us(0.3375);
		PORTB = 0;
		_delay_us(0.7875);
	}
	else if (bit)
	{
		PORTB = 2;
		_delay_us(0.7375);
		PORTB = 0;
		_delay_us(0.3875);
	}
}

void errorFunc(void)
{	
	// Blink red led
	uint8_t l = 0, i = 0;
	while (1)
	{
		for (l = 0; l < ledCount; l++)
		{
			for (i = 0; i < 8; i++)
			{
				sendBit(0);
			}
			for (i = 0; i < 8; i++)
			{
				sendBit(1);
			}
			for (i = 0; i < 8; i++)
			{
				sendBit(0);
			}
		}
		_delay_ms(500);
		ledStripOFF();
		_delay_ms(500);
	}
}