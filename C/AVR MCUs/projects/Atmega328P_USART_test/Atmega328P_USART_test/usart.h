/*
 * usart.h
 *
 * Created: 8/25/2022 1:19:22 PM
 *  Author: poJLikno
 */ 


#ifndef USART_H_
#define USART_H_

#include "main.h"

void usart_init(unsigned short speed);
void usart_transmit(unsigned char data);
void usart_print(char* data);
void usart_println(char* data);

#endif /* USART_H_ */