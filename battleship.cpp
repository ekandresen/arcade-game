#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>

using namespace std;

const int COLUMNS = 10;

void gameDisplay(int [][COLUMNS], int [][COLUMNS]);

void computerMap(int[][COLUMNS]);

void playerMap(int[][COLUMNS]);

void battleshipGame(int[][COLUMNS], int[][COLUMNS], int[][COLUMNS]);

// Standard battleship rules

int main()
{

	const int ROWS = 10;

	int playerBoard[ROWS][COLUMNS] = { 0 }, computerBoard[ROWS][COLUMNS] = { 0 }, computerDisplay[ROWS][COLUMNS] = { 0 };

	char ch;

	cout << "Welcome to battleship! The goal is to be the first to sink all 5 of your opponent's ships." << endl;

	cout << "You will be playing against a computer, who's goal is the same - Find your ships and sink them." << endl;

	cout << "Press any button to begin.";

	ch = cin.get();

	computerMap(computerBoard);

	playerMap(playerBoard);

	cout << "Great! Now let's get into the game.";

	battleshipGame(playerBoard, computerBoard, computerDisplay);

	return 0;
}

void gameDisplay(int playerBoard[][COLUMNS], int computerDisplay[][COLUMNS])
{

	int i = 0, j = 0, k = 0;

	cout << endl << setw(13) << "PLAYER" << setw(13) << "COMPUTER" << endl;
	cout << setw(11) << " 12345678910" << setw(14) << " 12345678910" << endl;

	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			if (j == 0)
				cout << setw(1) << static_cast<char>(65 + i) << ' ';
			if (playerBoard[i][j] > 2)
				cout << "#";
			else if (playerBoard[i][j] == 0)
				cout << ".";
			else if (playerBoard[i][j] == -1)
				cout << "X";
			else if (playerBoard[i][j] == 1)
				cout << "o";
		}
		cout << "   ";
		for (k = 0; k < 10; k++) {
			if (k == 0)
				cout << setw(1) << static_cast<char>(65 + i) << ' ';
			if (computerDisplay[i][k] == 1)
				cout << "o";
			else if (computerDisplay[i][k] == 0)
				cout << ".";
			else if (computerDisplay[i][k] == -1)
				cout << "X";
		}
		cout << endl;
	}
	cout << "Key:\n# = Player Ship\n. = Unknown/Empty\no = Miss\nX  = Hit" << endl;
}

void computerMap(int computerBoard[][COLUMNS])
{

	int i = 0, startPointX, startPointY, direction, ships = 5, shipSize = 0, shipValue;

	bool left = true, right = true, up = true, down = true;

	while (ships > 0) {

		left = true;
		right = true;
		up = true;
		down = true;

		if (ships == 5) {
			shipValue = 10;
			shipSize = 5;
		}
		else if (ships == 4) {
			shipValue = 9;
			shipSize = 4;
		}
		else if (ships == 3) {
			shipValue = 8;
			shipSize = 3;
		}
		else if (ships == 2) {
			shipValue = 7;
			shipSize = 3;
		}
		else if (ships == 1) {
			shipValue = 6;
			shipSize = 2;
		}

		startPointX = 0 + rand() % 10;

		startPointY = 0 + rand() % 10;

		while (computerBoard[startPointY][startPointX] > 2) {
			startPointX = 0 + rand() % 10;
			startPointY = 0 + rand() % 10;
		}

		computerBoard[startPointY][startPointX] = shipValue;

		for (i = 1; i < shipSize; i++) {
			if (startPointX >= (10 - shipSize)) {
				right = false;
			}
			if (startPointX <= (-1 + shipSize)) {
				left = false;
			}
			if (computerBoard[startPointY][startPointX + i] > 2) {
				right = false;
			}
			if (computerBoard[startPointY][startPointX - i] > 2) {
				left = false;
			}
		}

		for (i = 1; i < shipSize; i++) {
			if (startPointY >= (10 - shipSize)) {
				down = false;
			}
			if (startPointY <= (-1 + shipSize)) {
				up = false;
			}
			if (computerBoard[startPointY + i][startPointX] > 2) {
				down = false;
			}
			if (computerBoard[startPointY - i][startPointX] > 2) {
				up = false;
			}
		}

		direction = 1 + rand() % 4;

		switch (direction)
		{
		case 1:
			if (left == false) {
				direction += 1;
			}
			else {
				right = false;
				up = false;
				down = false;
				break;
			}
		case 2:
			if (right == false) {
				direction += 1;
			}
			else {
				left = false;
				up = false;
				down = false;
				break;
			}
		case 3:
			if (up == false) {
				direction += 1;
			}
			else {
				left = false;
				right = false;
				down = false;
				break;
			}
		case 4:
			if (down == false) {
				direction = 1;
			}
			else {
				left = false;
				right = false;
				up = false;
				break;
			}
		}

		for (i = 1; i < shipSize; i++) {
			if (left == true) {
				computerBoard[startPointY][startPointX - i] = shipValue;
			}
			else if (right == true) {
				computerBoard[startPointY][startPointX + i] = shipValue;
			}
			else if (up == true) {
				computerBoard[startPointY - i][startPointX] = shipValue;
			}
			else if (down == true) {
				computerBoard[startPointY + i][startPointX] = shipValue;
			}
		}

		ships -= 1;
	}
}

