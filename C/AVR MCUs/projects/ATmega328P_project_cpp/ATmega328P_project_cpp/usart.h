#ifndef USART_H_
#define USART_H_


#include "main.h"

void usart_init(unsigned short baud);
void usart_transmit(unsigned char data);
void usart_print(const char* data);
void usart_println(const char* data);


#endif /* USART_H_ */