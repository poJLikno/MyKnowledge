#ifndef TCP_SOCKETS_H
#define TCP_SOCKETS_H

#include "../NetSockets.h"

class TCPSocket
{
public:
	virtual void CloseSocket() = 0;

	virtual void SendData(const char *data, size_t size) = 0;

	virtual int ReceiveData(char *buffer, size_t size) = 0;
};

class TCPServer : TCPSocket
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

	void CloseSocket() override final;

	void GetClientIP(char *buffer, size_t size);

	void SendData(const char *data, size_t size) override final;

	int ReceiveData(char *buffer, size_t size) override final;
};

class TCPClient : TCPSocket
{
private:
	SOCKET client;
	sockaddr_in serverInfo;

public:
	TCPClient(const char *ip, uint16_t port);

	~TCPClient();

	void ConnectToServer();

	void CloseSocket() override final;

	void SendData(const char *data, size_t size) override final;

	int ReceiveData(char *buffer, size_t size) override final;
};

#endif