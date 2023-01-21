/*
 * pwm.c
 *
 * Created: 8/27/2022 3:53:34 PM
 *  Author: poJLikno
 */ 

#include "pwm.h"

void pwm_init()
{
	TCCR1A = (1<<WGM11) | (1<<COM1A1);
	TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10);
	ICR1 = 4999;
	OCR1A = 0;//size;
	DDRB |= (1<<PORTB1) | (1<<PORTB2);
	PORTB &= ~((1<<PORTB1) | (1<<PORTB2));
}

void pwm_change(unsigned short angle)
{
	if (angle >= 0 && angle <= 180)
	{
		unsigned short val = round(2.666666666666667 * (float)angle + 120);
		OCR1A = val;
	}
}