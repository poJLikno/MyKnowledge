#include "UDPSockets.h"

UDPClient::UDPClient(const char *ip, uint16_t port)
{
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
		throw std::runtime_error("Can't start Winsock! " + std::to_string(wsOk) + '\n');

	client = socket(AF_INET, SOCK_DGRAM, 0);

	serverInfo = {};
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_port = htons(port);
	inet_pton(AF_INET, ip, &serverInfo.sin_addr);

	serverLength = sizeof(serverInfo);
}

UDPClient::~UDPClient()
{
	closesocket(client);
	WSACleanup();
}

void UDPClient::CloseSocket()
{
	closesocket(client);
	WSACleanup();
}

void UDPClient::SendData(const char *data, size_t size)
{
	int sendOk = sendto(client, data, size, 0, (sockaddr *)&serverInfo, sizeof(serverInfo));
	if (sendOk == SOCKET_ERROR)
		throw std::runtime_error("That didn't work! " + std::to_string(WSAGetLastError()) + '\n');
}

int UDPClient::ReceiveData(char *buffer, size_t size)
{
	int bytesIn = recvfrom(client, buffer, size, 0, (sockaddr *)&serverInfo, &serverLength);
	if (bytesIn == SOCKET_ERROR)
		throw std::runtime_error("Error receiving from client " + std::to_string(WSAGetLastError()) + '\n');

	return bytesIn;
}