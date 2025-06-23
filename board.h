#pragma once



#include <cstring>
#include <stdbool.h>
#include "mario.h"
#include "barrel.h"
#include "Ghost.h"
#include "vector"



class Mario;


class Board {
	enum Directions { LEFT = 'a', RIGHT = 'd', UP = 'w', DOWN = 'x', STAND = 's' };
	static constexpr char STOP = 27;
	static constexpr int MAX_Y = 25;
	static constexpr int MAX_X = 80;
	static constexpr int MAX_EXPLODING_RANGE = 2;
	static constexpr int THROWING_TIMER = 50;
	static constexpr int INCREASE_SCORE = 10;
	static constexpr int DECREASE_SCORE = 2;

	
	Mario mario;
	std::vector<Barrel> barrel;
	std::vector<Ghost*> ghost_vec;
	bool board_is_valid = true;
	int timer_throwing_b = 0;
	int score = 0;
	int floor = 0;
	int L_x = 1;
	int L_y = 1;
	int kong_position_x = 0;
	int kong_position_y = 0;
	int curr_board_score = 0;
	bool silent = false;
	
	

	char originalBoard[MAX_Y][MAX_X + 1];
	
	char currentBoard[MAX_Y][MAX_X + 1];  // +1 for null terminator	

public:
	Board() { mario.set_mario_board(this); };
	Board(const Board&) = delete;
	Board& operator=(const Board&) = delete;

	void increase_score();
	
	void decrease_score() { score -= DECREASE_SCORE; curr_board_score -= DECREASE_SCORE; }
	Mario& get_mario() { return mario;}
	const char get_char(int x, int y)const;
	const char get_char_cb(int x, int y);
	void set_char_ob(int x, int y, char new_ch);
	int get_score() const { return score; }
	int get_score_screen() const { return curr_board_score; }
	int get_floor() const { return floor; }
	void move_ghost();
	void reset_score() { score = 0; }
	void reset_score_screen() { curr_board_score = 0; }

	int check_ladder_is_under(Position& poss);
	bool check_wall_hit();
	bool check_mario_in_fall();
	char floor_under_barrel(const Position& poss);
	bool floor_is_under(Position& poss) const;
	bool floor_is_under(Position&& poss) const;
	bool floor_under_b(char under);
	bool in_border_x();
	bool in_border_y();
	bool is_ladder(Position& poss);
	bool is_last_level_of_ladder(Position poss);
	bool update_mario_poss(Position& prev);
	bool update_barrel_poss(Barrel& b);
	bool timer_throw_b(int time_frame);
	bool explode_barrel(Barrel& barrel, int b_itr, Mario& mario);

	void throw_barrel();
	void next_mario_move(char ch_pressed);
	void move_barrel(Barrel& b);
	void up_is_pressed(Position& poss);
	void restart_level();
	void reset();
	void print();
	void print_prev_char(Position& poss);
	void load(const std::string& filename);
	void update_legend();
	void need_change_dir( Ghost& g);
	void clear_ghost_vec();
	void clear_barrels();
	void hammer_attack();
	void increase_floor() { floor++;}
	void set_floor(int x) { floor = x; }
	bool check_board_is_valid();
	bool check_and_print_errors(bool floor_valid, int qOnB, int kOnB, int gOnB, bool qOnAir, bool kOnAir);
	void hammer_effect(int x, int y);
	void free_ghost_vec();
	void set_silent() { silent = true; }
	void update_mario_ptr_to_ghost(){
		if (!ghost_vec.empty()) {
			ghost_vec[0]->set_mario_pointer(&mario);
		}
	}
	bool valid_char(char ch);
};  