void playerMap(int playerBoard[][COLUMNS])
{
	int i = 0, j = 0, startPointX, startPointY, userDirection, ships = 5, shipSize = 0, shipValue;

	bool left = true, right = true, up = true, down = true;

	char userCh;

	while (ships > 0) {

		left = true;
		right = true;
		up = true;
		down = true;

		if (ships == 5) {
			cout << "Enter the starting position of your carrier (example: A 2): ";
			shipValue = 10;
			shipSize = 5;
		}
		else if (ships == 4) {
			cout << "Enter the starting position of your battleship (example: A 2): ";
			shipValue = 9;
			shipSize = 4;
		}
		else if (ships == 3) {
			cout << "Enter the starting position of your cruiser (example: A 2): ";
			shipValue = 8;
			shipSize = 3;
		}
		else if (ships == 2) {
			cout << "Enter the starting position of your submarine (example: A 2): ";
			shipValue = 7;
			shipSize = 3;
		}
		else if (ships == 1) {
			cout << "Enter the starting position of your destroyer (example: A 2): ";
			shipValue = 6;
			shipSize = 2;
		}

		cin >> userCh >> startPointX;

		startPointY = static_cast<int>(userCh) - 65;

		startPointX -= 1;

		while (playerBoard[startPointY][startPointX] > 2) {
			cout << "Invalid position. Enter a different position.";
			cin >> userCh >> startPointX;
			startPointY = static_cast<int>(userCh) - 65;
			startPointX -= 1;
		}

		playerBoard[startPointY][startPointX] = shipValue;

		for (i = 1; i < shipSize; i++) {
			if (startPointX >= (10 - shipSize)) {
				right = false;
			}
			if (startPointX <= (-1 + shipSize)) {
				left = false;
			}
			if (playerBoard[startPointY][startPointX + i] > 2) {
				right = false;
			}
			if (playerBoard[startPointY][startPointX - i] > 2) {
				left = false;
			}
		}
		
		for (i = 1; i < shipSize; i++) {
			if (startPointY >= (10 - shipSize)) {
				down = false;
			}
			if (startPointY <= (-1 + shipSize)) {
				up = false;
			}
			if (playerBoard[startPointY + i][startPointX] > 2) {
				down = false;
			}
			if (playerBoard[startPointY - i][startPointX] > 2) {
				up = false;
			}
		}

		cout << "This ship can face these directions: \n";
		if (left == true)
			cout << "- left (1)\n";
		if (right == true)
			cout << "- right (2)\n";
		if (up == true)
			cout << "- up (3)\n";
		if (down == true)
			cout << "- down (4)\n";
		cout << "\nWhich direction will the ship face?: ";
		cin >> userDirection;

		switch (userDirection) {
		case 1:
			if (left != true) {
				cout << "This ship cannot face left. Please enter a different number.";
				cin >> userDirection;
			}
			else {
				right = false;
				up = false;
				down = false;
				break;
			}
		case 2:
			if (right != true) {
				cout << "This ship cannot face right. Please enter a different number.";
				cin >> userDirection;
			}
			else {
				left = false;
				up = false;
				down = false;
				break;
			}
		case 3:
			if (up != true) {
				cout << "This ship cannot face up. Please enter a different number.";
				cin >> userDirection;
			}
			else {
				right = false;
				left = false;
				down = false;
				break;
			}
		case 4:
			if (down != true) {
				cout << "This ship cannot face down. Please enter a different number.";
				cin >> userDirection;
			}
			else {
				right = false;
				up = false;
				left = false;
				break;
			}
		}

		for (i = 1; i < shipSize; i++) {
			if (left == true) {
				playerBoard[startPointY][startPointX - i] = shipValue;
			}
			else if (right == true) {
				playerBoard[startPointY][startPointX + i] = shipValue;
			}
			else if (up == true) {
				playerBoard[startPointY - i][startPointX] = shipValue;
			}
			else if (down == true) {
				playerBoard[startPointY + i][startPointX] = shipValue;
			}
		}
		ships -= 1;

	}

}

