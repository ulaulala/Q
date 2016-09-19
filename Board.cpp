#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <io.h>
#include <fcntl.h>

#include "Board.h"
#include "Gamer.h"
#include "GameMaster.h"
#include "Player.h"
#include "List.h"

using namespace std;

Board::Board() {
}


char Board::getBoard(int x, int y) {
	return board[x][y];
}

void Board::setBoard(int x, int y, char inside) {
	board[x][y] = inside;
}

int Board::getHowManyPlayers(GameMaster manager) {
	howManyPlayers = manager.getHowManyPlayers();
	return howManyPlayers;
}

void Board::setHowManyPlayers(int howManyPlayers) {
	this->howManyPlayers = howManyPlayers;
}


void Board::draw(Gamer** players, int howManyPlayers, List<int>* head) {
	// info
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "~QUORIDOR~" << endl << endl;
	SetConsoleTextAttribute(hOut, 7);
	cout << " GRACZE:" << endl;
	SetConsoleTextAttribute(hOut, 14);
	this->howManyPlayers = howManyPlayers;
	for (int i = 0; i < howManyPlayers; i++)
		cout << " " << players[i]->getCounter() << " -> " << players[i]->getName() << endl;;
	SetConsoleTextAttribute(hOut, 7);
	cout << endl;
	cout << " Sterowanie: " << endl << endl;
	SetConsoleTextAttribute(hOut, 12);
	cout << "   W  " << endl;
	cout << " A S D" << endl << endl;
	SetConsoleTextAttribute(hOut, 7);
	cout << " W - do gory, A - w lewo, S - w dol, D - w prawo" << endl;
	cout << " B - stawianie scianki" << endl << endl;
	cout << " E - wyjscie z gry" << endl;
	cout << "   Pamietaj aby dokonczyc runde!" << endl << endl;

	//plansza
	for (int i = 0; i < 19; i = i + 2) {
		for (int j = 0; j < 19; j++) {
			board[i][j] = '-';
		}
	}
	for (int i = 1; i < 19; i = i + 2) {
		for (int j = 0; j < 19; j = j + 2) {
			board[i][j] = '|';
		}
		for (int j = 1; j < 19; j = j + 2) {
			board[i][j] = ' ';
		}
	}

	//rozstawienie pionkow
	for (int i = 0; i < howManyPlayers; i++) {
		int xp = players[i]->getX();
		int yp = players[i]->getY();
		/*int xp = 2 * x - 1;
		int yp = 2 * y - 1;*/
		board[xp][yp] = players[i]->getCounter();
	}

	//rozstawienie scianek
	if (head != NULL) {
		for (List<int>* count = head; count != NULL; count = count->next) {
			count->wallsToBoard(*this);
		}
	}

	//wyswietlanie planszy
	SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
			//indeksy na krawedziach:
	cout << setw(3);
	cout << ".";
	int n = 97;
	for (int i = 0; i < 9; i++) {
		cout << setw(3);
		if (i == 0)
			cout << ".";
		else {
			SetConsoleTextAttribute(hOut, 8);
			cout << (char)n;
			n++;
		}
		cout << setw(3);
		SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << i + 1;
	}
	cout << setw(3);
	cout << ".";
	cout << endl;
	n = 97;
	for (int i = 0; i < 19; i++) {
		if (i%2 == 1) {
			cout << setw(3);
			cout << i / 2 + 1; //indeksowanie liczbowe
		}
		else {
			cout << setw(3);
			if (i == 0 || i == 18)
				cout << ".";
			else {
				SetConsoleTextAttribute(hOut, 8);
				cout << (char)n; //indeksowanie literowe
				n++; //nastepna litera
			}
		}
		//plansza wlasciwa
		for (int j = 0; j < 19; j++) {
			if (board[i][j] == '*') { //tam gdzie scianka to na bialo
				cout << setw(3);
				SetConsoleTextAttribute(hOut, 15);
				cout << board[i][j] << flush;
			}
			else if (board[i][j] == '|' || board[i][j] == '-') { //tam gdzie krawedz to fiolet
				cout << setw(3);
				SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << board[i][j] << flush;
			}
			else { //pionk na zolto
				cout << setw(3);
				SetConsoleTextAttribute(hOut, 14);
				cout << board[i][j] << flush;
			}
		}
		cout << endl;
	}
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
}


Board::~Board() {
}
