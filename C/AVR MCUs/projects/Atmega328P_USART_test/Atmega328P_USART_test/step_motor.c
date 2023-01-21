/*
 * step_motor.c
 *
 * Created: 8/30/2022 1:08:20 AM
 *  Author: poJLikno
 */ 

#include "step_motor.h"

unsigned short pins[4];

void step_motor_init(unsigned short a, unsigned short b, unsigned short c, unsigned short d)
{
	pins[0] = a;
	pins[1] = b;
	pins[2] = c;
	pins[3] = d;
	
	DDRD |= pins[0] | pins[1] | pins[2] | pins[3];
	PORTC &= ~(pins[0] | pins[1] | pins[2] | pins[3]);
}

void step_motor_rotate(short angle)
{
	unsigned short steps[4][4] =//0.704
	{	{1, 0, 0, 1},
		{0, 0, 1, 1},
		{0, 1, 1, 0},
		{1, 1, 0, 0}
	};
	
	if (angle > 0)
	{
		unsigned short con = round((float)angle / 0.704);
		for (unsigned short i = 0; i < con; i++)
		{
			for (unsigned short y = 0; y < 4; y++)
			{
				for (unsigned short x = 0; x < 4; x++)
				{
					if (steps[y][x])
					{
						PORTD |= (pins[x]);
					}
					else
					{
						PORTD &= ~(pins[x]);
					}
				}
				_delay_ms(2);
				PORTD &= ~(pins[0] | pins[1] | pins[2] | pins[3]);
			}
		}
	}
	else if (angle < 0)
	{
		unsigned short con = round((float)angle * -1.f / 0.704);
		for (unsigned short i = 0; i < con; i++)
		{
			for (short y = 3; y >= 0; y--)
			{
				for (unsigned short x = 0; x < 4; x++)
				{
					if (steps[y][x])
					{
						PORTD |= (pins[x]);
					}
					else
					{
						PORTD &= ~(pins[x]);
					}
				}
				_delay_ms(2);
				PORTD &= ~(pins[0] | pins[1] | pins[2] | pins[3]);
			}
		}
	}
	else;
}