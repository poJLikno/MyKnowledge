#include <iostream>
#include <ws2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

int main(int argc, const char *argv[])
{
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
	{
		std::cout << "Can't start Winsock! " << wsOk << '\n';
		return EXIT_SUCCESS;
	}

	SOCKET server = socket(AF_INET, SOCK_DGRAM, 0);

	sockaddr_in serverInfo = {}, clientInfo = {};
	{
		serverInfo.sin_addr.S_un.S_addr = ADDR_ANY;
		serverInfo.sin_family = AF_INET;
		serverInfo.sin_port = htons(54000);
	}

	int clientLength = sizeof(clientInfo);

	if (bind(server, (sockaddr *)&serverInfo, sizeof(serverInfo)) == SOCKET_ERROR)
	{
		std::cout << "Can't bind socket! " << WSAGetLastError() << '\n';
		return EXIT_SUCCESS;
	}

	std::cout << "Start...\n";

	char buf[1024] = {};

	while (true)
	{

		int bytesIn = recvfrom(server, buf, sizeof(buf), 0, (sockaddr *)&clientInfo, &clientLength);
		if (bytesIn == SOCKET_ERROR)
		{
			std::cout << "Error receiving from client " << WSAGetLastError() << '\n';
			continue;
		}

		char clientIp[256] = {};
		inet_ntop(AF_INET, &clientInfo.sin_addr, clientIp, 256);

		std::cout << "Message recv from " << clientIp << " : " << buf << '\n';

		/*
		std::string message("Loh"); // Message!
		int sendOk = sendto(server, message.c_str(), message.size() + 1, 0, (sockaddr *)&clientInfo, sizeof(clientInfo));
		if (sendOk == SOCKET_ERROR)
		{
			std::cout << "That didn't work! " << WSAGetLastError() << '\n';
		}
		*/

		ZeroMemory(&clientInfo, clientLength);
		ZeroMemory(buf, sizeof(buf));
	}

	closesocket(server);
	WSACleanup();

	return EXIT_SUCCESS;
}