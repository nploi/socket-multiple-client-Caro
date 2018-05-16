/*
* @author
* - Nguyen Nhut Minh
* - 1660345
* @email
* - nhutminh12a21998@gmail.com
*/


#include "SocketClient.h"
#include <sstream>

/*
@describe
	find opponent. if exists opponent return n (variable character 0 -> 'O' or 1 -> 'X'), else return -1;
@param
	socket & buff 
@return
	agree: 0 or 1
	not agree: -1
*/
int findPlayer(SocketClient &client, string buff)
{
	int n;
	cout << "Finding player ...\n";
	do {
		buff.clear();
		buff = client.Receive();
		if (buff.empty())
			return -1;
		n = (int)buff[0] - 48;
		if (n == 0 || n == 1)
			break;
	} while (1);
	return n;
}


/*
@describe
	Ask player have play continue or haven't play conntinue. Player seclect 1 to continue or 0 to stop
@param
	socket & value continue
@return
	agree: return 1 if send to server success  
	not agree: return 0 if error
*/
int playContinue(SocketClient &client, int valContinue)
{
	char* val;
	val = new char;
	val[0] = (char)(valContinue + 48);
	return client.Send(val);
}

int main()
{
	SocketClient client;
	string buff;

	//init client
	try
	{
		client.InitClient(SERVER_ADDR, PORT);
	}
	catch (int exception)
	{
		if (exception == ERROR_INIT)
		{
			cout << "ERROR! cannot init client" << endl;
			return 0;
		}
		else
			cout << "Connected to server" << endl;
	}

	//register username
	string username;
	do
	{
		cout << "Username of Player: ";
		getline(cin, username);
		client.registerUsername(username);

		//receive result register username(1: success, 0: error. Do again)
		buff = client.Receive();

		if (buff.empty()){
			cout << "Disconnect to server !!\n";
			return 0;
		}

		if ((int)buff[0] == '1')
		{
			cout << "Register success !!" << endl;
			break;
		}
		else
			cout << "Username existed. Please select username different!!!" << endl;
		buff.clear();
	} while (1);

	//TODO(FIX)

	//_beginthreadex(0, 0, client.SendThread, (void *)client.getClient(), 0, 0);//thread send point


	do
	{
		int n;
		n = findPlayer(client, buff);
		if (n == -1)
		{
			cout << "Disconnect to server... !!!" << endl;
			closesocket(client.getClient());
			WSACleanup();
			system("pause");
		}
		system("cls");
		char chessMan1 = ((n % 2 == 0) ? 'X' : 'O');
		char chessMan2 = (!(n % 2 == 0) ? 'X' : 'O');

		//communicate between two client
		int x, y;
		char point[2];
		int win;
		Map game;
		game.display();
		while (1)
		{
			if (n % 2 != 0)
			{
				win = 0;
				do
				{
					cout << endl << "Select cell (x, y): " << endl;
					cin >> x >> y;
					if (!game.isValid(x, y) || !game.isChess(x, y))
						cout << "Cell error!!! Please select cell again." << endl;
				} while (!game.isValid(x, y) || !game.isChess(x, y));
				memset(&buff, 0, sizeof(point));
				point[0] = (char)(x + 48);
				point[1] = ' ';
				point[2] = (char)(y + 48);
				int check = client.Send(point);

				game.chess(x, y, chessMan1);
				game.display();

				//receive result win
				buff.clear();
				buff = client.Receive();

				if (buff.empty()) {
					cout << "Disconnect to server... !!!" <<endl;
					break;
				}
				if ("exit" == buff.substr(0, 4)) 
				{
					cout << endl << "Congratulation!!! You win" << endl;
					break;
				}
				std::istringstream in(buff);
				in >> x >> y >> win;
				if (win == 1)
				{
					cout << endl << "You win!!! Congratulation" << endl;
					break;
				}
				else
				{
					if (win == -1)
					{
						cout << endl << "You lost!!!" << endl;
						break;
					}
				}
			}
			else
			{
				//receive point(x, y) from opponent
				cout << endl << "Waiting to session...." << endl;
				win = 0;
				buff.clear();
				buff = client.Receive();

				if (buff.empty()) {
					cout << "Disconnect to server... !!!"<<endl;
					break;
				}

				std::istringstream in(buff);
				in >> x >> y >> win;
				game.chess(x, y, chessMan2);
				game.display();
				if (buff == "exit")
				{
					cout << endl << "Congratulation!!! You win" << endl;
					break;
				}
				if (win == 1)
				{
					cout << endl << "You win!!! Congratulation" << endl;
					break;
				}
				else
				{
					if (win == -1)
					{
						cout << endl << "You lost!!!" << endl;
						break;
					}
				}

			}
			n++;
		}

		//select continue
		int valContinue;
		while (1)
		{
			cout << "Do you want continue? Select 1 to continue or 0 to stop" << endl;
			cin >> valContinue;
			if (valContinue == 1 || valContinue == 0)
				break;
			cout << "Error!!! Only select 0 or 1" << endl;
		}
		playContinue(client, valContinue);
		if (valContinue == 1) {
			cout << "Continue play chess" << endl;
		}
		else
		{
			cout << "Stop!!!" << endl;
			break;
		}
	} while (1);

	closesocket(client.getClient());
	WSACleanup();
	system("pause");
	return 0;
}