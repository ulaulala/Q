#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <io.h>
#include <fcntl.h>

#include "Board.h"
#include "Gamer.h"
#include "Player.h"
#include "GameMaster.h"
#include "List.h"

using namespace std;

int main() {
	srand(time(NULL));
	//_setmode(_fileno(stdout), _O_WTEXT);
	
	GameMaster manager;
	Gamer** players = NULL;
	Board gameBoard;
	
	List<int>* head = NULL;
	List<int>* tail = NULL;

	manager.menu(players, gameBoard, head, tail);


}