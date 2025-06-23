#include "utils.h" 
#include "position.h"
#include "barrel.h"

// Move barrel one step to the left
void Barrel::left() {
	dir_x = -1;
	dir_y = NONE;
	prev_dir_x = dir_x;
	prev_dir_y = dir_y;
	poss.move(symbol, dir_x, dir_y);
}
// Move barrel one step to the right
void Barrel::right() {
	dir_x = 1;
	dir_y = NONE;
	prev_dir_x = dir_x;
	prev_dir_y = dir_y;
	poss.move(symbol, dir_x, dir_y);
}
// Move barrel one step by default direction

// No move for barrel
void Barrel::stand() {
	dir_x = NONE;
	dir_y = NONE;
	poss.move(symbol, NONE, NONE);
}
// Falling barrel function
void Barrel::fall() {
	dir_x = NONE;
	dir_y = 1;
	depth_of_fall++;
	poss.move(symbol, dir_x, dir_y);
}
// Reset all private to default position
void Barrel::reset_barrel() {
	barrel_on_screen = false;
	dir_x = NONE;
	dir_y = NONE;
	depth_of_fall = NONE;
	poss.erase();
	reset_poss_after_strike();
}
// Exploding effect
void Barrel::explode_effect() {
	
		for (int j = 0; j <= 2; j++) {
			for (int i = 2; i > 0; i--) {
				gotoxy(poss.get_x() - i, poss.get_y() - j);
				std::cout << 'x';
			}
			for (int i = 0; i <= 2; i++) {
				gotoxy(poss.get_x() + i, poss.get_y() - j);
				std::cout << 'x';
			}
		}

		Sleep(2);
	for (int j = 0; j <= 2; j++) {
		for (int i = 2; i > 0; i--) {
			gotoxy(poss.get_x() - i, poss.get_y() - j);
			std::cout << ' ';
		}
		for (int i = 0; i <= 2; i++) {
			gotoxy(poss.get_x() + i, poss.get_y() - j);
			std::cout << ' ';
		}
	}
}
//Move barrel by his previous direction
void Barrel::default_move() {
	dir_x = prev_dir_x;
	dir_y = NONE;
	poss.move(symbol, dir_x, dir_y);
}


