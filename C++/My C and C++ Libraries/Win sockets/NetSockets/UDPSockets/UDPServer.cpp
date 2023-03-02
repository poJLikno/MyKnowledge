#include "UDPSockets.h"

UDPServer::UDPServer(uint16_t port)
{
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
		throw std::runtime_error("Can't start Winsock! " + wsOk + '\n');

	server = socket(AF_INET, SOCK_DGRAM, 0);

	serverInfo = {};
	serverInfo.sin_addr.S_un.S_addr = ADDR_ANY;
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_port = htons(port);

	clientInfo = {};
	clientLength = sizeof(clientInfo);
}

UDPServer::~UDPServer()
{
	closesocket(server);
	WSACleanup();
}

void UDPServer::BindSocket()
{
	if (bind(server, (sockaddr *)&serverInfo, sizeof(serverInfo)) == SOCKET_ERROR)
		throw std::runtime_error("Can't bind socket! " + std::to_string(WSAGetLastError()) + '\n');
}

void UDPServer::CloseSocket()
{
	closesocket(server);
	WSACleanup();
}

void UDPServer::GetClientIP(char *buffer, size_t size)
{	
	inet_ntop(AF_INET, &clientInfo.sin_addr, buffer, size);
}

void UDPServer::SendData(const char *data, size_t size)
{
	int sendOk = sendto(server, data, size, 0, (sockaddr *)&clientInfo, sizeof(clientInfo));
	if (sendOk == SOCKET_ERROR)
		throw std::runtime_error("That didn't work! " + std::to_string(WSAGetLastError()) + '\n');
}

void UDPServer::ReceiveData(char *buffer, size_t size)
{
	ZeroMemory(&clientInfo, clientLength);
	int bytesIn = recvfrom(server, buffer, size, 0, (sockaddr *)&clientInfo, &clientLength);
	if (bytesIn == SOCKET_ERROR)
		throw std::runtime_error("Error receiving from client " + std::to_string(WSAGetLastError()) + '\n');
}