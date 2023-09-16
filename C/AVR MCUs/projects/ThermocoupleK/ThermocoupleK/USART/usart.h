#ifndef USART_H
#define USART_H

#include <stdio.h>

void USART_Init(uint16_t speed);

void USART_TransmitByte(uint8_t data);

void USART_SendData(char *data, size_t data_size);

#endif