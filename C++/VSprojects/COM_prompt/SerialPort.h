#ifndef SERIALPORT_H_
#define SERIALPORT_H_


#include "Source.h"

class SerialPort
{
private:
	HANDLE hSerial;

public:
	void print(const char* data);
	void read();

	SerialPort(const char* sPortName);
	~SerialPort();
};


#endif/*SERIALPORT_H_*/