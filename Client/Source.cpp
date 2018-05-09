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
			system("pause");
			break;
		}
	} while (1);
	//danh co


	return 0;
}