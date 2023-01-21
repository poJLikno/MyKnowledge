#include "adc.h"

adc::adc()
{
	DDRC &= ~(1<<0);
	PORTC &= ~(1<<0);
	
	ADMUX = 0x00;
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}

unsigned short adc::read()
{
	ADCSRA |= (1<<ADSC);
	while (ADCSRA & (1<<ADSC));
	return (unsigned short)ADC;
}