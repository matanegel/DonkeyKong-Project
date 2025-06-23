#include "Game.h"


// If 'ESC' was pressed stoping the game 
void Game::stop_game() {
	
	while (true) {
		if (_kbhit()) {
			char ch = _getch();
			if (ch == STOP)
				break;
		}
	}
}
// Funcition that manage the game
void Game::start_game() {
	char ch; // character for input key
	Mario& my_mario = board.get_mario(); // Mario by referance from board class
	Position prev_poss; // previous postion for handling previous char printing and board updates 
	bool to_break = false; // flag for breaking
	bool winning = false;  // flag for winning	
	exit_flag = false;         
	
	std::string curr_string_in_file;
	int row = 0;

	std::vector<std::string> fileNames;
	getAllBoardFileNames(fileNames);
	set_level_size(fileNames.size());
	if (max_level == 0) {
		gotoxy(0, 0);
		std::cout << "Not valid. please check the files." << std::endl;
	}
	else {
		if (!save) {
			choose_level();
		}
		for (int i = board.get_floor(); i < fileNames.size(); i++) {
			board.clear_ghost_vec();
			board.load(fileNames[i]);
			if (!board.check_board_is_valid()) {
				handle_file_not_valid(fileNames.size());
				if (break_screen) {
					break_screen = false;
					break;
				}
				if (continue_screen) {
					continue_screen = false;
					continue;
				}
			}
			handle_and_open_files();
			if (break_screen) {
				break_screen = false;
				break;
			}

			board.reset(); // reset board
			if (!silent) {
				board.print(); // print currentBoard
			}
			board.update_mario_ptr_to_ghost();
			// Game loop
			while (true) {
				prev_poss = my_mario.get_mario_pos(); // initialize previous position before move
				// If -> key was pressed
				if (input_flag()) {
					ch = get_input(); // Get the key
					ch = tolower(ch); // Convert the key to lower letter
					
					save_to_file_steps(loop_iter, ch);
					
					to_break = key_was_pressed(ch); // Checking the input key for the next operation (exit||stop||continue) 
					if (to_break) { //return Flag for breaking
						break;
					}
				}
				// Else if -> if (mario.jumping_flag == true) then jumping.
				else if (my_mario.get_jumping_flag()) {
					board.check_wall_hit();
					my_mario.jump(my_mario.get_mario_dir());
				}
				// Checking if mario can move to the default direction
				else {
					board.check_wall_hit();
					my_mario.move_mario();
				}
				if (my_mario.get_alive() == false) {
					board.decrease_score();
				}
				// If -> mario is still alive
				if (my_mario.get_alive() == true || my_mario.get_lives() == 0) {
					board.update_mario_poss(prev_poss); // Update his position on board

					to_break = check_win_or_lose(my_mario); // Check if mario in winning or losing position
					if (to_break) { //return Flag for breaking
						save_to_result_file( loop_iter, my_mario.get_mario_pos());
						if (!check_result_file_is_valid() && game_res_correct) {
							
							gotoxy(0, 0);
							std::cout << "Test failed." << std::endl;
							game_res_correct = false;
						}
						if (player_state == 4) {
							player_state = 0;
						}
						
						break;
					}
					board.check_mario_in_fall(); // Checking if mario in fall condition 
					board.throw_barrel(); // Handling all barrels movement and explosion
					board.move_ghost();
				}
				// If mario is dead restart level
				if (my_mario.get_alive() == false) {
					
					save_to_result_file( loop_iter, my_mario.get_mario_pos());
					if (!check_result_file_is_valid() && game_res_correct) {
						gotoxy(0, 0);
						std::cout << "Test failed. " << std::endl;
						game_res_correct = false;
						
					}
					
					board.restart_level();
				}
				Sleep(sleep);
				// print the prvious character on screen
				board.print_prev_char(prev_poss);
				loop_iter++;
			}
			board.clear_barrels();
			close_files();
			if (my_mario.get_lives() == 0 || level == max_level || exit_flag) {
				board.clear_ghost_vec();
				board.reset_score_screen();
				break;
			}
			board.increase_floor();
			board.reset_score_screen();
		}
	}
}
// Printing menu 
void Game::print_menu() {
	int x = MIDDLE_X; // column position
	int y = MIDDLE_Y;  // row position

	// First line
	gotoxy(x, y);
	std::cout << "DONKEY KONG MENU:";

	// Move down one line...
	gotoxy(x, ++y);
	std::cout << "Press a key:";

	gotoxy(x, ++y);
	std::cout << "(1) Start a new game";
	
	gotoxy(x, ++y);
	std::cout << "(2) High scores";

	gotoxy(x, ++y);
	std::cout << "(8) Present instructions and keys";

	gotoxy(x, ++y);
	std::cout << "(9) EXIT";

}
// Waiting for a key while game on
void Game::get_the_key() {
	
	char key;
	bool run = true;
	while (run) {
		
		print_menu();
		key = _getch();

		switch (key) {
		case EXIT:
			system("cls"); // cleaning the screen before any operation (ChatGPT recommendation)
			run = false;
			game_is_running = false;
			break;
		case MENU:
			menu_pressed();
			break;
		case START:
			system("cls");
			start_game();
			print_state_board();
			break;
		case SHOW_SCORES:
			system("cls");
			print_high_scores();
			break;
		 default:
			 gotoxy(0, 0);
			 std::cout << "Invalid key, please press a correct key";
		}
	}
}
// Printing Game Instructions
void Game::print_keys() {

	std::cout << "c for activate colors" << std::endl
		<< "left = A or a" << std::endl
		<< "right = D or d" << std::endl
		<< "up or jump = W or w" << std::endl
		<< "down = X or x" << std::endl;
}
// Key instruction menu pressed
void Game::menu_pressed() {
	static bool show_menu = true;
	
	system("cls");
	if (show_menu) {
		print_keys();
		std::cout << "\npress (8) again to return";
		show_menu = false;
		
	}
	else {
		show_menu = true;
		
	}

}


