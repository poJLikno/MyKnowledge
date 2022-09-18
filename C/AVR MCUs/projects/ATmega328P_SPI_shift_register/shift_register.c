#include "shift_register.h"

void set_bits(unsigned char bits)
{
	spi(bits);
	PORTB |= (1<<2);
	//delay_us(5);
	PORTB &= ~(1<<2);
}