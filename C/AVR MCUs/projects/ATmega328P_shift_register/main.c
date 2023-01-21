#include "main.h"

unsigned char led, i, del = 255;

void main(void)
{
	DDRB |= (1<<2) | (1<<3) | (1<<5);
	PORTB &= ~((1<<2) | (1<<3) | (1<<5));

	SPCR = (1<<SPE) | (1<<MSTR);
	
	set_bits(0x00);

	while (1)
	{
		for (i = 0; i < 8; i++)
		{
			led <<= 1;
			led++;
			set_bits(led);
			delay_ms(del);
		}
		for (; i > 0; i--)
		{
			led >>= 1;
			set_bits(led);
			delay_ms(del);
		}
    }
}
