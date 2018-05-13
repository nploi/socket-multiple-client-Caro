#include "Player.h"


Player::Player()
{
}

string Player::receive() {
	char *str = new char[MAX_TEXT];
	string result;
	int check = recv(socket, str, sizeof(str) - 1, 0);
	for (size_t i = 0; str[i] != NULL; i++) {
		result.push_back(str[i]);
	}
	if (check == SOCKET_ERROR) {
		closesocket(socket);
		return string();
	}
	return result;
}

bool Player::sendAText(string text) {
	int check = send(socket, text.c_str(), sizeof(text.c_str()), 0);

	if (check != SOCKET_ERROR) {
		return 1;
	}
	closesocket(socket);
	return 0;
}

Player::~Player()
{
}
