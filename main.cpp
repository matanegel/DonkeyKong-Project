#include <iostream>
#include "utils.h"
#include "position.h" 
#include "board.h" 
#include "game.h"
#include "ManualGame.h"
#include "FileGame.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <cstdlib>
#include <crtdbg.h>



int main(int argc, char* argv[]) {
	gotoxy(0, 0);
	ShowConsoleCursor(false);

	Game* modeGame;

	if (argc > 1 && std::string(argv[1]) == "-save") {
		modeGame = new ManualGame(true);
		
	}
	if (argc > 1 && std::string(argv[1]) == "-load") {
		if (argc > 2 && std::string(argv[2]) == "-silent") {
			modeGame = new FileGame(true);
		}
		else {
			modeGame = new FileGame(false);
		}
			
	}
	else {
		modeGame = new ManualGame(false);
	}
	delete modeGame;

	return 0;
}