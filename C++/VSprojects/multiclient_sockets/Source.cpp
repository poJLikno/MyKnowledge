#include <iostream>
#include <winsock2.h>
#include <Windows.h>

#pragma comment(lib, "ws2_32.lib")

#pragma warning(disable : 4996)

using namespace std;

int main()//            SERVER
{
    WSADATA wsData;
    WSAStartup(MAKEWORD(2, 2), &wsData);

    cout << "Server ready" << endl;
    system("ipconfig");

    SOCKET servSocket;
    servSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servInfo;
    memset(&servInfo, 0, sizeof(servInfo));
    servInfo.sin_family = AF_INET;
    servInfo.sin_port = htons(2000);

    char answer = NULL;
    cout << "S or C: ";
    cin >> answer;

    if (answer == 'S')
    {
        bind(servSocket, (struct sockaddr*)&servInfo, sizeof(servInfo));
        listen(servSocket, 10);

        int buf[1];
        memset(buf, 0, sizeof(buf));

        SOCKET clientSocket;
        while (clientSocket = accept(servSocket, NULL, NULL))
        {
            cout << "Connect OK" << endl;

            while (recv(clientSocket, (char*)buf, sizeof(buf), 0) > 0)
            {
                cout << "Enter message" << endl;
            }
        }

        closesocket(servSocket);
    }
    else if (answer == 'C')
    {
        char* ip = new char[21];
        cout << "Enter the ip: ";
        cin >> ip;

        HOSTENT* host = gethostbyname(ip);
        memcpy(&servInfo.sin_addr.S_un.S_addr, host->h_addr_list[0], sizeof(servInfo.sin_addr.S_un.S_addr));

        connect(servSocket, (struct sockaddr*)&servInfo, sizeof(servInfo));

        int mas[1] = { 1 };
        send(servSocket, (const char*)mas, sizeof(mas), 0);

        delete[] ip;

        closesocket(servSocket);
    }


    return 0;
}
