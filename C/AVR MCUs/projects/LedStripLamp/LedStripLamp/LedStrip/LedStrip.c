#include "LedStrip.h"

#include "../F_CPU.h"

#include <avr/io.h>
#include <util/delay.h>

void setLedStripColor(RGB color, uint8_t led_count)
{
	uint8_t ports = PORTx;
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
				PORTx = M_DAT;
				_delay_us(0.7375);
				PORTx = 0;
				_delay_us(0.3875);
				
				save_color.g -= i;
			}
			else
			{
				PORTx = M_DAT;
				_delay_us(0.3375);
				PORTx = 0;
				_delay_us(0.7875);
			}
		}
		// Red byte
		for (i = 128; i > 0; i /=2)
		{
			if (save_color.r >= i)
			{
				PORTx = M_DAT;
				_delay_us(0.7375);
				PORTx = 0;
				_delay_us(0.3875);
				
				save_color.r -= i;
			}
			else
			{
				PORTx = M_DAT;
				_delay_us(0.3375);
				PORTx = 0;
				_delay_us(0.7875);
			}
		}
		// Blue byte
		for (i = 128; i > 0; i /=2)
		{
			if (save_color.b >= i)
			{
				PORTx = M_DAT;
				_delay_us(0.7375);
				PORTx = 0;
				_delay_us(0.3875);
				
				save_color.b -= i;
			}
			else
			{
				PORTx = M_DAT;
				_delay_us(0.3375);
				PORTx = 0;
				_delay_us(0.7875);
			}
		}
	}
	PORTx = ports;
}

void ledStripOFF(uint8_t led_count)
{
	uint8_t ports = PORTx;
	
	uint16_t i = 0;
	for (i = 0; i < led_count * 24; i++)
	{
		PORTx = M_DAT;
		_delay_us(0.3375);
		PORTx = 0;
		_delay_us(0.7875);
	}
	PORTx = ports;
}