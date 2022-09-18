#include <iostream>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#pragma warning(disable : 4996)

using namespace std;

int main()//            CLIENT
{
    WSADATA wsData;
    WSAStartup(MAKEWORD(2, 2), &wsData);

    printf("Trying to connect to Vadim's PC(192.168.0.123)...\n");

    SOCKET netSocket;
    netSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in netInfo;
    ZeroMemory(&netInfo, sizeof(netInfo));
    netInfo.sin_family = AF_INET;
    netInfo.sin_port = htons(9070);
    netInfo.sin_addr.S_un.S_addr = inet_addr("192.168.0.123");

    connect(netSocket, (struct sockaddr*)&netInfo, sizeof(netInfo));

    printf("connection successful\n");

    int mas[1] = {0};

    while (1)
    {
        Sleep(1000);
        if (GetKeyState('C') < 0 && GetForegroundWindow() == GetConsoleWindow())
        {
            printf("\"C\" was pressed\n");
            send(netSocket, (const char*)mas, sizeof(mas), 0);
            Sleep(1000);
        }
    }

    closesocket(netSocket);


    return 0;
}
