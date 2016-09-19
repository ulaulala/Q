#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cctype>
#include <string>
#include <time.h>

#include "Gamer.h"
#include "Computer.h"
#include "Player.h"
#include "GameMaster.h"
#include "List.h"

using namespace std;

Gamer** GameMaster::makePlayers() {
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "  NOWA GRA" << endl << endl;
	SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "  Ilu graczy wezmie udzial w grze? (2 lub 4):  ";
	while (1) {
		string tempHowManyPlayers; //zmienna pomocnicza dla ktorej sprawdzane sa dane
		cin >> tempHowManyPlayers;
		if (tempHowManyPlayers[1] == '\0') { //czy wpisano tylko jeden znak?
			if (tempHowManyPlayers[0] != '2' && tempHowManyPlayers[0] != '4') {
				SetConsoleTextAttribute(hOut, 8);
				cout << "W grze moze wziac udzial 2 lub 4 przeciwnikow. ";
				cout << "Podaj jeszcze raz: ";
				SetConsoleTextAttribute(hOut, 7);
			}
			else {
				howManyPlayers = tempHowManyPlayers[0] - 48; //poprawny wynik konwertuje z char na int
				break;
			}
		}
		else {
			SetConsoleTextAttribute(hOut, 8);
			cout << "W grze moze wziac udzial 2 lub 4 przeciwnikow. ";
			cout << "Podaj jeszcze raz: ";
			SetConsoleTextAttribute(hOut, 7);
		}
	}

	cout << "  Ilu z nich to komputer? ";
	while (1) {
		string tempHowManyComputers;
		cin >> tempHowManyComputers;
		//cout << "Wpisales: " << tempHowManyComputers << endl;
		if (tempHowManyComputers[1] == '\0') {
			if (howManyPlayers == 2) {
				if (tempHowManyComputers[0] == '1' || tempHowManyComputers[0] == '0') {
					howManyComputers = tempHowManyComputers[0] - 48; //poprawny wynik: char->int
					break;
				}
				else {
					SetConsoleTextAttribute(hOut, 8);
					cout << "Blad danych. Podaj jeszcze raz: ";
					SetConsoleTextAttribute(hOut, 7);
				}
			}
			else if (howManyPlayers == 4) {
				if (tempHowManyComputers[0] == '0' || tempHowManyComputers[0] == '1' || tempHowManyComputers[0] == '2' || tempHowManyComputers[0] == '3') {
					howManyComputers = tempHowManyComputers[0] - 48; //poprawny wynik: char->int
					break;
				}
				else {
					SetConsoleTextAttribute(hOut, 8);
					cout << "Blad danych. Podaj jeszcze raz: ";
					SetConsoleTextAttribute(hOut, 7);
				}
			}
		}
		else {
			SetConsoleTextAttribute(hOut, 8);
			cout << "Blad danych. Podaj jeszcze raz: ";
			SetConsoleTextAttribute(hOut, 7);
		}
	}

	howManyHumans = howManyPlayers - howManyComputers;
	Gamer** players = new Gamer*[howManyPlayers]; //wskaznik na JAKIEGOS gracza
	int n = 0;
	for (int i = 0; i < howManyHumans; i++) { //najpierw stworz "ludzkich" graczy
		players[n] = new Player[1];
		n++;
	}
	for (int i = 0; i < howManyComputers; i++) { //brakujacy to komputery
		players[n] = new Computer[1];
		n++;
	}


	n = 0;

	for (int i = 0; i < howManyPlayers; i++) { //specyfikacja graczy
		cout << endl << "  GRACZ " << n + 1 << endl;
		players[n]->namePlayer();

		if (i == 0)
			players[n]->move(1, 9); //1,5
		else if (i == 1)
			players[n]->move(17, 9); //9,5
		else if (i == 2)
			players[n]->move(9, 17); // 5,9
		else if (i == 3)
			players[n]->move(9, 1); // 5,1
		n++;

	}

	system("CLS");

	return players;
}

int GameMaster::getHowManyPlayers() {
	return howManyPlayers;
}

