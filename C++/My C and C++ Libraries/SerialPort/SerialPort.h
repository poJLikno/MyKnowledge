#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include <iostream>
#include <Windows.h>

class SerialPort
{
private:
	HANDLE hSerialPort = nullptr;

public:
	SerialPort(const char *port_name, unsigned long baud_rate);

	~SerialPort();

	DWORD SendData(const char *data, size_t data_size);

	DWORD RecieveData(char *buffer);
};

#endif