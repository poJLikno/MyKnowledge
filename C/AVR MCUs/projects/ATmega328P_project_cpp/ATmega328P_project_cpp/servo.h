#ifndef SERVO_H_
#define SERVO_H_


#include "main.h"

class servo
{
public:
	void rotate(unsigned short angle);
	servo();
	~servo();
};


#endif /* SERVO_H_ */