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
using namespace std;

#define BUFF_SIZE 256

//Content the names of client
map<string, bool> hash;

/*
	@describe
		Register an account
	@param
		param: void
	@return
		NULL
*/
unsigned _stdcall registerAccount(void *param);

/*
	@describe
		Start new match
	@param
		param: void
	@return
		NULL
*/
void startMatch(void *param);

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

	sockaddr_in clientAddr;
	int clientAddrLen = sizeof(clientAddr);
	player *playerTemp;
	match *matchNew;

	queue<SOCKET> queue;

	while (true) {
		// Init new match
		playerTemp = new player;
		matchNew = new match;
		//new connection
		playerTemp->socket = accept(server.getListenSocket(), (sockaddr *)&clientAddr, &clientAddrLen);
		cout << playerTemp->socket << " connected\n";
		//start thread for user create an account
		_beginthreadex(0, 0, registerAccount, (void*)playerTemp, 0, 0);
		
	}
	//pthread_create(&client[I].ThreadReception, NULL, Reception, NULL)
	return 0;
}


unsigned _stdcall registerAccount(void *param) {
	char buff[50];
	player *client = (player*)param;
	while (true) {
		int check = recv(client->socket, buff, sizeof(buff), 0);
		if (check == SOCKET_ERROR) {
			shutdown(client->socket, 2);
			return NULL;
		}

		string userName(buff);
		string data;
		if ((bool)(::hash.find(userName) == ::hash.end()) == true) {

			data = "1";
			memset(&buff, 0, sizeof(buff));//clear the buffer
			strcpy_s(buff, data.c_str());
			::hash.insert(pair<string, bool>(userName, 1));
			break;
		}
		else{
			data = "0";
		}
		memset(&buff, 0, sizeof(buff));//clear the buffer
		strcpy_s(buff, data.c_str());
		//if register succes, will send for client '1' and '0' is fail
		send(client->socket, buff, strlen(buff), 0);
	}
	client->name = buff;
	cout << "Register success !!\n";
	return NULL;
}

void startMatch(void *param) {
	//TODO(FIX)
	/*char buff[50];
	int ret;
	match* newMatch = (match*)param;
	SOCKET target;
	int n = 0;
	
	buff[0] = '1';
	send(newMatch->player01.socket, buff, strlen(buff), 0);
	buff[0] = '0';
	send(newMatch->player01.socket, buff, strlen(buff), 0);
	while (true){
		if (n % 2 == 0){
			ret = recv(newMatch->player01.socket, buff, BUFF_SIZE, 0);
			cout << twoClient->client01 << " sent " << buff << endl;
			target = twoClient->client02;
		}
		else{
			ret = recv(twoClient->client02, buff, BUFF_SIZE, 0);
			cout << twoClient->client02 << " sent " << buff << endl;
			target = twoClient->client01;
		}
		if (ret == SOCKET_ERROR)
		{
			break;
		}
		send(target, buff, strlen(buff), 0);
		n++;
	}*/
}