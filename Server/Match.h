#pragma once

#include "Player.h"
#include <vector>
using namespace std;
/*
structure of match
include player1, player2, and thread
*/
class Match {
public:
	Match(){

	}

	/*
	@describe
	Add player for game
	@param
	player: player
	@return
	NULL
	*/
	void addPlayer(Player player) {
		players.push_back(player);
	}

	~Match() {

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
		Match* newMatch = (Match*)param;
		SOCKET target;
		int n = 0;
		buff[0] = '1';
		send(newMatch->players[0].socket, buff, strlen(buff), 0);
		buff[0] = '0';
		send(newMatch->players[1].socket, buff, strlen(buff), 0);
		while (true) {
			if (n % 2 == 0){
				buff[0] = '-';
				while (buff[0] < '0' || buff[0] > '9') {
					ret = recv(newMatch->players[0].socket, buff, 50, 0);
				}
				cout << newMatch->players[0].socket << " sent " << buff << endl;
				target = newMatch->players[1].socket;
			}
			else {
				buff[0] = '-';
				while (buff[0] < '0' || buff[0] > '9') {
					ret = recv(newMatch->players[1].socket, buff, 50, 0);
				}
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
	vector<Player> players;
	pthread_t thread;
};