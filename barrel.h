#pragma once 
#include "utils.h" 
#include "position.h"
#include "Enemy.h"
#include <vector>

class Barrel : public Enemy {
private:
	static constexpr int NONE = 0;
	static constexpr int STARTING_Y_LVL = 3;

	bool barrel_on_screen = false;
	

	
	int prev_dir_x = 1;
	int prev_dir_y = NONE;
	int depth_of_fall = NONE;

public:
	Barrel(int x, int y) :Enemy('o', x, y) { barrel_on_screen = true; };
	Barrel() :Enemy('o', 1, 0) {};
	

	void set_on_screen(bool show) { barrel_on_screen = show; }
	
	bool get_on_screen() const { return barrel_on_screen; }

	int get_depth() const { return depth_of_fall; };

	void reset_depth() { depth_of_fall = 0; };
	void left();
	void right();
	void stand();
	void fall();
	void reset_barrel();
	void explode_effect();
	void default_move();
	void set_prev_move() { prev_dir_x = dir_x; };
};