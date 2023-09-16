#include "SerialPort.h"

SerialPort::SerialPort(const char* port_name, unsigned long baud_rate)
{
    hSerialPort = CreateFile(std::string("\\\\.\\" + std::string(port_name)).c_str(), GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerialPort == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
            throw std::runtime_error("SerialPort -> Serial port does not exist!");
        else
            throw std::runtime_error("SerialPort -> Some other error occurred!");
    }

    DCB dcbSerialParams = { 0 };
    {
        dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
        if (!GetCommState(hSerialPort, &dcbSerialParams))
            throw std::runtime_error("SerialPort -> Getting state error!");
        dcbSerialParams.BaudRate = baud_rate;//CBR_9600;
        dcbSerialParams.ByteSize = 8;
        dcbSerialParams.StopBits = ONESTOPBIT;
        dcbSerialParams.Parity = NOPARITY;
    }

    if (!SetCommState(hSerialPort, &dcbSerialParams))
        throw std::runtime_error("SerialPort -> Error setting serial port state!");
}

SerialPort::~SerialPort()
{
    CloseHandle(hSerialPort);
}

DWORD SerialPort::SendData(const char *data, size_t data_size)
{
    DWORD written_bytes_count = 0;
    if (!WriteFile(hSerialPort, data, (DWORD)data_size, &written_bytes_count/*Can't be NULL in Windows 7*/, NULL))
        throw std::runtime_error("SerialPort -> Can't send data!");
    return written_bytes_count;
}

DWORD SerialPort::RecieveData(char *buffer)
{
    DWORD recieved_bytes_count = 0;
    if (!ReadFile(hSerialPort, buffer, 1, &recieved_bytes_count, NULL))
        throw std::runtime_error("SerialPort -> Can't recieve data!");
    return recieved_bytes_count;
}