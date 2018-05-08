/*
* This's socket and some structures for project
* @author
* - Nguyen Phuc Loi
* - 1660321
* @email
* - nploi1998@gmail.com
*/

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
		string text;
		int ret;
		Match* newMatch = (Match*)param;
		Player target;
		int n = 0;
		text = "0";
		newMatch->players[0].sendAText(text);
		text = "1";
		newMatch->players[1].sendAText(text);

		while (true) {
			text.clear();
			if (n % 2 == 0){
				while (text.empty()){
					text = newMatch->players[0].receive();
				}
				cout << newMatch->players[0].name << " sent " << text << endl;
				target = newMatch->players[1];
			}
			else {
				while (text.empty()){
					text = newMatch->players[1].receive();
				}
				cout << newMatch->players[1].name << " sent " << text << endl;
				target = newMatch->players[0];
			}
			if (text == "stop")
			{
				break;
			}
			target.sendAText(text);

			n++;
		}
		pthread_cancel(newMatch->thread);
		return NULL;
	}

public:
	vector<Player> players;
	pthread_t thread;
};