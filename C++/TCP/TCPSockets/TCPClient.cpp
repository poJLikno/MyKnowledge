#include "TCPSockets.h"

TCPClient::TCPClient(const char *ip, uint16_t port)
{
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
		throw std::runtime_error("Can't start Winsock! " + std::to_string(wsOk) + '\n');

	client = socket(AF_INET, SOCK_STREAM, 0);

	serverInfo = {};
	{
		serverInfo.sin_addr.S_un.S_addr = ADDR_ANY;
		serverInfo.sin_family = AF_INET;
		serverInfo.sin_port = htons(port);
	}
	inet_pton(AF_INET, ip, &serverInfo.sin_addr);
}

TCPClient::~TCPClient()
{
	closesocket(client);
	WSACleanup();
}

void TCPClient::ConnectToServer()
{
	if (connect(client, (sockaddr *)&serverInfo, sizeof(serverInfo)) == SOCKET_ERROR)
		throw std::runtime_error("Can't connect to server! " + std::to_string(WSAGetLastError()) + '\n');
}

void TCPClient::CloseSocket()
{
	closesocket(client);
	WSACleanup();
}

void TCPClient::SendData(const char *data, size_t size)
{
	int sendOk = send(client, data, size, 0);
	if (sendOk == SOCKET_ERROR)
		throw std::runtime_error("That didn't work! " + std::to_string(WSAGetLastError()) + '\n');
}

int TCPClient::ReceiveData(char *buffer, size_t size)
{
	int bytesIn = recv(client, buffer, size, 0);
	if (bytesIn == SOCKET_ERROR)
		throw std::runtime_error("Error receiving from client " + std::to_string(WSAGetLastError()) + '\n');

	return bytesIn;
}