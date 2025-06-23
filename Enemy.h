#pragma once
#include "utils.h" 
#include "position.h"

class Enemy
{
protected:
	static constexpr int NONE = 0;
	Position poss;
	int start_poss_x = 0;
	int start_poss_y = 0;
	bool movement = true;
	char symbol;
	int dir_x = NONE;
	int dir_y = NONE;
	bool dangerous = false;

public:
	Enemy(char symbol, int x ,int y) : symbol(symbol), poss(x, y), start_poss_x(x), start_poss_y(y) {} // Constructor with symbol initialization and poss
	void set_poss(int x, int y) { poss.set_xy(x, y); };
	void set_dir_x(int x) { dir_x = x; }
	void set_dir_y(int y) { dir_y = y; }
	

	char get_symbol() const { return symbol; };
	int get_dir_x() const { return dir_x; }
	int get_dir_y() const { return dir_y; }
	Position get_poss()const { return poss; }
	void random_dir() { (rand() % 2 == 0) ? dir_x = -1 : dir_x = 1; };
	//bool is_dangerous() const { return dangerous; }
	void reset_poss_after_strike();

};

