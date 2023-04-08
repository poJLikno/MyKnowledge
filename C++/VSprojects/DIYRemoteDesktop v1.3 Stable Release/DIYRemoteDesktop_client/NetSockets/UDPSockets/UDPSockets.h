#ifndef UDP_SOCKETS_H
#define UDP_SOCKETS_H

#include "../NetSockets.h"

class UDPSocket
{
public:
	virtual void CloseSocket() = 0;

	virtual void SendData(const char *data, size_t size) = 0;

	virtual int ReceiveData(char *buffer, size_t size) = 0;
};

class UDPServer : UDPSocket
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

	void CloseSocket() override final;

	void GetClientIP(char *buffer, size_t size);

	void SendData(const char *data, size_t size) override final;

	int ReceiveData(char *buffer, size_t size) override final;
};

class UDPClient : UDPSocket
{
private:
	SOCKET client;
	sockaddr_in serverInfo;
	int serverLength;

public:
	UDPClient(const char *ip, uint16_t port);

	~UDPClient();

	void CloseSocket() override final;

	void SendData(const char *data, size_t size) override final;

	int ReceiveData(char *buffer, size_t size) override final;
};

#endif