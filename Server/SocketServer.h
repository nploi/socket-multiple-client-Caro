/*
* This's the map for caro
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

#pragma comment(lib, "Ws2_32.lib")

#define PORT 9999
#define SERVER_ADDR "127.0.0.1"
#define MAX_CLIENT 100
#define ERROR 1001
#define HASHTABLE map<string, bool>


using namespace std;

HASHTABLE hash;

struct player{
	SOCKET socket;
	char name[50];
};

struct match{
	player player01, player02;
	pthread_t thread;
};

class SocketServer
{
public:
	SocketServer();
	~SocketServer();
private:
	struct sockaddr_in serverAddr;
	SOCKET listenSock;
};

