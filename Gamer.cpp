#include "Gamer.h"

void Gamer::move(int x, int y) {
	setX(x);
	setY(y);
}

int Gamer::getX() {
	return x;
}

int Gamer::getY() {
	return y;
}

void Gamer::setX(int x) {
	this->x = x;
}

void Gamer::setY(int y) {
	this->y = y;
}

char Gamer::getCounter() {
	return counter;
}

char * Gamer::getName() {
	return name;
}

Gamer::Gamer() {
}


Gamer::~Gamer() {
}
