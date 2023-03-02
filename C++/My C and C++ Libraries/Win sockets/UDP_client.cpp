#include <iostream>
#include <ws2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

int main(int argc, const char *argv[])// Client
{
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
	{
		std::cout << "Can't start Winsock! " << wsOk << '\n';
		return EXIT_SUCCESS;
	}

	SOCKET client = socket(AF_INET, SOCK_DGRAM, 0);
	
	sockaddr_in serverInfo;
	{
		serverInfo.sin_family = AF_INET;
		serverInfo.sin_port = htons(54000);
	}
	inet_pton(AF_INET, "127.0.0.1", &serverInfo.sin_addr); // Convert from string to byte array

	std::string message("Aloha"); // Message!

	int sendOk = sendto(client, message.c_str(), message.size() + 1, 0, (sockaddr *)&serverInfo, sizeof(serverInfo));
	if (sendOk == SOCKET_ERROR)
	{
		std::cout << "That didn't work! " << WSAGetLastError() << '\n';
	}

	/*
	char buf[1024];
	int serverLength = sizeof(serverInfo);
	int bytesIn = recvfrom(client, buf, sizeof(buf), 0, (sockaddr *)&serverInfo, &serverLength);
	if (bytesIn == SOCKET_ERROR)
	{
		std::cout << "Error receiving from client " << WSAGetLastError() << '\n';
		return EXIT_SUCCESS;
	}

	std::cout << buf;
	*/

	closesocket(client);
	WSACleanup();
}