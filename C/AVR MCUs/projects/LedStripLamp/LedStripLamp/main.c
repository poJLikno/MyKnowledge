#include "F_CPU.h"
#include <util/delay.h>

#include "AVRPins/AVRPins.h"
#include "LedStrip/LedStrip.h"

int main(void)
{
	// Led strip settings
	uint8_t led_count = 34;
	RGB led_strip_color = { 255, 155, 155 };
		
	uint8_t flag = 0;
		
	// Configurate pins
	pinMode(B, 0, INPUT);
	pinMode(B, 1, OUTPUT);
	_delay_ms(250);
	
	ledStripInit(led_count);
	_delay_ms(250);
	
	ledStripRainbow();
	_delay_ms(5000);
	
	ledStripOFF();
	_delay_ms(250);
		
    while (1) 
    {
		if (!digitalRead(B, 0))
		{
			switch (flag)
			{
				case 0:
					flag = 1;
					ledStripON(led_strip_color);
					break;
				
				case 1:
					flag = 0;
					ledStripOFF();
					break;
				
				default:
					break;
			}
			_delay_ms(500);
			while (!digitalRead(B, 0));
			_delay_ms(500);
		}
    }
}

