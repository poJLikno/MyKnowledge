#include <iostream>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#pragma warning(disable : 4996)

using namespace std;

int main()//            CLIENT
{
    WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
	{
		std::cout << "Can't start Winsock! " << wsOk << '\n';
		return 0;
	}

	SOCKET client = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in serverInfo = {};
	{
		serverInfo.sin_addr.S_un.S_addr = ADDR_ANY;
		serverInfo.sin_family = AF_INET;
		serverInfo.sin_port = htons(6060);
	}
	inet_pton(AF_INET, "127.0.0.1", &serverInfo.sin_addr);
	
	if (connect(client, (sockaddr *)&serverInfo, sizeof(serverInfo)) == SOCKET_ERROR)
	{
		std::cout << "Can't connect to server! " << WSAGetLastError() + '\n';
	}
	
	int sendOk = send(client, "any message!", 13, 0);
	if (sendOk == SOCKET_ERROR)
	{
		std::cout << "That didn't work! " << WSAGetLastError() << '\n';
	}
	
	/*
	char buffer[1024] = {};
	if (recv(client, buffer, sizeof(buffer), 0) > 0)
	{
		std::cout << "Message: " << buffer << '\n';
	}
	*/
	
	closesocket(client);
	WSACleanup();

    return 0;
}
