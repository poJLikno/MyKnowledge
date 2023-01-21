#include "main.h"

unsigned char flag = 0;

void main(void)
{
	//led_strip
	DDRD |= (1<<2);
	PORTD &= ~(1<<2);
	
	//avoid module
	DDRD &= ~(1<<3);
	PORTD &= ~(1<<3);
	
	//start
	turn_off(34);
	delay_ms(1000);
	
	while (1)
    {
		unsigned char pin = PIND;
		
	    if (~pin & (1<<3))
	    {
			switch (flag)
			{
				case 0:
					flag = 1;
					turn_on(34);
					delay_ms(1000);
					break;
				case 1:
					flag = 0;
					turn_off(34);
					delay_ms(1000);
					break;
				default:
					break;
			}
			while (~PIND & (1<<3));
	    }
		delay_ms(50);
	}
}
