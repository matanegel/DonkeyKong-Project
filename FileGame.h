#pragma once
#include "Game.h"


class FileGame : public Game
{
private:

	class SilentGame {
		int result_iter = 0;
		Position result_poss;
		int result_state = 0;
		int result_score = 0;
		
		
	public:
		friend FileGame;
		SilentGame() = default;
	};

	SilentGame sg;
	std::ifstream file_steps_r;
	std::ifstream file_result_r;
	int prev_seed = 0;
	int next_move_iter = 0;
	int file_cursor = 0;
	
	

public:
	FileGame(bool silent_flag);
	~FileGame();
	void choose_level() override { level = 0; };
	virtual bool input_flag() override;
	bool key_was_pressed(char key) override;
	char get_input() override;
	void set_silent(bool arg) override {silent = arg;}
	virtual void set_save(bool arg) {};	
	void set_next_move_iter(int new_iter) { next_move_iter = new_iter; }
	virtual void handle_and_open_files() override;
	virtual void close_files();
	virtual bool check_result_file_is_valid() override;
	bool check_iter_result() { return loop_iter == sg.result_iter; };
	bool check_state_result() { return player_state == sg.result_state; };
	bool check_score_result() { return board.get_score_screen() == sg.result_score; };
	bool check_poss_result() { return board.get_mario().get_mario_pos() == sg.result_poss; };
	int get_level_for_errors();
};
