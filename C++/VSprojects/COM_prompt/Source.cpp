#include "Source.h"

int main(int argc, char* argv[])
{
    SerialPort com1("COM1");

    Sleep(100);

    //com1.print("Hello, i'm Roman!");

    //Sleep(1000);

    com1.read();

    return 0;
}