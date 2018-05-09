#include "Match.h"

void Match::addPlayer(Player player) {
	players.push_back(player);
}

void *Match::startMatch(void *param) {
	//TODO(FIX)
	string text;
	Match* newMatch = (Match*)param;
	Player target;
	Map game;
	int n = 0;
	text = "0";
	newMatch->players[0].chessman = 'X';

	newMatch->players[0].sendAText(text);
	text = "1";
	newMatch->players[1].chessman = 'O';
	newMatch->players[1].sendAText(text);

	while (true) {
		text.clear();
		if (n % 2 == 0){
			newMatch->communication(newMatch->players[0], newMatch->players[1], game);
		}
		else {
			newMatch->communication(newMatch->players[1], newMatch->players[0], game);
		}
		n++;
	}
	pthread_cancel(newMatch->thread);
	return NULL;
}

int Match::communication(Player player01, Player player02, Map &game) {
	string data;
	int x, y, win;
	do {
		data = player01.receive();
		if (data == string()) {
			player02.sendAText("exit");
			return 2;
		}

		istringstream in(data);
		in >> x >> y;
	} while (!game.isValid(x, y));

	cout << player01.name << " sent " << data << endl;

	game.chess(x, y, player01.chessman);
	win = game.isWin(x, y, player01.chessman);
	ostringstream os;
	os << x << " " << y << " " << win;
	player02.sendAText(os.str());
	// not win
	return 0;
}