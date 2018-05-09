#include "Match.h"

void Match::addPlayer(Player player) {
	players.push_back(player);
}

void *Match::startMatch(void *param) {
	//TODO(FIX)
	string text;
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