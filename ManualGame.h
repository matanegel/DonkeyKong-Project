#pragma once
#include "Game.h"


class ManualGame : public Game
{
private:
	std::ofstream file_steps_w;
	std::ofstream file_result_w;


public:
	ManualGame(bool save_flag) { save = save_flag; get_the_key(); }
	virtual void choose_level() override;
	virtual bool input_flag()override {
		return _kbhit();
	}
	virtual char get_input() override {
		return _getch();
	}
	bool key_was_pressed(char key) override;

	void set_save(bool arg) { save = arg; }
	virtual void save_to_file_steps(int count, char ch) override;
	void save_to_result_file( int count, const Position& poss) override;
	virtual void handle_and_open_files() override;
	virtual void close_files() override;
};

