#include <iostream>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#pragma warning(disable : 4996)

using namespace std;

int main()//            CLIENT
{
    WSADATA wsData;
    WSAStartup(MAKEWORD(2,2), &wsData);
    //char ip[20] = "";

    //cout << "Client ready\nEnter server's ip: ";
    //cin >> ip;
    //cout << "" << endl;

    SOCKET netSocket;
    netSocket = socket(AF_INET, SOCK_STREAM, 0);

    //HOSTENT *host = gethostbyname(ip);

    struct sockaddr_in netInfo;
    ZeroMemory(&netInfo, sizeof(netInfo));
    netInfo.sin_family = AF_INET;
    netInfo.sin_port = htons(2000);
	netInfo.sin_addr.S_un.S_addr = inet_addr(ip);
    //memcpy(&netInfo.sin_addr.S_un.S_addr, host -> h_addr_list[0], sizeof(netInfo.sin_addr.S_un.S_addr));

    connect(netSocket, (struct sockaddr *)&netInfo, sizeof(netInfo));

	int mas[1] = {1};
	send(netSocket, (const char*)mas, sizeof(mas), 0);
	
	closesocket(netSocket);


    return 0;
}