// Checking winning or losing 
bool Game::check_win_or_lose( Mario& mario) {
	bool to_break = false;

	if (mario.get_won()) {
		board.increase_score();
		level++;
		mario.reset_mario();
		
		if (level < max_level) {
			mario.set_won(false);
			player_state = 4;
		}
		if (level == max_level) { 
			player_state = 1;
		}
		to_break = true;
	}
	else if (mario.get_lives() <= 0) {
		player_state = 2;
		to_break = true;
	}
	return to_break;

}

void Game::getAllBoardFileNames(std::vector<std::string>& vec_to_fill) {
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator(fs::current_path())) {
		auto filename = entry.path().filename();
		auto filenameStr = filename.string();
		if (filenameStr.substr(0, 6) == "dkong_" && filename.extension() == ".screen") {
			vec_to_fill.push_back(filenameStr);
		}
	}
}

void Game::print_winning_board() {
	system("cls");
	gotoxy(0, 0);
	for (int i = 0; i < MAX_Y - 1; i++) {
		for (int j = 0; j < MAX_X; j++) {
			std::cout << winninig_board[i][j];
		}
		std::cout << std::endl;
	}
		gotoxy(42, 10);
		std::cout << board.get_score();
}

void Game::print_lose_board() {
	system("cls");
	gotoxy(0, 0);
	for (int i = 0; i < MAX_Y - 1; i++) {
		for (int j = 0; j < MAX_X; j++) {
			std::cout << loss_board[i][j];
		}
		std::cout << std::endl;
	}
	gotoxy(42, 10);
	std::cout << board.get_score();

}
// Prints the appropriate board state based on the player's status 
// and resets the game state for the next round
void Game::print_state_board() {
	if (player_state == 2) {
		print_lose_board();
		
	}
	else if (player_state == 1) {
		print_winning_board();
		add_to_high_scores();
	}
	else if(player_state == 3) {
		system("cls");
		gotoxy(0, 0);
		std::cout << "you exit the game... :(\n" << std::endl ;
		
	}
	player_state = 0;
	level = 0;
	loop_iter = 0;
	board.reset_score();
	board.get_mario().set_lives(3);
	board.get_mario().reset_mario();
	board.set_floor(0);
}

// Adds the current score to the high scores list and sorts the scores in descending order.
void Game::add_to_high_scores() {
	high_scores[3] = board.get_score();
	int n = sizeof(high_scores) / sizeof(high_scores[0]);
	std::sort(high_scores, high_scores + n, std::greater<int>()); //
}
//print the scores array(only the first 3 places)
void Game::print_high_scores() {
	static bool show_score = true;

	system("cls");
	if (show_score) {
		int x = 0; // column position
		int y = 0;  // row position
		gotoxy(x, y++);
		std::cout << "High scores:  ";
		gotoxy(x, y++);
		std::cout << "Best score:   " << high_scores[0];
		gotoxy(x, y++);
		std::cout << "Second place: " << high_scores[1];
		gotoxy(x, y++);
		std::cout << "Third place:  " << high_scores[2];
		gotoxy(x, y++);
		std::cout << "\npress (2) to return.";

		show_score = false;
	}
	else {
		show_score = true;
	}
}


std::string Game::get_the_name_file(int level, std::string end) {
	std::string s1 = "dkong_";
	char ch = level + '0';
	std::string file_name = s1 + ch + '.' + end;

	
	return file_name;
}


void Game::save_seed(int seed, std::ofstream& outfile)const {
	if (outfile.is_open()) {
		outfile << seed << std::endl;
	}
}


void Game::handle_file_not_valid(const int size) {
	char ch;
	level++;
	if (level == size) {
		gotoxy(0, 0);
		std::cout << "Not valid. please check the files." << std::endl;
		break_screen = true;
	}
	gotoxy(0, 0);
	std::cout << "Not valid. Press any key and Enter to continue to the next file: " << std::endl;
	std::cin >> ch;
	continue_screen = true;
}








	


