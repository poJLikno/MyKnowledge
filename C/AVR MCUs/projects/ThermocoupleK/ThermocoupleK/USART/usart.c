#include "USART.h"
#include <avr/io.h>

//USART_TransmitByte(0x0d);
//USART_TransmitByte(0x0a);

void USART_Init(uint16_t speed)
{
	UBRR0H = (uint8_t)(speed>>8);
	UBRR0L = (uint8_t)speed;
	
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);
	UCSR0A |= (1<<U2X0);
	UCSR0C = (1<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00);
}

void USART_TransmitByte(uint8_t data)
{
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

void USART_SendData(char *data, size_t data_size)
{
	size_t i = 0;
	for (i = 0; i < data_size; i++) USART_TransmitByte(data[i]);
}