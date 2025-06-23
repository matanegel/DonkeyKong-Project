#pragma once
#include <cstring>
#include <stdbool.h>
#include "board.h"
#include "mario.h"
#include "position.h"
#include "utils.h"
#include "barrel.h"
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <algorithm>



class Game
{
protected:
	Board board;
	size_t max_level = 0;
	size_t level = 0;
	bool game_is_running = true;
	bool exit_flag = false;
	int player_state = 0;
	bool save = false;
	bool load = false;
	bool silent = false;
	int loop_iter = 0;
	int sleep = 100;
	bool game_res_correct = true;
	bool break_screen = false;
	bool continue_screen = false;
	
	


	int high_scores[4] = {0};
	static constexpr char STOP = 27;
	static constexpr char START = '1';
	static constexpr char MENU = '8';
	static constexpr char EXIT = '9';
	static constexpr char SHOW_SCORES = '2';
	static constexpr int MIDDLE_X = 20;
	static constexpr int MIDDLE_Y = 12;
	static constexpr int MAX_X = 80;
	static constexpr int MAX_Y = 25;

	const char winninig_board[MAX_Y][MAX_X + 1] =
	{   "                                                                              ",//0
		"                                                                              ",//1
		"                          **     **   ******   ***   **                       ",//2
		"                          **     **  **    **  ****  **                       ",//3
		"                          **  *  **  **    **  ** ** **                       ",//4
		"                          ** *** **  **    **  **  ****                       ",//5
		"                           **   **    ******   **   ***                       ",//6
		"                                                                              ",//7
		"                                YOU WON THE GAME!                             ",//8
		"                                                                              ",//9
		"                                   SCORE:                                     ",//10
		"                                                                              ",//11
		"                                                                              ",//12
		"                                                                              ",//13
		"                                                                              ",//14
		"                                                                              ",//15
		"                                                                              ",//16
		"                                                                              ",//17
		"                                                                              ",//18
		"                                                                              ",//19
		"                                                                              ",//20
		"                                                                              ",//21
		"                                                                              ",//22
		"                                                                              ",//23
		"                                                                              ",//24
	};

	const char loss_board[MAX_Y][MAX_X + 1] =
{"                                                                              ",//0
"                                                                              ",//1
"                    ****          ********   *********  *********             ",//2
"                    ****          ********   *********  ***                   ",//3
"                    ****          **    **    *****     *********             ",//4
"                    ****          **    **       ****   *********             ",//5
"                    ***********   ********  *********   ***                   ",//6
"                    ***********   ********  *********   *********             ",//7
"                                YOU LOSE THE GAME!                            ",//8
"                                                                              ",//9
"                                   SCORE:                                     ",//10
"                                                                              ",//11
"                                                                              ",//12
"                                                                              ",//13
"                                                                              ",//14
"                                                                              ",//15
"                                                                              ",//16
"                                                                              ",//17
"                                                                              ",//18
"                                                                              ",//19
"                                                                              ",//20
"                                                                              ",//21
"                                                                              ",//22
"                                                                              ",//23
"                                                                              ",//24
	};
	

public:
	Game() {};
	Game(const Game&) = delete;    
	Game& operator= (const Game&) = delete;  
	virtual ~Game() {};

	void get_the_key();        
	virtual bool key_was_pressed(char key) = 0;       
	bool check_win_or_lose(Mario& mario);  
	void menu_pressed();      
	
	void start_game();       
	void stop_game();
	void print_menu();
	void print_keys();
	void getAllBoardFileNames(std::vector<std::string>& vec_to_fill);
	void set_level_size(int size) { max_level = size; }
	void print_winning_board();
	void print_lose_board();
	void print_state_board();
	virtual void choose_level() = 0;        // Allows the player to choose a starting level for the game.
	void add_to_high_scores();
	void print_high_scores();
	virtual bool input_flag() = 0;     //check if manual call kbhit or file game check with the file if there is a move in this index
	virtual char get_input() = 0;
	virtual void set_save(bool arg) {};
	virtual void set_silent(bool arg) {};
	virtual void save_to_file_steps(int count, char ch) {};
	std::string get_the_name_file(int level, std::string end);
	void save_seed(int seed, std::ofstream& outfile)const;
	virtual void save_to_result_file(int count, const Position& poss) {};
	virtual void handle_and_open_files() = 0;
	virtual void close_files() = 0;
	virtual bool check_result_file_is_valid() { return true; };
	void handle_file_not_valid(const int size);
};

