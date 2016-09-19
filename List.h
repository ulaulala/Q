#pragma once
#include "Board.h"

class Board;

template <class T>
class List {
		T x1, x2, x3; //wspolrzedne x calej scianki
		T y1, y2, y3; //wspolrzedne y calej scianki
public:
	List<T>* next;

	List();
	List(T x1, T y1, T direction);
	
	void wallsToBoard(Board &gameBoard);

	friend class GameMaster;

	~List();
};

