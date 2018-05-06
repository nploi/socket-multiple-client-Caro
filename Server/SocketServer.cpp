#include "SocketServer.h"


SocketServer::SocketServer()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		throw ERROR;
		WSACleanup();
		return;
	}
	//init socket
	listenSock = socket(AF_INET, SOCK_STREAM, 0/*IPPROTO_TCP*/);
	
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

	// Bind
	if (bind(listenSock, (sockaddr *)&serverAddr, sizeof(serverAddr)))
	{
		throw ERROR;
		return;
	}

	// listen
	if (listen(listenSock, MAX_CLIENT)){
		throw ERROR;
		return;
	}



}

/*
 Destructor
*/
SocketServer::~SocketServer()
{
	closesocket(listenSock);
	WSACleanup();
}
