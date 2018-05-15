/*
* @author
* - Nguyen Phuc Loi
* - 1660321
* @email
* - nploi1998@gmail.com
*/

#include "SocketServer.h"
#include <WS2tcpip.h>
#include <process.h>
#include <queue>
#include "Match.h"
using namespace std;

#define BUFF_SIZE 50

//Content the names of client
map<string, bool> hash;

queue<Player> queuePlayers;


/*
	@describe
		Register an account
	@param
		param: void
	@return
		NULL
*/
void *registerAccount(void *param);


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
int communication(Player player01, Player player02, Map &game);



/*
@describe
	Start new match
@param
	param: void
@return
	NULL
*/
void *startMatch(void *param);



/*
@describe	
	Check player, do you want to play continue
@param
	player: Player
@return
	agree: true
	not agree: false
*/
int playContinue(Player &player);


/*
@describe	
	Check queue of players, if queue have more 2 player connect to add 2 player in game
@param
	player: Player
@return
	agree: true
	not agree: false
*/
void checkQueue() {
	if (queuePlayers.size() >= 2){
		Match *m = new Match;
		m->addPlayer(queuePlayers.front());
		queuePlayers.pop();
		m->addPlayer(queuePlayers.front());
		queuePlayers.pop();
		pthread_create(&m->thread, NULL, startMatch, (void*)m);
	}
}


int main() {
	/*
		If cannot init socket for server, program will throw exception
		*/
	SocketServer server;
	try {
		server.init(PORT, SERVER_ADDR);
	}
	catch (int exception){
		if (exception == ERROR_INIT){
			cout << "Error!! Cannot init server !!";
			system("pause");
			return 0;
		}
	}

	cout << "*** SERVER'S OPENING !! ***\n";

	while (true) {
		// Init new match
		Player *playerTemp = new Player;

		//new connection
		*playerTemp = server.accepted();

		cout << playerTemp->socket << " connected\n";
		//start thread for user create an account
		pthread_create(&playerTemp->thread, NULL, registerAccount, (void*)playerTemp);
	}

	return 0;
}

void *registerAccount(void *param) {
	char buff[50];
	Player *client = (Player*)param;
	string sucess = "0";
	string userName;
	while (true) {

		userName = client->receive();
		if (userName.empty()) {
			closesocket(client->socket);
			return NULL;
		}

		if ((bool)(::hash.find(userName) == ::hash.end()) == true) {

			sucess = "1";
			::memset(&buff, 0, sizeof(buff));//clear the buffer
			strcpy_s(buff, sucess.c_str());
			::hash.insert(pair<string, bool>(userName, 1));
			client->name = userName;
			queuePlayers.push(*client);
			//if register succes, will send for client '1' and '0' is fail
			client->sendAText(sucess);
			checkQueue();
			break;
		}
		else {
			sucess = "0";
			//if register succes, will send for client '1' and '0' is fail
			client->sendAText(sucess);
		}
	}

	::cout << client->name << "'s registered success !!\n";

	pthread_cancel(client->thread);
	
	

	return NULL;
}

void *startMatch(void *param) {
	//TODO(FIX)
	int chessMan = 0;
	Match* newMatch = (Match*)param;
	string text;

	while (true) {
		Player target;
		Map game;
		int n = 0;
		int check = 0;
		newMatch->players[0].chessman = (chessMan % 2 == 0) ? 'X' : 'O';
		newMatch->players[0].sendAText(((chessMan % 2 == 0) ? "0" : "1"));
		newMatch->players[1].chessman = !(chessMan % 2 == 0) ? 'X' : 'O';
		newMatch->players[1].sendAText((!(chessMan % 2 == 0) ? "0" : "1"));

		while (check == 0) {
			if (n % 2 == 0){
				check = communication(newMatch->players[1], newMatch->players[0], game);
			}
			else {
				check = communication(newMatch->players[0], newMatch->players[1], game);
			}
			n++;
		}
		int agree01 = 0, agree02 = 0;
		agree01 = playContinue(newMatch->players[0]);
		agree02 = playContinue(newMatch->players[1]);
		if (agree01 && agree02) {
			continue;
		}
		break;
	}
	pthread_cancel(newMatch->thread);
	return NULL;
}

int communication(Player player01, Player player02, Map &game) {
	string data;
	int x, y, win;
	do {
		data = player01.receive();
		if (data == string()) {
			player02.sendAText("exit");
			cout << player02.name << " did disconnect !!\n";
			return 2;
		}

		istringstream in(data);
		in >> x >> y;

	} while (!game.isValid(x, y));

	cout << player01.name << " sent (" << x << ", " << y << ")" << endl;

	game.chess(x, y, player01.chessman);
	win = game.isWin(x, y, player01.chessman);


	if (win == 1) {
		ostringstream os1;
		os1 << x << " " << y << " 1 ";
		cout << "Sent to " << player02.name << ": " << os1.str() << endl;
		player01.sendAText(os1.str());
		ostringstream os;
		os << x << " " << y << " -1 " << endl;
		cout << "Sent to " << player01.name << ": " << os.str() << endl;
		player02.sendAText(os.str());
		return 1;

	}
	else {
		ostringstream os;
		os << x << " " << y << " 0 ";
		cout << "Sent to " << player02.name << " : " << os.str() << endl;
		player01.sendAText(os.str());
		cout << "Sent to " << player01.name << " : " << os.str() << endl;
		player02.sendAText(os.str());
	}
	return 0;
}

int playContinue(Player &player) {
	string check = player.receive();
	if (check.empty()) {
		return 0;
	}
	if (check[0] == '1') {
		queuePlayers.push(player);
		checkQueue();
		return 1;
	}
	if (check[0] == '0') {
		return 0;
	}
	return false;
}