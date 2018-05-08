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
	void addPlayer(Player player);

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
	static void *startMatch(void *param);

public:
	vector<Player> players;
	pthread_t thread;
};