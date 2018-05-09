#include "SocketClient.h"
SocketClient::SocketClient()
{
}

SOCKET SocketClient::getClient()
{
	return this->server;
}

void SocketClient::InitClient(const char* server_addr, int port)
{
	WSADATA WSAData;
	sockaddr_in addr;

	WSAStartup(MAKEWORD(2, 0), &WSAData);
	WORD wVersion = MAKEWORD(2, 2);
	this->server = socket(AF_INET, SOCK_STREAM, 0);

	addr.sin_addr.s_addr = inet_addr(server_addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	connect(this->server, (sockaddr *)&addr, sizeof(addr));
}

void SocketClient::registerUsername(string username)
{
	char buff[BUFF_SIZE];
	memset(&buff, 0, sizeof(buff));
	send(this->server, buff, sizeof(buff), 0);
}

void SocketClient::Send(char buff[])
{
	send(this->server, buff, sizeof(buff), 0);
}

void SocketClient::Receive(char buff[])
{
	memset(&buff, 0, sizeof(buff));
	recv(this->server, buff, sizeof(buff), 0);
}

SocketClient::~SocketClient()
{
	closesocket(this->server);
	WSACleanup();
}