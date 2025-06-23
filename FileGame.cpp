#include "FileGame.h"



FileGame::FileGame(bool silent_flag) {
	silent = silent_flag;
	load = true;
	sleep = 60;
	if (silent) {
		sleep = 0;
		board.get_mario().get_mario_pos().set_silent();
		board.set_silent();
	}
	start_game();
}

// Checking the input key for the next operation
bool FileGame::key_was_pressed(char key) {
	bool flag_break = false;
	
	if (key == 'c') {
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

 bool FileGame:: input_flag(){
	 return loop_iter == next_move_iter;
}

 char FileGame::get_input() {
	 char ch;
		 file_steps_r >> ch;
	 
		 if (!file_steps_r.eof()) {
			 file_steps_r >> next_move_iter;
		 }
		 
	 return ch;
 }
 //open files and check they are not empty
 void FileGame::handle_and_open_files() {

	 file_steps_r.open(get_the_name_file(level, "steps"), std::ios::in);
	 file_result_r.open(get_the_name_file(level, "result"), std::ios::in);
	 if (file_result_r.peek() == std::ifstream::traits_type::eof()) {  //check if the result file is empty and breal if it is
		 break_screen = true;
	 }
	 else if (file_steps_r.peek() != std::ifstream::traits_type::eof()) { //check if the steps file doesn't empty
		 file_steps_r >> prev_seed;
		srand(prev_seed);
		file_steps_r >> next_move_iter;
	 }
	 else {
		 break_screen = true;
	 }
	 if(break_screen){   //display a massage for the user before exit the game
		 char ch;
		 std::cout << "Not valid record empty files " << level << "\nEnter a key and enter to exit the game.";
		 std::cin >> ch;
		 close_files();
	 }
 }

 void FileGame:: close_files() {
	 file_steps_r.close();
	 file_result_r.close();
}

 bool FileGame::check_result_file_is_valid() {
	 int x, y;
	 static int row = 1;
	 char ch;
	 bool res = true;
	 int tmp_level = get_level_for_errors();
	 


	 if (file_result_r.is_open()) {
		
		 file_result_r >> sg.result_iter;
		 file_result_r >> x >> ch >> y;
		 sg.result_poss.set_xy(x, y);
		 file_result_r >> sg.result_state;
		 file_result_r >> sg.result_score;

		
		 if (!check_iter_result()) {
			 gotoxy(0, row++);
			 std::cout << "result iter has not compatible in level: " << tmp_level <<" file iter: "<< sg.result_iter << " game: " << loop_iter << std::endl;
			 res = false;
		 }

		 if (!check_score_result()) {
			 gotoxy(0, row++);
			 std::cout << "result score has not compatible in level: " << tmp_level << " file score: "<<sg.result_score << " game:  "<< board.get_score_screen() << std::endl;
			  res = false;
		 }

		 if (!check_state_result()) {
			 gotoxy(0, row++);
			 std::cout << "result state has not compatible in level: " << tmp_level << " file state: "<< sg.result_state<< "game: " << player_state << std::endl;;
			 res = false;
		 }
		 if (!check_poss_result()) {
			 gotoxy(0, row++);
			 std::cout << "result poss has not compatible in level: " << tmp_level << " file position:  "<< sg.result_poss.get_x()<< ", " << sg.result_poss.get_y() <<" game poss: " <<board.get_mario().get_mario_pos().get_x()<< ", " << board.get_mario().get_mario_pos().get_y() << std::endl;;
			res = false;
		 }
	 }
		 return res;
	 
 }

 int FileGame::get_level_for_errors() {
	 if (player_state == 4 || player_state == 1) {
		 return level - 1;
	 }
	 else return level;
 }

 FileGame::~FileGame() {
	 if (silent) {
		 char ch;
		 if (game_res_correct) {
			 gotoxy(0, 0);
			 std::cout << "Test passed." << std::endl;
		 }
		 std::cout << "\n\nPress any key and enter to exit." << std::endl;
		 std::cin >> ch;
	 }
	 else {
		 
		 print_state_board();
	 }
 }