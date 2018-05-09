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
#include <sstream>
#include "Map.h"

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


	/*
	@describe
		communication between players
	@param
		player01: player
		player02: player
	@return
		2: player01 is out
		1: player01 is win
		0: not win
	*/
	static int communication(Player player01, Player player02, Map &game);

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