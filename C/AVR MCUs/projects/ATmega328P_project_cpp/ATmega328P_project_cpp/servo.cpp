#include "servo.h"

servo::servo()
{
	DDRB = (1<<DDB1);
	PORTB = (0<<PORTB1);

	TCCR1A = (1<<COM1A1) | (1<<WGM11);
	TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10);
	TCNT1 = 0;
	ICR1 = 4999;
	OCR1A = 120;
}

void servo::rotate(unsigned short angle)
{
	if (angle >= 0 && angle <= 180)
	{
		unsigned short val = round(2.666666666666667 * (float)angle + 120.f);
		OCR1A = val;
	}
}