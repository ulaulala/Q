#pragma once
#include "Gamer.h"
#include "Board.h"
#include "GameMaster.h"

class Player: public Gamer {

public:
	void namePlayer();

	friend class Board;
	friend class GameMaster;

	Player();
	~Player();
};

