#include "SerialPort.h"

SerialPort::SerialPort(const char* sPortName)
{
    SerialPort::hSerial = CreateFile(sPortName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (hSerial == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
        {
            cout << "serial port does not exist.\n";
        }
        cout << "some other error occurred.\n";
    }

    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams))
    {
        cout << "getting state error\n";
    }
    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams))
    {
        cout << "error setting serial port state\n";
    }
}

void SerialPort::print(const char* data)
{
    unsigned short lenght = 0;
    while (data[lenght] != '\0')
    {
        lenght++;
    }
    lenght++;

    unsigned short size = sizeof(data) * lenght;
    DWORD counter = 0;

    cout << data << endl;
    cout << size << endl;
    cout << size / 8 << endl;
    WriteFile(SerialPort::hSerial, data, size, &counter, NULL);
}

void SerialPort::read()
{
    DWORD size = 0;
    char data = 0;
    while (true)
    {
        bool res = ReadFile(SerialPort::hSerial, &data, 1, &size, 0);
        if (size > 0) cout << data;
    }
}

SerialPort::~SerialPort(){}