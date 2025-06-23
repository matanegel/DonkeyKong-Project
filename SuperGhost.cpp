#include "SuperGhost.h"

void SuperGhost::move() {
	

	if (is_climbing) {
		dir_y = -1;
		poss.move(symbol, NONE, dir_y);
	}
	else if (is_climbing_down) {
		dir_y = 1;
		poss.move(symbol, NONE, dir_y);
	}
	else {
		dir_y = NONE;	
		Ghost::move();
		hunting_mario();
	}
}

void SuperGhost::hunting_mario() {
	if (poss.get_y() == mario_ptr->get_mario_pos().get_y()) {
		if (poss.get_x() > mario_ptr->get_mario_pos().get_x()) {
			dir_x = -1;
		}
		else {
			dir_x = 1;
		}
	}
}
