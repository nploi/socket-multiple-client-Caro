#include "Player.h"


Player::Player()
{
}

string Player::receive() {
	char *str = new char[MAX_TEXT];
	string result;
	int check = recv(socket, str, sizeof(str), 0);
	int lenght = strlen(str);
	str[lenght] = NULL;
	for (size_t i = 0; str[i] != NULL; i++)
	{
		result.push_back(str[i]);
	}
	if (check == SOCKET_ERROR) {
		return string();
	}
	return result;
}

bool Player::sendAText(string text) {
	int check = send(socket, text.c_str(), sizeof(text.c_str()), 0);

	if (check != SOCKET_ERROR)
	{
		return 1;
	}
	return 0;
}

Player::~Player()
{
}
