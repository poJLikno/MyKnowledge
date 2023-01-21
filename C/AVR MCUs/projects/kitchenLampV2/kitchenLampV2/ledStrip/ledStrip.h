#ifndef LED_STRIP_H
#define LED_STRIP_H

#include <avr/io.h>

#define StripPort (1 << 0)

void sendBit0(void);

void sendBit1(void);

void turnOn(unsigned short led_count);

void turnOff(unsigned short led_count);

#endif