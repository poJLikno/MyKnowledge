/*
 * adc.c
 *
 * Created: 8/28/2022 12:06:19 AM
 *  Author: poJLikno
 */ 

#include "adc.h"

void adc_init()
{
	DDRC &= ~(1<<PORTC0);
	PORTC &= ~(1<<PORTC0);
	
	ADMUX = 0x00;
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}

unsigned short adc_read()
{
	ADCSRA |= (1<<ADSC);
	while (ADCSRA & (1<<ADSC));
	return (unsigned short)ADC;
}