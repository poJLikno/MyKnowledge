#include "usart.h"

void usart_init(unsigned short baud)
{
	unsigned short speed = round((float)F_CPU / (16.f * (float)baud) - 1.f);
	UBRR0H = (unsigned char)(speed>>8);
	UBRR0L = (unsigned char)speed;
	
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
}

void usart_transmit(unsigned char data)
{
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

void usart_print(const char* data)
{
	unsigned short size = 0;
	while (1)
	{
		if (data[size] == '\0') break;
		size++;
	}
	
	for (unsigned short i = 0; i < size; i++)
	{
		usart_transmit(data[i]);
	}
}

void usart_println(const char* data)
{
	unsigned short size = 0;
	while (1)
	{
		if (data[size] == '\0') break;
		size++;
	}
	
	for (unsigned short i = 0; i < size; i++)
	{
		usart_transmit(data[i]);
	}
	usart_transmit(0x0d);
	usart_transmit(0x0a);
}