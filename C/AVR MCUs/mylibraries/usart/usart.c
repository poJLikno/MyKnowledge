#include "usart.h"

void usart_init(unsigned short speed)
{
	UBRR0H = (unsigned char) (speed>>8);
	UBRR0L = (unsigned char) speed;
	
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);
	UCSR0A |= (1<<U2X0);
	UCSR0C = (1<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00);
}

void usart_transmit(unsigned char data)
{
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

void usart_print(char* data)
{
	int size = 0;
	while (1)
	{
		if (data[size] == '\0') break;
		size++;
	}
	
	for (int i = 0; i < size; i++)
	{
		usart_transmit(data[i]);
	}
}

void usart_println(char* data)
{
	int size = 0;
	while (1)
	{
		if (data[size] == '\0') break;
		size++;
	}
	
	for (int i = 0; i < size; i++)
	{
		usart_transmit(data[i]);
	}
	usart_transmit(0x0d);
	usart_transmit(0x0a);
}