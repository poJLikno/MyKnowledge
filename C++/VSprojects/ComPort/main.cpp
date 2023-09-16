#include "SerialPort/SerialPort.h"

int main(int argc, const char *argv[])
{
	std::cout << "ComPort - My C++ library\r\nTest\r\n\r\n";
	try
	{
		char symbol = 0;
		char message[1024] = { 0 };

		SerialPort com_port("COM3", 9600UL);
		//com_port.SendData("start", 5ULL);
		std::cout << "== Start ==\r\n";
		while (GetKeyState(VK_ESCAPE) >= 0)
		{
			if (GetKeyState('F') < 0)
			{
				std::cout << "Type message: ";
				std::cin.getline(message, sizeof(message));
				com_port.SendData(message, sizeof(message));
				ZeroMemory(message, sizeof(message));
			}
			if (com_port.RecieveData(&symbol) > 0UL)
			{
				std::cout << symbol;
				symbol = 0;
			}
		}
		std::cout << "=== End ===\r\nExit...\r\n";
	}
	catch (std::runtime_error &e)
	{
		std::cout << "\r\n= = = = =\r\n" << e.what() << "\r\n= = = = =\r\n";
	}

	return 0;
}