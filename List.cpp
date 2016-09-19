#include <iostream>

#include "Board.h"
#include "List.h"

using namespace std;


template<class T>
List<T>::List(T x1, T y1, T direction): next(NULL) {
	this->x1 = x1; //pobrany srodek scianki
	this->y1 = y1;
	if (direction == 0) { // poziomo
		y2 = y1 - 1; //ustawienie pozostalych wspolrzednych wzgledem kierunku
		y3 = y1 + 1;
		x3 = x2 = x1;
	}
	else if (direction == 1) { //pionowo 
		x2 = x1 - 1; //ustawienie pozostalych wspolrzednych wzgledem kierunku
		x3 = x1 + 1;
		y3 = y2 = y1;
	}
}

template<class T>
List<T>::List(): next(NULL) {
	x1 = x2 = x3 = 0;
	y1 = y2 = y3 = 0;
}

template<class T>
void List<T>::wallsToBoard(Board &gameBoard) { //ustawienie scianki na planszy
	gameBoard.setBoard(x1, y1, '*');
	gameBoard.setBoard(x2, y2, '*');
	gameBoard.setBoard(x3, y3, '*');
}

template<class T>
List<T>::~List() {
	delete next;
}

template class List<int>;