void GameMaster::game(Gamer** players, Board gameBoard, List<int>* head, List<int>* tail) {
	while (1) {
		for (int i = 0; i < howManyPlayers; i++) {
			HANDLE hOut;
			hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			cout << endl << endl;
			cout << " Ruch " << players[i]->getName() << " (" << players[i]->getCounter() << ")" << endl;
			int x = players[i]->getX();
			int y = players[i]->getY();
			string direction;

			while (1) {
				if (!strcmp(players[i][0].getName(), "Bot")) { //czy ten gracz to komputer?
					int tempdirection;
					tempdirection = rand() % 5;
					(tempdirection == 0) ? (direction = "w") : (tempdirection == 1) ? (direction = "a") : (tempdirection == 2) ? (direction = "s") : (tempdirection == 3) ? (direction = "d") : (tempdirection == 4) ? (direction = "b") : (direction = "s");
					//direction[0] = '\0';
				}
				else
					cin >> direction;
				if (direction[1] == '\0') {
					if (direction[0] == 'w' || direction[0] == 'W') {
						if (x != 1 && gameBoard.getBoard(x - 1, y) != '*') { //czy nie chce ruszyc sie poza plansze && czy nie chce przejsc przez scianke
							if (gameBoard.getBoard(x - 2, y) == ' ') { //jesli pole obok w tym kierunku jest puste to przestaw na nie
								x = x - 2;
							}
							else if (gameBoard.getBoard(x - 4, y) == ' ' && gameBoard.getBoard(x - 3, y) != '*') { //jesli pole bezposrednio obok w tej linii jest zajête przestaw na nastêpne jesli jest puste
								x = x - 4;
							}
							players[i]->move(x, y); //zmienia polozenie na nowe wartosci x i y
							break;
						}

						else {
							SetConsoleTextAttribute(hOut, 8);
							cout << "Ruch niemozliwy. Jeszcze raz: ";
							SetConsoleTextAttribute(hOut, 7);
							continue;
						}
					}
					else if (direction[0] == 'a' || direction[0] == 'A') {
						if (y != 1 && gameBoard.getBoard(x, y - 1) != '*') {
							if (gameBoard.getBoard(x, y - 2) == ' ') {
								y = y - 2;
							}
							else if (gameBoard.getBoard(x, y - 4) == ' ' && gameBoard.getBoard(x, y - 3) != '*') {
								y = y - 4;
							}
							players[i]->move(x, y);
							break;
						}
						else {
							SetConsoleTextAttribute(hOut, 8);
							cout << "Ruch niemozliwy. Jeszcze raz: ";
							SetConsoleTextAttribute(hOut, 7);
							continue;
						}
					}
					else if (direction[0] == 's' || direction[0] == 'S') {
						if (x != 17 && gameBoard.getBoard(x + 1, y) != '*') {
							if (gameBoard.getBoard(x + 2, y) == ' ') {
								x = x + 2;
							}
							else if (gameBoard.getBoard(x + 4, y) == ' ' && gameBoard.getBoard(x + 3, y) != '*') {
								x = x + 4;
							}
							players[i]->move(x, y);
							break;
						}
						else {
							SetConsoleTextAttribute(hOut, 8);
							cout << "Ruch niemozliwy. Jeszcze raz: ";
							SetConsoleTextAttribute(hOut, 7);

						}
					}
					else if (direction[0] == 'd' || direction[0] == 'D') {
						if (y != 17 && gameBoard.getBoard(x, y + 1) != '*') {
							if (gameBoard.getBoard(x, y + 2) == ' ') {
								y = y + 2;
							}
							else if (gameBoard.getBoard(x, y + 4) == ' ' && gameBoard.getBoard(x, y + 3) != '*') {
								y = y + 4;
							}
							players[i]->move(x, y);
							break;
						}
						else {
							SetConsoleTextAttribute(hOut, 8);
							cout << "Ruch niemozliwy. Jeszcze raz: ";
							SetConsoleTextAttribute(hOut, 7);
							continue;
						}
					}
					else if (direction[0] == 'b' || direction[0] == 'B') { //scianka
						char p = 0, q = 0;
						int x, y;
						int way = -10;
						if (!strcmp(players[i]->getName(), "Bot")) { //czy ten gracz to komputer?
							do {									//losowy ruch (powtarzaj az nie napotkasz innych scianek)
								p = rand() % 8 + 97;
								q = rand() % 8 + 97;
								way = rand() % 2;
								(p == 'a' || p == 'A') ? (x = 2) : (p == 'b' || p == 'B') ? (x = 4) : (p == 'c' || p == 'C') ? (x = 6) : (p == 'd' || p == 'D') ? (x = 8) : (p == 'e' || p == 'E') ? (x = 10) : (p == 'f' || p == 'F') ? (x = 12) : (p == 'g' || p == 'G') ? (x = 14) : (p == 'h' || p == 'H') ? (x = 14) : (x = 0);
								(q == 'a' || q == 'A') ? (y = 2) : (q == 'b' || q == 'B') ? (y = 4) : (q == 'c' || q == 'C') ? (y = 6) : (q == 'd' || q == 'D') ? (y = 8) : (q == 'e' || q == 'E') ? (y = 10) : (q == 'f' || q == 'F') ? (y = 12) : (q == 'g' || q == 'G') ? (y = 14) : (q == 'h' || q == 'H') ? (y = 14) : (y = 0);
							} while ((way == 0) ? (gameBoard.getBoard(x, y) == '*' || gameBoard.getBoard(x, y - 1) == '*' || gameBoard.getBoard(x, y + 1) == '*') : (gameBoard.getBoard(x, y) == '*' || gameBoard.getBoard(x - 1, y) == '*' || gameBoard.getBoard(x + 1, y) == '*'));
						} // jesli poziomo to sprawdz czy nie ma w tym punkcie i sasiednich y-ach scianki, w przeciwnym wypadku (jesli pionowo) sprawdz sasiednie x 
						else {
							do {
								if (way != -10) {
									SetConsoleTextAttribute(hOut, 8);
									cout << "Tutaj stoi juz scianka. Postaw gdzies indziej:" << endl;
									SetConsoleTextAttribute(hOut, 7);
								}
								cout << " Srodek scianki:" << endl << "   wiersz (a-h): ";
								cin >> p;
								while (p < 97 || p >104) { // wg ASCII: od a do h
									SetConsoleTextAttribute(hOut, 8);
									cout << "Blad. Ponow probe: ";
									SetConsoleTextAttribute(hOut, 7);
									cin >> p;
								} //ustaw x dla tablicy board[x][y] w zaleznosci od a-h:
								// koncowa instrukcja (x=0) nigdy sie nie wykona, napisana na potrzeby poprawnosci skladni operatora selekcji
								(p == 'a' || p == 'A') ? (x = 2) : (p == 'b' || p == 'B') ? (x = 4) : (p == 'c' || p == 'C') ? (x = 6) : (p == 'd' || p == 'D') ? (x = 8) : (p == 'e' || p == 'E') ? (x = 10) : (p == 'f' || p == 'F') ? (x = 12) : (p == 'g' || p == 'G') ? (x = 14) : (p == 'h' || p == 'H') ? (x = 14) : (x = 0);
								cout << "   kolumna (a-h): ";
								cin >> q;
								while (q < 97 || q >104) { // wg ASCII: od a do h
									SetConsoleTextAttribute(hOut, 8);
									cout << "Blad. Ponow probe: ";
									SetConsoleTextAttribute(hOut, 7);
									cin >> q;
								} //ustaw y dla tablcy board[x][y] w zaleznosci od a=h:
								// koncowa instrukcja (y=0) nigdy sie nie wykona, napisana na potrzeby poprawnosci skladni operatora selekcji
								(q == 'a' || q == 'A') ? (y = 2) : (q == 'b' || q == 'B') ? (y = 4) : (q == 'c' || q == 'C') ? (y = 6) : (q == 'd' || q == 'D') ? (y = 8) : (q == 'e' || q == 'E') ? (y = 10) : (q == 'f' || q == 'F') ? (y = 12) : (q == 'g' || q == 'G') ? (y = 14) : (q == 'h' || q == 'H') ? (y = 14) : (y = 0);
								cout << "   pionowo(1)/poziomo(0): ";
								cin >> way;
								while (way != 0 && way != 1) {
									SetConsoleTextAttribute(hOut, 8);
									cout << "Blad. Ponow probe kierunku: ";
									SetConsoleTextAttribute(hOut, 7);
									cin >> way;
								}
							} while ((way == 0) ? (gameBoard.getBoard(x, y) == '*' || gameBoard.getBoard(x, y - 1) == '*' || gameBoard.getBoard(x, y + 1) == '*') : (gameBoard.getBoard(x, y) == '*' || gameBoard.getBoard(x - 1, y) == '*' || gameBoard.getBoard(x + 1, y) == '*'));
						} // jesli poziomo to sprawdz czy nie ma w tym punkcie i sasiednich y-ach scianki, w przeciwnym wypadku (jesli pionowo) sprawdz sasiednie x 

						List <int>* newWall = new List<int>(x, y, way);
						if (head == NULL) {
							head = tail = newWall;
						}
						else {
							tail->next = newWall;
							tail = newWall;
						}
						break;
					}
					else if (direction[0] == 'e' || direction[0] == 'E') {
						cout << " Czy chcesz zapisac gre? (T/N)" << endl;
						string yesOrNo;
						while (1) {
						cin >> yesOrNo;
							if (yesOrNo[1] == '\0') { //czy wpisano 1 znak?
								if (yesOrNo[0] == 't' || yesOrNo[0] == 'T') { //czy to dobry znak?
									save(gameBoard, players, head, tail, i);

									delete head;
									for (int i = 0; i < howManyPlayers; i++)
										delete players[i];
									delete players;

									break;
								}
								else if (yesOrNo[0] == 'n' || yesOrNo[0] == 'N') {

									delete head;
								
									delete []players;

									system("CLS");
									menu(players, gameBoard, head, tail);
									break;
								}
								else {
									SetConsoleTextAttribute(hOut, 8);
									cout << " Wybierz T lub N" << endl;
									SetConsoleTextAttribute(hOut, 7);
								}

							}
							else {
								SetConsoleTextAttribute(hOut, 8);
								cout << "Patrz: sterowanie. Ruch: ";
								SetConsoleTextAttribute(hOut, 7);
							}
						}
					}
					else {
						SetConsoleTextAttribute(hOut, 8);
						cout << "Blad. Podaj jeszcze raz: ";
						SetConsoleTextAttribute(hOut, 7);
					}

				}
				else {
					SetConsoleTextAttribute(hOut, 8);
					cout << "Podaj tylko jeden znak: ";
					SetConsoleTextAttribute(hOut, 7);
				}
			}

			system("CLS");
			gameBoard.draw(players, howManyPlayers, head);

			//czy juz wygrana?
			for (int i = 0; i < howManyPlayers; i++) {
				if (players[0][0].getX() == 17) {
					win(players, 0, gameBoard, head, tail);
				}
				else if (players[1][0].getX() == 1) {
					win(players, 1, gameBoard, head, tail);
				}
				if (howManyPlayers == 4) {
					if (players[2][0].getY() == 1) {
						win(players, 2, gameBoard, head, tail);
					}
					else if (players[3][0].getY() == 17) {
						win(players, 3, gameBoard, head, tail);
					}
				}
			}

		}
	}
}


