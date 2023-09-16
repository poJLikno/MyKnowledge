#include "SerialPort/SerialPort.h"

int main(int argc, const char *argv[])
{
	std::cout << "ComPort - My C++ library\r\nTest\r\n\r\n";
	try
	{
		char symbol = 0;

		SerialPort com_port("COM3", 9600UL);
		//com_port.SendData("start", 5ULL);
		std::cout << "== Start ==\r\n";
		while (com_port.RecieveData(&symbol) > 0UL && GetKeyState(VK_ESCAPE) >= 0)
		{
			std::cout << symbol;
			symbol = 0;
		}
		std::cout << "=== End ===\r\nExit...\r\n";
	}
	catch (std::runtime_error &e)
	{
		std::cout << "\r\n= = = = =\r\n" << e.what() << "\r\n= = = = =\r\n";
	}

	return 0;
}