#define F_CPU 16000000UL

#include <math.h>
#include <avr/io.h>
#include <util/delay.h>
//#include <avr/interrupt.h>

#include "MAX6675/MAX6675.h"
#include "USART/USART.h"


/*ISR(USART_RX_vect)
{
	USART_TransmitByte(UDR0);
}*/

void float_to_string(char *buffer, uint8_t buffer_size, float num);

int main(void)
{
	//sei();
	USART_Init(207);
    MAX6675_Init();
    while (1) 
    {
		if (MAX6675_ReadTemp())
		{
			float temp = MAX6675_GetTemp();
			char buffer[16] = { 0 };
			float_to_string(buffer, sizeof(buffer), temp);
			USART_SendData(buffer, sizeof(buffer));
			// \r\n
			USART_TransmitByte(0x0d);
			USART_TransmitByte(0x0a);
		}
		else
		{
			USART_SendData("None", 4ULL);
			// \r\n
			USART_TransmitByte(0x0d);
			USART_TransmitByte(0x0a);
		}
		_delay_ms(1000.0);
    }
}

void float_to_string(char *buffer, uint8_t buffer_size, float num)
{	
	snprintf(buffer, buffer_size, "%d", (int)num);
	num -= (float)trunc(num);
	if (num != 0.f)
	{
		if (num < 0.f) num *= -1.f;
		while (num - (float)trunc(num) != 0.f) num *= 10.f;
		snprintf(buffer, buffer_size, "%s.%d", buffer, (int)num);
	}
}