#ifndef STEP_MOTOR_H_
#define STEP_MOTOR_H_


#include "main.h"

void step_motor_init(unsigned char a, unsigned char b, unsigned char c, unsigned char d);
void step_motor_rotate(short angle);


#endif /* STEP_MOTOR_H_ */