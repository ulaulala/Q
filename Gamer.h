#pragma once
class Gamer {
protected:
	int x, y;
	char name[20];
	char counter;
public:
	virtual void namePlayer() = 0;
	void move(int x, int y);

	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	char getCounter();
	char* getName();

	friend class Board;
	friend class GameMaster;

	Gamer();
	~Gamer();
};

