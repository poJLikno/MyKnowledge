#include "ledStrip.h"

void sendBit0(void)
{
	PORTB |= StripPort;
	asm volatile(
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
	);
	PORTB &= ~StripPort;
	asm volatile(
	"nop\n\t"
	"nop\n\t"
	"nop\n\t"
	"nop\n\t"
	"nop\n\t"
	"nop\n\t"
	"nop\n\t"
	"nop\n\t"
	"nop\n\t"
	"nop\n\t"
	);
}

void sendBit1(void)
{
	PORTB |= StripPort;
	asm volatile(
	"nop\n\t"
	"nop\n\t"
	"nop\n\t"
	"nop\n\t"
	"nop\n\t"
	"nop\n\t"
	"nop\n\t"
	"nop\n\t"
	"nop\n\t"
	);
	PORTB &= ~StripPort;
	asm volatile(
	"nop\n\t"
	"nop\n\t"
	"nop\n\t"
	"nop\n\t"
	"nop\n\t"
	);
}

void turnOn(unsigned short led_count)
{
	uint16_t i = 0;
	while (i++ < (8 * 3 * led_count)) sendBit1();
}

void turnOff(unsigned short led_count)
{
	uint16_t i = 0;
	while (i++ < (8 * 3 * led_count)) sendBit0();
}