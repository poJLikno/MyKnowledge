#include "DiskpartParser/DiskpartParser.h"
#include <math.h>

int main(int argc, const char *argv[])
{
	try
	{
		DiskpartParser::ParseVolumeList_Volume("log.txt", NULL, 0);
		//float i = 0.123456f;
		//std::cout << i;
	}
	catch (std::runtime_error &e)
	{
		std::cout << "\r\n" << e.what() << "\r\n";
	}

	return 0;
}