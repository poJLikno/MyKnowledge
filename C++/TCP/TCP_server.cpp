#include <iostream>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, const char *argv[])//            SERVER
{
    WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
	{
		std::cout << "Can't start Winsock! " << wsOk << '\n';
		return 0;
	}

	SOCKET server = socket(AF_INET, SOCK_STREAM, 0);
	SOCKET client = {};

	sockaddr_in serverInfo = {}, clientInfo = {};
	{
		serverInfo.sin_addr.S_un.S_addr = ADDR_ANY;
		serverInfo.sin_family = AF_INET;
		serverInfo.sin_port = htons(6060);
	}

	int clientLength = sizeof(clientInfo);
	
	if (bind(server, (sockaddr *)&serverInfo, sizeof(serverInfo)) == SOCKET_ERROR)
	{
		std::cout << "Can't bind socket! " << WSAGetLastError() << '\n';
		return 0;
	}
	
	if (listen(server, SOMAXCONN) == SOCKET_ERROR)
	{
		std::cout << "Can't start listening port! " << WSAGetLastError() << '\n';
		return 0;
	}
	
	char buffer[1024] = {};
	
	while (client = accept(server, (sockaddr *)&clientInfo, &clientLength))
	{
		std::cout << "Connection OK!\n";
		
		char clientIp[256] = {};
		inet_ntop(AF_INET, &clientInfo.sin_addr, clientIp, sizeof(clientIp));
		
		while(recv(client, buffer, sizeof(buffer), 0) > 0)
		{
			std::cout << "Message from " << clientIp << ": " << buffer << '\n';
			/*
			int sendOk = send(client, "any message!", 13, 0);
			if (sendOk == SOCKET_ERROR)
			{
				std::cout << "That didn't work! " << WSAGetLastError() << '\n';
			}
			*/
		}
	}
	closesocket(server);
	WSACleanup();

    return 0;
}