void battleshipGame(int playerBoard[][COLUMNS], int computerBoard[][COLUMNS], int computerDisplay[][COLUMNS])
{

	int playerShipsDestroyed = 0, comShipsDestroyed = 0, xGuess, yGuess, comCarrier = 5, comBattleship = 4, comCruiser = 3, comSubmarine = 3, comDestroyer = 2;

	int playCarrier = 5, playBattleship = 4, playCruiser = 3, playSubmarine = 3, playDestroyer = 2;

	char ch;

	cout << "Player will go first!\n";

	while (playerShipsDestroyed < 5 || comShipsDestroyed < 5) {

		gameDisplay(playerBoard, computerDisplay);

		cout << "Player turn.\n";

		cout << "Enter the position of your shot (example F 4): ";

		cin >> ch >> xGuess;

		yGuess = static_cast<int>(ch) - 65;

		xGuess -= 1;

		if (computerBoard[yGuess][xGuess] > 2) {
			cout << "Hit. ";
			if (computerBoard[yGuess][xGuess] == 10) {
				cout << "Carrier.\n";
				comCarrier -= 1;
				if (comCarrier == 0) {
					cout << "Computer carrier has sunk.\n";
					comShipsDestroyed += 1;
				}
			}
			else if (computerBoard[yGuess][xGuess] == 9) {
				cout << "Battleship.\n";
				comBattleship -= 1;
				if (comBattleship == 0) {
					cout << "Computer battleship has sunk.\n";
					comShipsDestroyed += 1;
				}
			}
			else if (computerBoard[yGuess][xGuess] == 8) {
				cout << "Cruiser.\n";
				comCruiser -= 1;
				if (comCruiser == 0) {
					cout << "Computer cruiser has sunk.\n";
					comShipsDestroyed += 1;
				}
			}
			else if (computerBoard[yGuess][xGuess] == 7) {
				cout << "Submarine.\n";
				comSubmarine -= 1;
				if (comSubmarine == 0) {
					cout << "Computer submarine has sunk.\n";
					comShipsDestroyed += 1;
				}
			}
			else if (computerBoard[yGuess][xGuess] == 6) {
				cout << "Destroyer.\n";
				comDestroyer -= 1;
				if (comDestroyer == 0) {
					cout << "Computer destroyer has sunk.\n";
					comShipsDestroyed += 1;
				}
			}
			computerDisplay[yGuess][xGuess] = -1;
		}
		else {
			cout << "Miss.\n";
			computerDisplay[yGuess][xGuess] = 1;
		}

		cout << "Computer will go next.\n";

		xGuess = 0 + rand() % 10;
		yGuess = 0 + rand() % 10;

		while (playerBoard[yGuess][xGuess] == -1 || playerBoard[yGuess][xGuess] == 1) {
			xGuess = 0 + rand() % 10;
			yGuess = 0 + rand() % 10;
		}

		cout << "Computer guesses " << (static_cast<char>(yGuess + 65)) << " " << xGuess + 1 << "!" << endl;

		if (playerBoard[yGuess][xGuess] > 2) {
			cout << "Hit! ";
			if (playerBoard[yGuess][xGuess] == 10) {
				cout << "Carrier.\n";
				playCarrier -= 1;
				if (playCarrier == 0) {
					cout << "Player carrier has sunk.\n";
					playerShipsDestroyed += 1;
				}
			}
			else if (playerBoard[yGuess][xGuess] == 9) {
				cout << "Battleship.\n";
				playBattleship -= 1;
				if (playBattleship == 0) {
					cout << "Player battleship has sunk.\n";
					playerShipsDestroyed += 1;
				}
			}
			else if (playerBoard[yGuess][xGuess] == 8) {
				cout << "Cruiser.\n";
				playCruiser -= 1;
				if (playCruiser == 0) {
					cout << "Player cruiser has sunk.";
					playerShipsDestroyed += 1;
				}
			}
			else if (playerBoard[yGuess][xGuess] == 7) {
				cout << "Submarine.\n";
				playSubmarine -= 1;
				if (playSubmarine == 0) {
					cout << "Player submarine has sunk.";
					playerShipsDestroyed += 1;
				}
			}
			else if (playerBoard[yGuess][xGuess] == 6) {
				cout << "Destroyer.\n";
				playDestroyer -= 1;
				if (playDestroyer == 0) {
					cout << "Player destroyer has sunk.";
					playerShipsDestroyed += 1;
				}
			}
			playerBoard[yGuess][xGuess] = -1;
		}
		else {
			cout << "Miss.\n";
			playerBoard[yGuess][xGuess] = 1;
		}
	}
	if (playerShipsDestroyed == 5) {
		cout << "Computer wins.";
	}
	else if (comShipsDestroyed == 5) {
		cout << "Player wins!";
	}
}