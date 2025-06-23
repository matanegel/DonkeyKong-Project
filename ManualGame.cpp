#include "ManualGame.h"


void ManualGame::choose_level() {
	int player_lvl;
	system("cls");
	std::cout << "choose your start level and then enter(0 - " << max_level - 1 << ") else default level 0:" << std::endl;
	std::cin >> player_lvl;
	// Check if the input level is valid (within the allowed range)
	if (player_lvl <= (max_level - 1) && player_lvl >= 0) {
		board.set_floor(player_lvl);       // If valid, set the game board to the chosen level.
		level = player_lvl;
	}
}

// Checking the input key for the next operation (exit||stop||continue)
bool ManualGame::key_was_pressed(char key) {
	bool flag_break = false;
	if (key == EXIT && !save) {
		flag_break = true;
		exit_flag = true;
		player_state = 3;
		board.get_mario().reset_mario();
		
	}
	else if (key == STOP) {
		stop_game();
	}
	else if (key == 'c') {
		board.get_mario().get_mario_pos().set_color_definition();

	}
	else {
		if (key == 'p') {
			board.hammer_attack();
		}
		board.check_wall_hit();
		board.next_mario_move(key);

	}

	return flag_break;
}

void ManualGame::save_to_file_steps(int count, char ch) {
		
	if (save) {
		bool is_valid = (ch == 'a' || ch == 'd' || ch == 's' || ch == 'x' || ch == 'w' || ch == 'p' || ch == 'c');
		if (file_steps_w.is_open()) {
			if (is_valid) {
				file_steps_w << count << " " << ch << std::endl;
			}
		}
	}
}

void ManualGame::save_to_result_file(int count, const Position& poss) {
	if (board.get_score() <= -6) {
		int i;
		i = 5;
	}
	if (save) {
		if (file_result_w.is_open()) {

			file_result_w << count << " " << poss.get_x() << "," << poss.get_y() << " " << player_state;
			file_result_w << " " << board.get_score_screen();
			file_result_w << std::endl;

			if (player_state == 1 || player_state == 2) {
				file_result_w << board.get_score() << "-" << "Toatal score";
			}
			
		}
	}
}

void ManualGame::handle_and_open_files() {
	if (save) {
		file_steps_w.open(get_the_name_file(level, "steps"));
		file_result_w.open(get_the_name_file(level, "result"));

		int seed = static_cast<int>(time(nullptr));
		srand(seed);
		save_seed(seed, file_steps_w);
	}
}

void ManualGame::close_files() {
	if (save) {
		file_steps_w.close();
		file_result_w.close();
	}
}