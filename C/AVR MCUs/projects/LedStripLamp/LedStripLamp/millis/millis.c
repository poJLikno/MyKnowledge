#include "millis.h"
#include <avr/io.h>
#include <avr/interrupt.h>

uint64_t counter_ms;

ISR(TIMER0_COMPA_vect)
{
	counter_ms++;
	TCNT0 = 0;
}

uint64_t millis(void)
{
	cli();
	uint64_t result = counter_ms;
	sei();
	return result;
}

void timerInit(void)
{
	TCCR0A &= ~((1<<COM0A1) | (1<<COM0A0) | (1<<WGM00) | (1<<WGM01));
	TCCR0B &= ~(1<<WGM02);
	TIMSK |= (1<<OCIE0A);
	sei();
	OCR0A = 249;
	TCCR0B &= ~(1<<CS02);
	TCCR0B |= ((1<<CS00) | (1<<CS01));
	TCNT0 = 0;
}