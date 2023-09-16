#include "LedStrip.h"

#include "../F_CPU.h"

#include <string.h>
#include <avr/io.h>
#include <util/delay.h>

void setLedStripColorsArray(RGB *colors_array, uint8_t *counts_array, uint8_t elements_count, uint8_t leds_per_tick, uint8_t led_count)
{
	uint8_t ports = PORTx;
	
	RGB save_color = { 0 };
	uint8_t l = 0, j = 0, k = 0, i = 0;
	for (l = 0; l < led_count; l += leds_per_tick)
	{
		for (j = 0; j < elements_count; j++)
		{
			for (k = 0; k < counts_array[j]; k++)
			{
				save_color = colors_array[j];
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
		}
	}
	
	PORTx = ports;
}

void setLedStripArray(RGB *colors_array, uint16_t size, uint8_t led_count)
{
	uint8_t ports = PORTx;
	
	RGB save_color = { 0 };	
	uint8_t l = 0, j = 0, i = 0;
	for (l = 0; l < led_count; l += size / sizeof(RGB))
	{
		for (j = 0; j < size / sizeof(RGB); j++)
		{
			save_color = colors_array[j];
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
	}
	
	PORTx = ports;
}