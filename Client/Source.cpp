/*
* @author
* - Nguyen Nhut Minh
* - 1660345
* @email
* - nhutminh12a21998@gmail.com
*/


#include "SocketClient.h"
#include <sstream>

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

	//gui username
	string username;
	do
	{
		cout << "Username is: ";
		getline(cin, username);
		//gui username cho server
		client.registerUsername(username);
		buff = client.Receive();			//nhan lai kq dang ki username(1: thanh cong, 0: Nhap lai)
		
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
			cout << "Username existed. Please register username again!!!" << endl;
		buff.clear();
	} while (1);

	//TODO(FIX)
	
	//_beginthreadex(0, 0, client.SendThread, (void *)client.getClient(), 0, 0);//thread send point
	do
	{
		buff.clear();
		buff = client.Receive();
		int n = (int)buff[0] - 48;
		char client1 = ((n % 2 == 0) ? 'X' : 'O');
		char client2 = (!(n % 2 == 0) ? 'X' : 'O');


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
					cout << "\nSelect cell (x, y): " << endl;
					cin >> x >> y;
					if (!game.isValid(x, y) || !game.isChess(x, y))
						cout << "Cell error!!!. Please select cell again." << endl;
				} while (!game.isValid(x, y) || !game.isChess(x, y));
				memset(&buff, 0, sizeof(point));
				point[0] = (char)(x + 48);
				point[1] = ' ';
				point[2] = (char)(y + 48);
				int check = client.Send(point);

				game.chess(x, y, client1);
				game.display();

				buff.clear();
				buff = client.Receive();
				if (buff.empty()) {
					cout << "Disconnect to server !!\n";
					break;
				}
				std::istringstream in(buff);
				in >> x >> y >> win;
				if (buff == "exit")
				{
					cout << endl << "Congratulate!!! You win" << endl;
					break;
				}
				if (win == 1)
				{
					cout << endl << "You win!!!Congratulation" << endl;
					break;
				}
				else
				{
					if (win == -1)
					{
						cout << endl << "You close!!!" << endl;
						break;
					}
				}
			}
			else
			{
				win = 0;
				buff.clear();
				buff = client.Receive();

				if (buff.empty()) {
					cout << "Disconnect to server !!\n";
					break;
				}

				std::istringstream in(buff);
				in >> x >> y >> win;
				game.chess(x, y, client2);
				game.display();
				if (buff == "exit")
				{
					cout << endl << "Congratulate!!! You win" << endl;
					break;
				}
				if (win == 1)
				{
					cout << endl << "You win!!!Congratulation" << endl;
					break;
				}
				else
				{
					if (win == -1)
					{
						cout << endl << "You close!!!" << endl;
						break;
					}
				}

			}
			n++;
		}
		int valContinue;
		while (1)
		{
			cout << "Do you play continue? ( 1->continue || 0->stop )" << endl;
			cin >> valContinue;
			if (valContinue == 1 || valContinue == 0)
				break;
			cout << "Error!!! Only selected 0 or 1" << endl;
		}
		client.PlayContinue(valContinue);
		if (valContinue == 1)
			cout << "Continue---->" << endl;
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