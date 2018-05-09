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
	string receive();

	/*
	@describe
		Send a text to client
	@param
		text: string
	@return
		if success will return true
		else return false
	*/
	bool sendAText(string text);

	~Player();
public:
	SOCKET socket;
	string name;
	pthread_t thread;
	char chessman;
};
