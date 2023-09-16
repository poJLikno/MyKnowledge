#include "MAX6675.h"
#include <avr/io.h>

uint16_t buffer;

void MAX6675_Init(void)
{
	DDRx |= ((1<<M_CLK) | (1<<M_CS));
	PORTx |= (1<<M_CS);// | (1<<M_DAT));
}

uint8_t MAX6675_ReadTemp(void)
{
	uint8_t result = 0;
	uint16_t data = 0;
	
	PORTx &= ~(1<<M_CS);
	for (int i = 0; i < 16; i++) {
		PORTx |= (1<<M_CLK);
		data <<= 1;
		if (PINx & (1<<M_DAT)) data |= 1;
		PORTx &= ~(1<<M_CLK);
	}
	PORTx |= (1<<M_CS);
	if ((data & 0b100) || (data == 0xFFFF)) {}
	else
	{
		buffer = data >> 3;
		result = 1;
	}
	
	return result;
}

float MAX6675_GetTemp(void)
{
	return (float)buffer / 4.f;
}