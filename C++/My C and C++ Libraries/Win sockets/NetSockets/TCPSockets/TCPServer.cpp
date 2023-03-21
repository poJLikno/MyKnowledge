#include "TCPSockets.h"

TCPServer::TCPServer(uint16_t port)
{
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
		throw std::runtime_error("Can't start Winsock! " + std::to_string(wsOk) + '\n');

	server = socket(AF_INET, SOCK_STREAM, 0);
	client = {};

	serverInfo = {};
	{
		serverInfo.sin_addr.S_un.S_addr = ADDR_ANY;
		serverInfo.sin_family = AF_INET;
		serverInfo.sin_port = htons(port);
	}

	clientInfo = {};
	clientLength = sizeof(clientInfo);
}

TCPServer::~TCPServer()
{
	closesocket(client);
	closesocket(server);
	WSACleanup();
}

void TCPServer::BindSocket()
{
	if (bind(server, (sockaddr *)&serverInfo, sizeof(serverInfo)) == SOCKET_ERROR)
		throw std::runtime_error("Can't bind socket! " + std::to_string(WSAGetLastError()) + '\n');
}

void TCPServer::ListenPort()
{
	if (listen(server, SOMAXCONN) == SOCKET_ERROR)
		throw std::runtime_error("Can't start listening port! " + std::to_string(WSAGetLastError()) + '\n');
}

SOCKET TCPServer::AcceptConnection()
{
	ZeroMemory(&clientInfo, clientLength);
	client = accept(server, (sockaddr *)&clientInfo, &clientLength);

	return client;
}

void TCPServer::CloseSocket()
{
	closesocket(client);
	closesocket(server);
	WSACleanup();
}

void TCPServer::GetClientIP(char *buffer, size_t size)
{
	inet_ntop(AF_INET, &clientInfo.sin_addr, buffer, size);
}

void TCPServer::SendData(const char *data, size_t size)
{
	int sendOk = send(client, data, size, 0);
	if (sendOk == SOCKET_ERROR)
		throw std::runtime_error("That didn't work! " + std::to_string(WSAGetLastError()) + '\n');
}

int TCPServer::ReceiveData(char *buffer, size_t size)
{
	int bytesIn = recv(client, buffer, size, 0);
	if (bytesIn == SOCKET_ERROR)
		throw std::runtime_error("Error receiving from client " + std::to_string(WSAGetLastError()) + '\n');

	return bytesIn;
}