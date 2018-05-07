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
#include <vector>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 5454
#define SERVER_ADDR "127.0.0.1"
#define MAX_CLIENT 100
#define ERROR_INIT 1001


using namespace std;

/*
	Structure of
	include socket and name of client and pthread;
*/
struct player {
	SOCKET socket;
	string name;
	pthread_t thread;
};

/*
	structure of match
	include player1, player2, and thread
*/
class match {
public:
	match(){

	}

	/*
		@describe
			Add player for game
		@param
			player: player
		@return 
			NULL
	*/
	void addPlayer(player player) {
		players.push_back(player);
	}

	~match() {

	}

	/*
	@describe
		Start new match
	@param
		param: void
	@return
		NULL
	*/
	static void *startMatch(void *param) {
		//TODO(FIX)
		char buff[50];
		int ret;
		match* newMatch = (match*)param;
		SOCKET target;
		int n = 0;
		buff[0] = '1';
		send(newMatch->players[0].socket, buff, strlen(buff), 0);
		buff[0] = '0';
		send(newMatch->players[1].socket, buff, strlen(buff), 0);
		while (true){
			if (n % 2 == 0){
				ret = recv(newMatch->players[0].socket, buff, 50, 0);
				cout << newMatch->players[0].socket << " sent " << buff << endl;
				target = newMatch->players[1].socket;
			}
			else{
				ret = recv(newMatch->players[1].socket, buff, 50, 0);
				cout << newMatch->players[1].socket << " sent " << buff << endl;
				target = newMatch->players[0].socket;
			}
			if (ret == SOCKET_ERROR)
			{
				break;
			}
			send(target, buff, strlen(buff), 0);
			n++;
		}
		pthread_cancel(newMatch->thread);
		return NULL;
	}

public:
	vector<player> players;
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

