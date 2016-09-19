#pragma once
#include <iostream>

#include "Board.h"
#include "Gamer.h"
#include "Player.h"
#include "List.h"

class GameMaster {
public:
	int howManyPlayers, howManyHumans, howManyComputers;
	friend class Player; 
	friend class Board;

	Gamer** makePlayers();
	int getHowManyPlayers();

	void game(Gamer** players, Board gameBoard, List<int>* head, List<int>* tail);
	void win(Gamer** players, int i, Board gameBoard, List<int>* head, List<int>* tail);
	void menu(Gamer** players, Board gameBoard, List<int>* head, List<int>* tail);
	void save(Board gameBoard, Gamer** players, List<int>* head, List<int>* tail, int i);
	void resume(Board gameBoard, Gamer** players, List<int>* head, List<int>*tail);

	GameMaster();
	~GameMaster();
};

