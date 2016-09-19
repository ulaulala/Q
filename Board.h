#pragma once
#include "Player.h"
#include "Gamer.h"
#include "GameMaster.h"
#include "List.h"

template <class T>
class List;

class Board {
	char board[19][19];
	int howManyPlayers;

public:
	Board();
	friend class Player;
	friend class GameMaster;
	template <class T>
	friend class List;

	char getBoard(int x, int y);
	void setBoard(int x, int y, char inside);

	int getHowManyPlayers(GameMaster manager);
	void setHowManyPlayers(int howManyPlayers);

	void draw(Gamer** playersioihnougi, int howManyPlayers, List<int>* head);

	~Board();
};

