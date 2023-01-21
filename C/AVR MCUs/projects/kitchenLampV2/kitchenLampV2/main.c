#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "ledStrip/ledStrip.h"

#define SensorPin (1 << 2)
#define StripLength 34

uint8_t flagStripOn;

void onAction(void);

int main(void)
{
	flagStripOn = 0;
	
	DDRB |= (1<<0);
	PORTB &= ~(1 << 0);
	
	_delay_ms(500);
	turnOff(StripLength);
	_delay_ms(500);
    while (1)
	{
		uint8_t SensorActive = ~PINB & SensorPin;
		if (SensorActive)
			onAction();
		_delay_ms(50);
	}
	
	return 0;
}

void onAction(void)
{
	switch (flagStripOn)
	{
		case 0:
			turnOn(StripLength);
			flagStripOn = 1;
			_delay_ms(1000);
			break;
		
		case 1:
			turnOff(StripLength);
			flagStripOn = 0;
			_delay_ms(1000);
			break;
		
		default:
			break;
	}
	while (~PINB & SensorPin);
}