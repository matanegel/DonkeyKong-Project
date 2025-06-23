#pragma once 

#include "position.h"
class Board;

class Mario {
private:
	static constexpr int LEFT_MOVE = -1;
	static constexpr int RIGHT_MOVE = 1;
	static constexpr int DOWN_MOVE = 1;
	static constexpr int UP_MOVE = -1;
	static constexpr int STAND_MOVE = 0;
	static constexpr int start_X = 1;
	static constexpr int start_Y = 23;
	static constexpr int NONE = 0;


	bool won = false;
	bool alive = true;
	bool is_jumping = false;
	bool has_an_hammer = false;
	int amount_of_mario = 0;
	bool is_climbing = false;
	
	char mario = '@';
	Position mario_pos;
	Board* pb = nullptr; 
	int start_poss_x = 0;
	int start_poss_y = 0;
	int mario_dir = STAND_MOVE;
	int mario_dir_y = STAND_MOVE;
	int lives = 3;
	int jumpCounter = 0; // Count iteration while jumping

public:
	Mario() : mario_dir(STAND_MOVE),mario_pos(start_X, start_Y) {  };
	Mario(const Mario&) = delete;
	Mario& operator= (const Mario&) = delete;
	bool get_hammer_flag() const{ return has_an_hammer; };
	void set_super_mario() { mario = 'M'; }
	void set_won(bool condition) { won = condition; }
	void set_alive(bool condition) { alive = condition; }
	void set_mario_board(Board* b); 
	void set_mario_dir(int new_dir) { mario_dir = new_dir; }
	void set_mario_dir_y(int new_dir) { mario_dir_y = new_dir; }
	void set_starting_pos(int x, int y) { mario_pos.set_xy(x, y); }
	void set_jumping(bool condition) { is_jumping = condition; }
	void set_lives(int _lives) { lives = _lives; };
	void save_and_set_starting_poss(int x, int y) { start_poss_x = x, start_poss_y = y, set_starting_pos(x, y); }
	
	Position& get_mario_pos() { return mario_pos; }
	int get_mario_dir() { return mario_dir; }
	int get_lives() const;
	char get_mario_char() { return mario; }
	bool get_alive() const { return alive; }
	bool get_won() const { return won; }
	bool get_jumping_flag() const { return is_jumping; }
	int get_start_x() const { return start_poss_x; }
	int get_start_y() const { return start_poss_y; }

	bool next_move_secure(int dir_x, int dir_y);
	void reset_jumpimgCounter() { jumpCounter = 0; }
	void right();
	void left();
	void stand();
	void move_m(int dir_y);
	void move_mario();
	void climb(int dir_y);
	void fall();
	void decrease_lives();
	void jump(int mario_dir);
	void reset_mario();
	void increase_amount() { amount_of_mario++; }
	int get_amount_of_mario() { return amount_of_mario; }
	void reset_amount() { amount_of_mario = 0; }
	void update_climbing_flag();
};