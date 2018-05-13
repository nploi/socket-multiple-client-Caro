/*
* @author
* - Nguyen Nhut Minh
* - 1660345
* @email
* - nhutminh12a21998@gmail.com
*/


#include "SocketClient.h"

int main()
{
	SocketClient client;
	string buff;
	char* message;
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

	//Nhan bien danh 'X' or 'O'
	buff.clear();
	buff = client.Receive();
	int n = (int)buff[0] - 48;
	
	int x, y, win;
	char msg[BUFF_SIZE];
	Map game;
	game.display();
	_beginthreadex(0, 0, client.SendThread, (void *)client.getClient(), 0, 0);//thread send point
	while (1)
	{
		buff.clear();
		buff = client.Receive();
		if (buff == "exit")
		{
			cout << "Congratulate!!! You win" << endl;
			system("pause");
			break;
		}
		x = (int)buff[0]-48;//buff[1]=' '
		y = (int)buff[1]-48;
		win = (int)buff[2]-48;
		game.chess(x, y, ((n % 2 == 0) ? 'X' : 'O'));
		game.display();
		if (win != 0)
		{
			cout << "Congratulate!!! You win" << endl;
			system("pause");
			break;
		}
		n++;
	}

	system("pause");
	return 0;
}