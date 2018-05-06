/*
* This's socket and some structures for project
* @author
* - Nguyen Phuc Loi
* - 1660321
* @email
* - nploi1998@gmail.com
*/

#pragma once
#include <pthread.h>
#include <iostream> 
#include <stdio.h>
#include <WinSock2.h>
#include <map>
#include <string.h>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 5454
#define SERVER_ADDR "127.0.0.1"
#define MAX_CLIENT 100
#define ERROR_INIT 1001


using namespace std;

/*
	Structure of
	include socket and name of client 
*/
struct player {
	SOCKET socket;
	string name;
};

/*
	structure of match
	include player1, player2, and thread
*/
struct match {
	player player01, player02;
	pthread_t thread;
};

class SocketServer {
public:
	SocketServer();
	
	/*
		@param
			NULL
		@return
			SOCKET of server
	*/
	SOCKET getListenSocket();

	/*
		@param
			port: int -> PORT of server
			address: const char* -> Address of server
		@return
			NULL
	*/
	void init(int port, const char *address);
	~SocketServer();
private:
	struct sockaddr_in serverAddr;
	SOCKET listenSock;
};

