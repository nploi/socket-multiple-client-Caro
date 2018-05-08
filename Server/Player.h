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

#define MAX_TEXT 256

using namespace std;

/*
class of
include socket and name of client and pthread;
*/
class Player {
public:
	Player();

	/*
	@describe
		Receive a text from client
	@param
		NULL
	@return
		if success will return text from client
		else return string empty
	*/
	string receive() {
		char *str = new char[MAX_TEXT];
		int check = recv(socket, str, MAX_TEXT, 0);
		if (check == SOCKET_ERROR) {
			return string();
		}
		return string(str);
	}

	/*
	@describe
		Send a text to client
	@param
		text: string
	@return
		if success will return true
		else return false
	*/
	bool sendAText(string text) {
		char *str = new char[text.size()];
		for (size_t i = 0; i < text.size(); i++)
		{
			str[i] = text[i];
		}
		int check = send(socket, str, MAX_TEXT, 0);

		if (check != SOCKET_ERROR)
		{
			return 1;
		}
		return 0;
	}

	~Player();
public:
	SOCKET socket;
	string name;
	pthread_t thread;
};