void GameMaster::win(Gamer** players, int i, Board gameBoard, List<int>* head, List<int>* tail) {
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, 15);
	cout << " GRATULACJE!" << endl;
	cout << players[i]->getName() << " zwyciezyl w tej grze!" << endl << endl;
	SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);

	time_t temptime;
	time(&temptime);

	ofstream statisticsFile;
	statisticsFile.open("statistics.txt", ios_base::app);
	if (statisticsFile.is_open()) {
		statisticsFile << ctime(&temptime);
		statisticsFile << "Uczestnicy:    ";
		for (int j = 0; j < howManyPlayers; j++) {
			statisticsFile << j + 1 << ". " << players[j]->getName() << "  ";
		}
		statisticsFile << endl << "Zwyciezca:    ";
		statisticsFile << players[i]->getName() << endl << endl;
	}

	delete head;
	delete[]players;
	menu(players, gameBoard, head, tail);
}

void GameMaster::menu(Gamer** players, Board gameBoard, List<int>* head, List<int>* tail) {
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "~QUORIDOR~" << endl << endl;
	SetConsoleTextAttribute(hOut, 8);
	cout << " MENU: " << endl;
	SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "  1 - Rozpocznij nowa gre" << endl;
	cout << "  2 - Wznow gre" << endl;
	cout << "  3 - Statystyki" << endl;
	cout << "  4 - Zamknij program" << endl;
	string choose; //zmienna pomocnicza
	int _choose; //wybor wlasciwy
	while (1) {
		cin >> choose;
		if (choose[1] == '\0') {
			if (choose[0] == '1' || choose[0] == '2' || choose[0] == '3' || choose[0] == '4') {
				_choose = choose[0] - 48; //char->int
				break;
			}
			else {
				SetConsoleTextAttribute(hOut, 8);
				cout << "Wybor niemozliwy. Wprowadz ponownie: ";
				SetConsoleTextAttribute(hOut, 7);
			}
		}
		else {
			SetConsoleTextAttribute(hOut, 8);
			cout << "Wybor niemozliwy. Wprowadz ponownie: ";
			SetConsoleTextAttribute(hOut, 7);
		}
	}
	system("CLS");
	switch (_choose) {
	case 1: { //nowa gra
		head = NULL;
		Gamer** players = makePlayers();
		gameBoard.draw(players, howManyPlayers, head);
		game(players, gameBoard, head, tail);
		break;
	}
	case 2: { //wznow
		resume(gameBoard, players, head, tail);
		break;
	}
	case 3: { //statystyka
		system("CLS");
		SetConsoleTextAttribute(hOut, 14);
		cout << "STATYSTYKA:" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
		ifstream statisticsFile;
		statisticsFile.open("statistics.txt");
		if (statisticsFile.is_open()) {
			string line;
			while (!statisticsFile.eof()) { //czyta plik do konca
				getline(statisticsFile, line); //pobiera linie z pliku
				cout << line << endl; //wyswietla pobrana linie
			}
		}
		cout << endl;
		menu(players, gameBoard, head, tail);
		break;
	}
	case 4: { //zakoncz
		SetConsoleTextAttribute(hOut, 11);
		cout << " Zamykanie..." << endl << " Do widzenia :)" << endl;
		if (players != NULL)
			for (int i = 0; players[i] != NULL; i++) {
				delete players[i];
			}
		delete head;
		SetConsoleTextAttribute(hOut, 7);
		Sleep(2000);
		exit(0);
		break;
	}
	}
}

