#ifndef TCP_SOCKETS_H
#define TCP_SOCKETS_H

#include "../NetSockets.h"

class TCPServer
{
private:
	SOCKET server;
	sockaddr_in serverInfo;
	SOCKET client;
	sockaddr_in clientInfo;
	int clientLength;

public:
	TCPServer(uint16_t port);

	~TCPServer();

	void BindSocket();

	void ListenPort();

	SOCKET AcceptConnection();

	void CloseSocket();

	void GetClientIP(char *buffer, size_t size);

	void SendData(const char *data, size_t size);

	int ReceiveData(char *buffer, size_t size);
};

class TCPClient
{
private:
	SOCKET client;
	sockaddr_in serverInfo;

public:
	TCPClient(const char *ip, uint16_t port);

	~TCPClient();

	void ConnectToServer();

	void CloseSocket();

	void SendData(const char *data, size_t size);

	int ReceiveData(char *buffer, size_t size);
};

#endif