#include "Player.h"
#include "Gamer.h"
#include "Board.h"
#include "GameMaster.h"

#include <string>
#include <iostream>
#include <windows.h>

using namespace std;


Player::Player() {
}

void Player::namePlayer() {
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "  Podaj imie Gracza: ";
	cin >> name;
	cout << "  Jakim pionkiem chcesz byc? ";
	string tempCounter;
	while (1) {
		cin >> tempCounter;
		if (tempCounter[1] == '\0') { //czy napewno podano jeden znak?
			counter = tempCounter[0]; //podany znak jest pionkiem
			break;
		}
		else {
			SetConsoleTextAttribute(hOut, 8);
			cout << "Podaj tylko jeden znak: ";
			SetConsoleTextAttribute(hOut, 7);
		}
	}
	cout << endl;
}



Player::~Player() {
}