void GameMaster::save(Board gameBoard, Gamer** players, List<int>* head, List<int>* tail, int i) {
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	ofstream savingFile;
	savingFile.open("lastGame.txt");
	if (savingFile.is_open()) {
		//savingFile << i << endl;
		savingFile << howManyPlayers << endl;
		savingFile << howManyComputers << endl;

		//dane graczy:
		for (int i = 0; i < howManyPlayers; i++) {
			savingFile << players[i]->getName() << " " << players[i]->getCounter() << " " << players[i]->getX() << " " << players[i]->getY() << endl;
		}

		//plansza:
		for (int i = 0; i < 19; i++) {
			for (int j = 0; j < 19; j++) {
				char tempInside = gameBoard.getBoard(i, j);
				if (tempInside == ' ') //standardowe czytanie pliku nie czyta spacji wiec zamiast nich zapisywane sa kropki
					savingFile << ".";
				else
					savingFile << tempInside;
			}
			savingFile << endl;
		}
	}
	else {
		SetConsoleTextAttribute(hOut, 8);
		cout << "Blad zapisu." << endl;
		SetConsoleTextAttribute(hOut, 7);
	}
	savingFile.close();
	cout << "Zapisano." << endl;
	Sleep(1500);
	system("CLS");
	menu(players, gameBoard, head, tail);
}

