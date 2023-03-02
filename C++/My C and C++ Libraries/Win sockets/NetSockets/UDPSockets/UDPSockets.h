#ifndef UDP_SOCKETS_H
#define UDP_SOCKETS_H

#include "../NetSockets.h"

class UDPServer
{
private:
	SOCKET server;
	sockaddr_in serverInfo;
	sockaddr_in clientInfo;
	int clientLength;

public:
	UDPServer(uint16_t port);

	~UDPServer();

	void BindSocket();

	void CloseSocket();

	void GetClientIP(char *buffer, size_t size);

	void SendData(const char *data, size_t size);

	void ReceiveData(char *buffer, size_t size);
};

class UDPClient
{
private:
	SOCKET client;
	sockaddr_in serverInfo;
	int serverLength;

public:
	UDPClient(const char *ip, uint16_t port);

	~UDPClient();

	void CloseSocket();

	void SendData(const char *data, size_t size);

	void ReceiveData(char *buffer, size_t size);
};

#endif