#include "Computer.h"
#include "Gamer.h"

#include <iostream>

using namespace std;

void Computer::namePlayer() {
	strcpy(name, "Bot"); //kazdy komputer ma na imiê Bot
	int x = rand() % 8; //losowanie pionka
	(x == 0) ? (counter = '!') : (x == 1) ? (counter = '@') : (x == 2) ? (counter = '#') : (x == 3) ? (counter = '$') : (x == 4) ? (counter = '%') : (x==5)?(counter = '^'):(x==6)?(counter='&'):(x==7)?(counter='+'):(counter='x');
}

Computer::Computer() {
}


Computer::~Computer() {
}
