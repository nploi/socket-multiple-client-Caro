#include "Player.h"


Player::Player()
{
}

string Player::receive() {
	char *str = new char[MAX_TEXT];
	int check = recv(socket, str, MAX_TEXT, 0);
	if (check == SOCKET_ERROR) {
		return string();
	}
	return string(str);
}

bool Player::sendAText(string text) {
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

Player::~Player()
{
}
