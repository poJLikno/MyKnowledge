/*
 * step_motor.h
 *
 * Created: 8/30/2022 1:07:59 AM
 *  Author: poJLikno
 */ 


#ifndef STEP_MOTOR_H_
#define STEP_MOTOR_H_

#include "main.h"

void step_motor_init(unsigned short a, unsigned short b, unsigned short c, unsigned short d);
void step_motor_rotate(short angle);

#endif /* STEP_MOTOR_H_ */