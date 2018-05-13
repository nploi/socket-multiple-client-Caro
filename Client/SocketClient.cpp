/*
* @author
* - Nguyen Nhut Minh
* - 1660345
* @email
* - nhutminh12a21998@gmail.com
*/


#include "SocketClient.h"
SocketClient::SocketClient()
{
}

SOCKET SocketClient::getClient()
{
	return this->server;
}

void SocketClient::InitClient(const char* server_addr, int port)
{
	WSADATA WSAData;
	sockaddr_in addr;

	WSAStartup(MAKEWORD(2, 0), &WSAData);
	WORD wVersion = MAKEWORD(2, 2);
	this->server = socket(AF_INET, SOCK_STREAM, 0);

	addr.sin_addr.s_addr = inet_addr(server_addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	connect(this->server, (sockaddr *)&addr, sizeof(addr));
}

void SocketClient::registerUsername(string username)
{
	//char buff[BUFF_SIZE];
	//memset(&buff, 0, sizeof(buff));
	//buff = username.c_str();
	username[username.size()] = NULL;
	send(this->server, username.c_str(), username.size(), 0);
}

void SocketClient::Send(char buff[])
{
	send(this->server, buff, sizeof(buff), 0);
}

string SocketClient::Receive()
{
	char buff[BUFF_SIZE];
	memset(&buff, 0, sizeof(buff));
	recv(this->server, buff, sizeof(buff), 0);
	return string(buff);
}

unsigned _stdcall SocketClient::SendThread(void* param)
{
	Map game;
	SocketClient client;
	client.server = (SOCKET)param;
	int x, y;
	char buff[2];
	while (1)
	{
		memset(&buff, 0, sizeof(buff));
		do
		{
			cout << "\nSelect cell (x, y): " << endl;
			cin >> x >> y;
			if (!game.isValid(x, y))
				cout << "Cell error!!!. Please select cell again." << endl;
		} while (!game.isValid(x, y));
		memset(&buff, 0, sizeof(buff));
		buff[0] = (char)x;
		buff[1] = (char)y;
		client.Send(buff);
	}
	system("pause");
	closesocket(client.server);
	WSACleanup();
	return 0;
}

SocketClient::~SocketClient()
{
	closesocket(this->server);
	WSACleanup();
}