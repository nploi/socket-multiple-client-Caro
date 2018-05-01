#pragma once
/*
* GAME CARO
* @author
* - Nguyen Phuc Loi
* @email
* - nploi1998@gmail.com
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define WIN 3
#define MAX_SIZE 3

class Map {
public:
	/*
	* init size MAX_SIZE x MAX_SIZE
	*/
	Map(){
		map.resize(MAX_SIZE);
		for (int i = 0; i < map.size(); i++) {
			map[i].resize(MAX_SIZE);
			for (int j = 0; j < map[i].size(); j++){
				map[i][j] = ' ';
			}
		}
	}

	/*
	*  - Display map of CARO
	*   exp: 3-3
	*   -------
	*   | | | |
	*   -------
	*   | | | |
	*   -------
	*   | | | |
	*   -------
	*/
	void display() {
		system("cls");
		cout << "    ";
		for (int i = 0; i < map.size(); i++){
			cout << '-' << i;
		}
		cout << "- Y" << endl;
		cout << "    ";
		for (int i = 0; i <= map.size() * 2; i++){
			cout << '-';
		}
		for (int i = 0; i < map.size(); i++) {
			cout << endl << i << " - |";
			for (int j = 0; j < map[i].size(); j++){
				cout << map[i][j] << '|';
			}
			cout << endl << "    ";
			for (int i = 0; i <= map.size() * 2; i++){
				cout << "-";
			}
		}
		cout << "\nX";
	}

	/*
	*@Params
	*   x: integer
	*   y: integer
	*   c: character
	*   (x,y) is location of map
	*   c: is character of client
	*/
	bool chess(int x, int y, char c){

		if ((x >= map.size() || x < 0 || y >= map[0].size() || y < 0) || map[x][y] != ' '){
			return false;

		}

		map[x][y] = c;
		return true;
	}

	/*
	*@Params
	*   x: integer
	*   y: integer
	*   c: character
	*   (x,y) is location of map
	*   c: is X or O/
	*@return
	* win or not win (true or false)
	*/
	int isWin(int x, int y, char c) {
		int countLess = 0, countGreat = 0;
		// check x to top and (x + 1) to down
		for (int i = x; i >= 0; i--){
			if (map[i][y] != c)
				break;
			countLess++;
		}
		for (int i = x + 1; i < map.size(); i++){
			if (map[i][y] != c)
				break;
			countGreat++;
		}
		if (countLess + countGreat >= WIN)
			return true;

		//check y to left and y + 1 to right
		countLess = 0, countGreat = 0;
		for (int i = y; i >= 0; i--){
			if (map[x][i] != c)
				break;
			countLess++;
		}
		for (int i = y + 1; i < map[0].size(); i++){
			if (map[x][i] != c)
				break;
			countGreat++;
		}
		if (countLess + countGreat >= WIN)
			return true;

		// check diagonal
		countLess = 0, countGreat = 0;
		for (int i = x, j = y; isValid(i, j); i--, j--) {
			if (map[i][j] != c)
				break;
			countGreat++;
		}

		for (int i = x + 1, j = y + 1; isValid(i, j); i++, j++) {
			if (map[i][j] != c)
				break;
			countGreat++;
		}

		if (countLess + countGreat >= WIN)
			return true;


		// check diagonal
		countLess = 0, countGreat = 0;
		for (int i = x, j = y; isValid(i, j); i++, j--) {
			if (map[i][j] != c)
				break;
			countGreat++;
		}

		for (int i = x - 1, j = y + 1; isValid(i, j); i--, j++) {
			if (map[i][j] != c)
				break;
			countGreat++;
		}

		if (countLess + countGreat >= WIN)
			return true;


		return false;
	}


	/*
	*@Params
	*   x: integer
	*   y: integer
	* Check location is valid or invalid
	*@return
	*   (true or false)
	*/
	bool isValid(int x, int y) {
		if (x < 0 || x >= map.size() || y < 0 || y >= map.size())
			return false;
		return true;
	}

	~Map(){
		if (map.empty())
			return;
		for (int i = 0; i < map.size(); i++){
			if (map[i].empty())
				continue;
			map[i].clear();
		}
		map.clear();
	}
private:
	std::vector<vector<char> > map;
};

//int main() {
//
//	/*
//	* Init values
//	*/
//	Map m;
//	int n = 0, isWin = 0;
//
//	/*
//	* Logic games
//	*/
//	while (true){
//		m.display();
//		if (isWin){
//			cout << (((n - 1) % 2 == 0) ? "\n\nPlayer 1 (X)" : "\n\nPlayer 2 (O)") << " is Win !!\n";
//			break;
//		}
//		int x, y, check = 1;
//		do {
//			cout << ((n % 2 == 0) ? "\n\nPlayer 1 (X)" : "\n\nPlayer 2 (O)");
//			cout << "\n(x, y) >>";
//			cin >> x >> y;
//			check = m.chess(x, y, ((n % 2 == 0) ? 'X' : 'O'));
//
//			if (check)
//			{
//				isWin = m.isWin(x, y, ((n % 2 == 0) ? 'X' : 'O'));
//				break;
//			}
//			cout << "you select is wrong!!\nTry again\n";
//		} while (true);
//
//		n++;
//	}
//	system("pause");
//	return 0;
//}