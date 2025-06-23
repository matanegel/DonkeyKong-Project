#pragma once
#include "utils.h" 
#include "position.h"
#include "Enemy.h"
#include <time.h>
#include "mario.h"
 
class Ghost : public Enemy
{
protected:
	static Mario* mario_ptr;
	bool is_climbing = false;
	bool is_climbing_down = false;
	
public:
	// Constructor: Initializes a Ghost at position (x, y)
	// and calls a function to assign it a random direction.
	Ghost(char symbol, int x, int y) : Enemy(symbol, x, y) {  
		random_dir();
	};

	virtual void move() { poss.move(symbol, dir_x, dir_y); };
	// Generates a random number between 0 and 99.
	int random_1_100() const { return rand() % 100; };
	// Determines if the Ghost should change direction.
	// There is a 5% chance (when num < 5) to return true, 
	// indicating the Ghost should change direction.
	 virtual bool check_probability_to_change_dir()const{
		int num = random_1_100();
		return num < 5 ? true : false;
	}
	void set_climbing(bool flag) { is_climbing = flag; }
	void set_climbing_down(bool flag) { is_climbing_down = flag; }
	bool get_climbing() { return is_climbing; }
	bool get_climbing_down() { return is_climbing_down; }
	void set_mario_pointer(Mario* const mario) {
		mario_ptr = mario;
	}
};