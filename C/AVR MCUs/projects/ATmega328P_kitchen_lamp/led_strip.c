#include "led_strip.h"

void send_bit_0()
{
	PORTD |= (1<<2);
	#asm("nop");
	#asm("nop");
	#asm("nop");
	#asm("nop");
	#asm("nop");
	#asm("nop");
	PORTD &= ~(1<<2);
	#asm("nop");
	#asm("nop");
	#asm("nop");
	#asm("nop");
	#asm("nop");
	#asm("nop");
	#asm("nop");
	#asm("nop");
	#asm("nop");
	#asm("nop");
	#asm("nop");
	#asm("nop");
}

void send_bit_1()
{
	PORTD |= (1<<2);
	#asm("nop");
	#asm("nop");
	#asm("nop");
	#asm("nop");
	#asm("nop");
	#asm("nop");
	#asm("nop");
	#asm("nop");
	#asm("nop");
	#asm("nop");
	#asm("nop");
	PORTD &= ~(1<<2);
	#asm("nop");
	#asm("nop");
	#asm("nop");
	#asm("nop");
	#asm("nop");
	#asm("nop");
	#asm("nop");
}

void turn_on(unsigned short led_count)
{
	unsigned short i;
	for (i = 0; i < (8 * 3 * led_count); i++)
	{
		send_bit_1();
	}
}

void turn_off(unsigned short led_count)
{
	unsigned short i;
	for (i = 0; i < (8 * 3 * led_count); i++)
	{
		send_bit_0();
	}
}