void GameMaster::resume(Board gameBoard, Gamer ** players, List<int>* head, List<int>* tail) {
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	ifstream readingFile;
	readingFile.open("lastGame.txt");
	//cout << "OTWARTO PLIK";
	if (readingFile.is_open()) {
		for (int i = 0; i < 2; i++) {
			if (!readingFile.eof()) {
				if (i == 0) readingFile >> howManyPlayers;
				else if (i == 1) readingFile >> howManyComputers;
			}
			else {
				SetConsoleTextAttribute(hOut, 8);
				cout << "Blad danych w pliku." << endl;
				SetConsoleTextAttribute(hOut, 7);
				Sleep(2000);
				system("CLS");
				menu(players, gameBoard, head, tail);
			}
		}

		/*if (players != NULL)
			delete[]players;
		if (head != NULL)
			delete head;*/

		howManyHumans = howManyPlayers - howManyComputers;
		players = new Gamer*[howManyPlayers];
		int n = 0;
		for (int i = 0; i < howManyHumans; i++) {
			players[n] = new Player[1];
			n++;
		}
		for (int i = 0; i < howManyComputers; i++) {
			players[n] = new Computer[1];
			n++;
		}

		bool error = false;
		for (int j = 0; j < howManyPlayers; j++) {
			for (int k = 0; k < 4; k++) {
				if (!readingFile.eof()) {
					if (k == 0) readingFile >> players[j]->name; // >> players[j]->counter >> players[j]->x >> players[j]->y;
					else if (k == 1) readingFile >> players[j]->counter;
					else if (k == 2)readingFile >> players[j]->x;
					else if (k == 3)readingFile >> players[j]->y;

				}

				if (readingFile.eof()) {
					SetConsoleTextAttribute(hOut, 8);
					cout << "Blad danych w pliku." << endl;
					SetConsoleTextAttribute(hOut, 7);
					Sleep(2000);
					system("CLS");
					menu(players, gameBoard, head, tail);
				}
			}
			//if (!isalpha(players[j]->counter) && !isalnum(players[j]->counter)) error = true;
			//if (isblank(players[j]->name[0])) error = true;
			if (players[j]->x < 0 || players[j]->x > 17 || ((players[j]->x) % 2 == 0)) error = true;
			if (players[j]->y < 0 || players[j]->y > 17 || ((players[j]->y) % 2 == 0)) error = true;


			//cout << "name, counter, x, y: " << players[j]->name << players[j]->counter << players[j]->x << players[j]->y << endl;
		}

		for (int i = 0; i < 19; i++) {
			for (int j = 0; j < 19; j++) {
				if (!readingFile.eof()) {
					char tempInside;
					readingFile >> tempInside;
					if (tempInside == '.') //przy zapisywaniu pomocniczo zapisane zostaly kropki aby w latwy sposob odczytac miejsca gdzie powinna byc spacja
						gameBoard.setBoard(i, j, ' ');
					else
						gameBoard.setBoard(i, j, tempInside);
				}
				else {
					SetConsoleTextAttribute(hOut, 8);
					cout << "Blad danych w pliku." << endl;
					SetConsoleTextAttribute(hOut, 7);
					Sleep(2000);
					system("CLS");
					menu(players, gameBoard, head, tail);
				}
			}
		}
		if (error) {
			SetConsoleTextAttribute(hOut, 8);
			cout << "Blad danych w pliku." << endl;
			SetConsoleTextAttribute(hOut, 7);
			Sleep(2000);
			system("CLS");
			menu(players, gameBoard, head, tail);
		}
	}
	else {
		SetConsoleTextAttribute(hOut, 8);
		cout << "Blad wczytywania." << endl;
		SetConsoleTextAttribute(hOut, 7);
		Sleep(2000);
		system("CLS");
		menu(players, gameBoard, head, tail);
	}
	//wywolanie gry
	gameBoard.draw(players, howManyPlayers, head);
	game(players, gameBoard, head, tail);
}



GameMaster::GameMaster() {
}


GameMaster::~GameMaster() {
}
