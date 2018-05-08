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

#define BUFF_SIZE 256

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
			return 0;
		}
	}

	while (true) {
		// Init new match
		Player *playerTemp = new Player;

		//new connection
		*playerTemp = server.accepted();

		cout << playerTemp->socket << " connected\n";
		//start thread for user create an account

		//_beginthreadex(0, 0, registerAccount, (void*)playerTemp, 0, 0);
		pthread_create(&playerTemp->thread, NULL, registerAccount, (void*)playerTemp);
		//registerAccount((void*)playerTemp);
	}

	return 0;
}

//void registerAccount(void *param) {
//	char buff[50];
//	player *client = (player*)param;
//	while (true) {
//		int check = recv(client->socket, buff, sizeof(buff), 0);
//		if (check == SOCKET_ERROR) {
//			shutdown(client->socket, 2);
//			return ;
//		}
//
//		string userName(buff);
//		string data;
//		if ((bool)(::hash.find(userName) == ::hash.end()) == true) {
//
//			data = "1";
//			memset(&buff, 0, sizeof(buff));//clear the buffer
//			strcpy_s(buff, data.c_str());
//			::hash.insert(pair<string, bool>(userName, 1));
//			break;
//		}
//		else{
//			data = "0";
//		}
//		memset(&buff, 0, sizeof(buff));//clear the buffer
//		strcpy_s(buff, data.c_str());
//		//if register succes, will send for client '1' and '0' is fail
//		send(client->socket, buff, strlen(buff), 0);
//	}
//	client->name = buff;
//	queuePlayers.push(*client);
//	cout << "Register success !!\n";
//	return ;
//}


void *registerAccount(void *param) {
	char buff[50];
	Player *client = (Player*)param;
	string sucess = "0";
	string userName;
	while (true) {
		while (userName.empty()){
			userName = client->receive();
			if (userName.empty()) {
				shutdown(client->socket, 2);
				return NULL;
			}
		}

		if ((bool)(::hash.find(userName) == ::hash.end()) == true) {

			sucess = "1";
			::memset(&buff, 0, sizeof(buff));//clear the buffer
			strcpy_s(buff, sucess.c_str());
			::hash.insert(pair<string, bool>(userName, 1));
			client->name = userName;
			queuePlayers.push(*client);
			if (queuePlayers.size() >= 2) {
				Match *m = new Match;
				m->addPlayer(queuePlayers.front());
				queuePlayers.pop();
				m->addPlayer(queuePlayers.front());
				queuePlayers.pop();
				pthread_create(&m->thread, NULL, m->startMatch, (void*)m);
			}
			break;
		}
		else {
			sucess = "0";
			//if register succes, will send for client '1' and '0' is fail
			client->sendAText(sucess);
		}
	}
	//if register succes, will send for client '1' and '0' is fail
	client->sendAText(sucess);

	::cout << "Register success !!\n";
	
	pthread_cancel(client->thread);
	return NULL;
}

