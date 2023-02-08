#include <iostream>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#pragma warning(disable : 4996)

using namespace std;

int main()//            SERVER
{
    WSADATA wsData;
    WSAStartup(MAKEWORD(2,2), &wsData);

    //cout << "Server ready" << endl;
    //system("ipconfig");

    SOCKET servSocket;
    servSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servInfo;
    memset(&servInfo, 0, sizeof(servInfo));
    servInfo.sin_family = AF_INET;
    servInfo.sin_port = htons(2000);

    bind(servSocket, (struct sockaddr *)&servInfo, sizeof(servInfo));
    listen(servSocket, 10);

    int buf[1];
    memset(buf, 0, sizeof(buf));

    SOCKET clientSocket;
    while (clientSocket = accept(servSocket, NULL, NULL))
    {
        cout << "Connect OK" << endl;

        while(recv(clientSocket, (char*)buf, sizeof(buf), 0) > 0)
        {
            cout << "Enter message" << endl;
        }
    }
    closesocket(servSocket);


    return 0;
}
