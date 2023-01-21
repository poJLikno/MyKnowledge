#include "encoder.h"

unsigned char a, b, lasta;
short con = 0;

void encoder_init(unsigned char p1, unsigned char p2)
{
	a = p1;
	b = p2;
	
	DDRD &= ~((1<<a) | (1<<b));
	PORTD &= ~((1<<a) | (1<<b));
	
	lasta = (PIND & (1<<a)) ? 1 : 0;
}

void encoder_listen()
{
	unsigned char currenta = (PIND & (1<<a)) ? 1 : 0;
	unsigned char currentb = (PIND & (1<<b)) ? 1 : 0;
	if (currenta != lasta)
	{
		if (currentb != currenta) con -= 45;
		else if (currentb == currenta) con += 45;
		
		lasta = currenta;
	}
}