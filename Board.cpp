
#include <cstring>
#include <iostream>
#include <windows.h>
#include "board.h"
#include <fstream>
#include <vector>
#include "Ghost.h"
#include "SuperGhost.h"


// Checking if ladder is under character position return the distance from the ladder
int Board::check_ladder_is_under(Position& poss) {
	const int x = poss.get_x();
	const int y = poss.get_y();
	if (y < MAX_Y - 2) {
		char ch1 = get_char(x, y + 1);
		char ch2 = get_char(x, y + 2);
		if (ch1 == 'H')
			return 1;
		else if (ch2 == 'H')
			return 2;
		else
			return 0;
	}
	return 0;
}
// Return char from OriginalBoard in specific x,y
const char Board::get_char(int x, int y) const {
	return originalBoard[y][x];
}
// Return char from CurrentBoard in specific x,y
const char Board::get_char_cb(int x, int y) {
	return currentBoard[y][x];
}
// Check if floor characters under specific position return type (char)
char Board::floor_under_barrel(const Position& poss) {
	const int x = poss.get_x();
	const int y = poss.get_y();
	char ch = get_char(x, y + 1);
	return ch;
}
// Check if floor characters under specific position return type (bool)
bool Board::floor_is_under(Position& poss) const{
	const int x = poss.get_x();
	const int y = poss.get_y();
	char ch = get_char(x, y + 1);
	if (ch == '=' || ch == '<' || ch == '>' || ch == '^') {
		return true;
	}
	else {
		return false;
	}
}
bool Board::floor_is_under(Position&& poss) const {
	const int x = poss.get_x();
	const int y = poss.get_y();
	char ch = get_char(x, y + 1);
	if (ch == '=' || ch == '<' || ch == '>' || ch == '^') {
		return true;
	}
	else {
		return false;
	}
}
// Check if mario in board borders return type (bool)
bool Board::in_border_x() {
	Position& curr_pos = mario.get_mario_pos();
	const int mario_x = curr_pos.get_x();
	if (mario_x < 2 || mario_x > 77)  {
		return false;
	}
	else {
		return true;
	}


}
// Check if mario facing a wall return (bool)
bool Board::check_wall_hit() {
	if (in_border_x() == false || in_border_y() == false) {
		mario.stand();
		return true;
	}
	else
		return false;
};
// Check if position is standing on ladder character
bool Board::is_ladder(Position& poss) {
	const int poss_x = poss.get_x();
	const int poss_y = poss.get_y();
	if (originalBoard[poss_y][poss_x] == 'H')
		return true;
	else
		return false;
}
// Check if it is the last level of ladder for jumping above floor
bool Board::is_last_level_of_ladder(Position poss) {
	const int poss_x = poss.get_x();
	const int poss_y = poss.get_y();
	switch (originalBoard[poss_y - 1][poss_x]) {
	case '=':
	case '<':
	case '>':
			return true;
	default:
		return false;
	}
}
// check mario position in border Y
bool Board::in_border_y() {
	Position curr_pos = mario.get_mario_pos();
	const int mario_y = curr_pos.get_y();
	// maybe to change 0 to 1 || 2
	if (mario_y < 0 || mario_y > 23)  {
		return false;
	}
	else {
		return true;
	}
}
// Update mario character in CurrentBoard and Update the prev position to originalBoard character 
bool Board::update_mario_poss(Position& prev)
{
	bool barrel_hit = false;
	const int prev_x = prev.get_x();
	const int prev_y = prev.get_y();
	Position curr_pos = mario.get_mario_pos();
	const int mario_x = curr_pos.get_x();
	const int mario_y = curr_pos.get_y();
	currentBoard[prev_y][prev_x] = originalBoard[prev_y][prev_x];
	currentBoard[mario_y][mario_x] = mario.get_mario_char();
	return true;
}
// Move barrel by the direcition of the floor
void Board::move_barrel(Barrel& b) {
	char ch = floor_under_barrel(b.get_poss());
	switch (ch) {
	case '<':
		b.left();
		break;
	case '>':
		b.right();
		break;
	case ' ':
		b.fall();
		break;
	case '^':
		b.random_dir();
		b.set_prev_move();
		b.default_move();
		break;
	default:
		b.default_move();
	}
	update_barrel_poss(b);
}
// Update barrel character in CurrentBoard and Update the prev position to originalBoard character 
bool Board::update_barrel_poss(Barrel& b)
{
	Position curr_pos = b.get_poss();
	const int barrel_x = curr_pos.get_x();
	const int barrel_y = curr_pos.get_y();
	const int prev_x = barrel_x - b.get_dir_x();
	const int prev_y = barrel_y - b.get_dir_y();
	currentBoard[prev_y][prev_x] = originalBoard[prev_y][prev_x];
	currentBoard[barrel_y][barrel_x] = b.get_symbol();
	return true;
}
// Checking mario in fall if falling more then 5 levels, mario = dead
bool Board::check_mario_in_fall() {
	Position m_poss = mario.get_mario_pos();
	static int fall_lvl = 0;

	if (!floor_is_under(m_poss) && !is_ladder(m_poss) && !mario.get_jumping_flag()) {
		mario.fall();
		fall_lvl++;
	}
	if (fall_lvl >= 5 && floor_is_under(m_poss)) {
		fall_lvl = 0;
		mario.set_alive(false);
		mario.decrease_lives();
		//restart_level();
		return true;
	}
	else if (floor_is_under(m_poss)) {
		fall_lvl = 0;
	}
	return false;
}
// Check if there is a floor under barrel
bool Board::floor_under_b(char under) {
	switch (under) {
	case '<':
	case '>':
	case '=':
	case '^':
		return true;
	default:
		return false;
	}
}
// Throwing a barrel every FRAME*time_frame
bool Board::timer_throw_b(int time_frame) {
	timer_throwing_b++;

	if (timer_throwing_b == time_frame) {
		barrel.push_back(Barrel(kong_position_x, kong_position_y));
		timer_throwing_b = 0;
		return true;
	}
	return false;
}
// Print the currentBoard on screen
void Board::print() {
	std::cout << currentBoard[0] << '\n';
	update_legend();
}

// Reset the currentBoard to originalBoard
void Board::reset() {
	for (int i = 0; i < MAX_Y; i++) {
		memcpy(currentBoard[i], originalBoard[i], MAX_X + 1);
	}
}
// Checking conditions when 'w' was pressed (if need to jump || climb)
void Board::up_is_pressed(Position& poss)
{
	if (is_ladder(poss)) {
		
		if (is_last_level_of_ladder(poss)) {
			mario.climb(-2);
		}
		else
			mario.set_mario_dir_y(-1);
	}
	else {
		if (floor_is_under(poss)) {
			mario.jump(mario.get_mario_dir());
		}
	}
}
// Print originalBoard[poss.y][poss.x] character 
void Board::print_prev_char(Position& poss) {
	int x = poss.get_x();      
	int y = poss.get_y();
	char ch = originalBoard[y][x];
	if (ch == 'p' && mario.get_hammer_flag()) {
		ch = ' ';
		set_char_ob(x, y, ' ');
	}
	poss.draw(ch);
}
// Restart level return all parameters to defualt values, decrease life. restarting board.
void Board::restart_level() {
	mario.set_starting_pos(mario.get_start_x(),mario.get_start_y());
	
	//mario.decrease_lives();
	//decrease_score();
	mario.reset_mario();
	clear_barrels();
	for (auto& ghost : ghost_vec) {
		ghost->reset_poss_after_strike();
		ghost->set_climbing(false);
		ghost->set_climbing_down(false);
	}
	timer_throwing_b = 0;

	gotoxy(0, 0);
	reset();
	if (!silent) {
		print();
	}
}
// Doing next move bassed on char input
void Board::next_mario_move(char ch_pressed) {
	switch (ch_pressed) {
	case UP:
		up_is_pressed(mario.get_mario_pos());
		break;
	case STAND:
		mario.stand();
		break;
	case LEFT:
		mario.left();
		break;
	case RIGHT:
		mario.right();
		break;
	case DOWN:
		mario.climb(check_ladder_is_under(mario.get_mario_pos()));
		break;
	}

}
// Function that managing all the throwing of the barrels, check fall_level, explosion, etc.
void Board::throw_barrel() {
	bool explode = false; // Flag if needed to explode barrel
	bool test_timer = timer_throw_b(THROWING_TIMER); // Throwing new barrel every 50 frames, change on_screen = true

	// Loop for moving\throwing the barrels in the array
	for (int itr = 0; itr < barrel.size(); itr++) {

		bool floor_under = floor_under_b(floor_under_barrel(barrel[itr].get_poss()));

		// If there is a floor and depth is bigger then 8 then explode barrel
		if (floor_under && barrel[itr].get_depth() >= 8) {
			explode = explode_barrel(barrel[itr], itr, mario);

			if (mario.get_alive() == false) {
				break;
			}
		}
		// If barrel didnt explode then move the barrel
		else {
			// If the falling depth is less then 8 and floor under barrel then reset the fal
			if (floor_under) {
				barrel[itr].reset_depth();
			}
			Position prev_barrel = barrel[itr].get_poss();
			move_barrel(barrel[itr]);
			print_prev_char(prev_barrel);
		}

		if (barrel[itr].get_poss().get_x() <= 0 || barrel[itr].get_poss().get_x() >= 79) {
			barrel.erase(barrel.begin() + itr);
		}
	}
}

// Function that explode Barrel& and check if mario is near explosion
bool Board::explode_barrel(Barrel& b, int b_itr, Mario& mario) {
	Position b_poss = b.get_poss();
	int x_b = b_poss.get_x();
	int y_b = b_poss.get_y();

	Position& m_poss = mario.get_mario_pos();
	int x_m = m_poss.get_x();
	int y_m = m_poss.get_y();

	b.explode_effect();
	// If mario distance less then 2 then mario dead
	if (abs(x_m - x_b) <= MAX_EXPLODING_RANGE && abs(y_m - y_b) <= MAX_EXPLODING_RANGE) {
		mario.set_alive(false);
	}

	barrel.erase(barrel.begin() + b_itr);

	return true;
}
//Load the board to the original board array from the file 
void Board::load(const std::string& filename) {
	if (!silent) {
	system("cls");
	}
	std::ifstream screen_file(filename);
	Ghost* ghost;
	int curr_row = 0;
	int curr_col = 0;
	char c;
	mario.reset_amount();
	board_is_valid = true;

	while (!screen_file.get(c).eof() && curr_row < MAX_Y) {
		if (c == '\n') {
			if (curr_col < MAX_X) {
				/*// add spaces for missing cols
#pragma warning(suppress : 4996) // to allow strcpy
				strcpy(originalBoard[curr_row] + curr_col, std::string(MAX_X - curr_col - 1, ' ').c_str());

			++curr_row;
			curr_col = 0;
			continue;*/
				board_is_valid = false;
			}
				++curr_row;
				curr_col = 0;
				continue;
		}
		if (curr_col <= MAX_X) {
			// handle special chars
			if (c == '@') {
				mario.increase_amount();
				c = ' ';
				mario.save_and_set_starting_poss(curr_col, curr_row);
			}
			else if (c == 'x'){
				c = ' ';
				 ghost = new Ghost('x', curr_col, curr_row);
				ghost_vec.push_back(ghost);
			}
			else if (c == 'X') {
				c = ' ';
				ghost = new SuperGhost('X', curr_col, curr_row);
				ghost_vec.push_back(ghost);
			}
			else if (c == '&') {
				kong_position_x = curr_col;
				kong_position_y = curr_row;
			}
			else if (c == 'L') {
				L_x = curr_col;
				L_y = curr_row;
			}

			originalBoard[curr_row][curr_col++] = c;
		}
	}


	int last_row = (curr_row < MAX_Y ? curr_row : MAX_Y - 1);
	// add a closing frame
	// first line
#pragma warning(suppress : 4996) // to allow strcpy
	//strcpy(originalBoard[0], std::string(MAX_X, 'W').c_str());
	originalBoard[0][MAX_X] = '\n';
	// last line
#pragma warning(suppress : 4996) // to allow strcpy
	//strcpy(originalBoard[last_row], std::string(MAX_X, 'W').c_str());
	originalBoard[last_row][MAX_X] = '\0';
	// first col + last col
	for (int row = 1; row < last_row; ++row) {
		//originalBoard[row][0] = 'W';
		//originalBoard[row][MAX_X] = 'W';
		originalBoard[row][MAX_X] = '\n';
	}

	if (last_row < MAX_Y - 1) {
		board_is_valid = false;
	}
	
}
//Handle the movement of the ghost 
void Board::move_ghost() {
	int curr_x, curr_y;

	for (Ghost* curr_ghost : ghost_vec) {
		Position tmp_curr_poss(curr_ghost->get_poss());
		curr_x = curr_ghost->get_poss().get_x();
		curr_y = curr_ghost->get_poss().get_y();
		currentBoard[curr_y][curr_x] = originalBoard[curr_y][curr_x];
		
		curr_ghost->move();
		Position new_curr_poss = curr_ghost->get_poss();
		if (is_ladder(new_curr_poss) && curr_ghost->get_climbing_down() == false) {
			if(mario.get_mario_pos().get_y() < curr_ghost->get_poss().get_y())
			curr_ghost->set_climbing(true);
		}
		else if (check_ladder_is_under(new_curr_poss) && curr_ghost->get_climbing() == false) {
			if(mario.get_mario_pos().get_y() > curr_ghost->get_poss().get_y())
			curr_ghost->set_climbing_down(true);
		}
		else if(floor_is_under(curr_ghost->get_poss())) {
			curr_ghost->set_climbing(false);
			curr_ghost->set_climbing_down(false);
		}
		print_prev_char(tmp_curr_poss);
		curr_x = curr_ghost->get_poss().get_x();
		curr_y = curr_ghost->get_poss().get_y();
		currentBoard[curr_y][curr_x] = curr_ghost->get_symbol();
		// Check if(0.05% || floor edge) then change direction
		(need_change_dir(*curr_ghost));
	}

}
//Print the legend on top left 
void Board::update_legend() {
	gotoxy(L_x, L_y);
	std::cout << "Lives: " << mario.get_lives();
	gotoxy(L_x, L_y + 1 );
	std::cout << "Score: " << get_score();
	gotoxy(L_x, L_y + 2);
	std::cout << "floor: " << get_floor();

}
//Checking if the ghost need to change direction
void Board::need_change_dir( Ghost& g) {
	Position curr_next;
	bool need_to_change = false;
	curr_next.set_xy((g.get_poss().get_x() + g.get_dir_x()), g.get_poss().get_y());
	if (g.check_probability_to_change_dir())
		need_to_change = true;
	else if (!floor_is_under(curr_next))
		need_to_change = true;
	else if (currentBoard[curr_next.get_y()][curr_next.get_x()] == 'x') {
		for (Ghost* other_ghost : ghost_vec) {
			if (other_ghost->get_poss() == curr_next) {
				other_ghost->set_dir_x((-1) * other_ghost->get_dir_x());
				break;
			}
		}
			need_to_change = true;
	}
	else if (curr_next.get_x() > 78 || curr_next.get_x() < 1)
		need_to_change = true;
	
	if (need_to_change) {
		g.set_dir_x((-1) * g.get_dir_x());
	}
}
void Board::clear_ghost_vec() {
	free_ghost_vec();
	ghost_vec.clear();
}

void Board::clear_barrels() {
	barrel.clear();
}

//handle the hammer attack and chack if there is a ghost or barrel
void Board::hammer_attack() {
	if (mario.get_hammer_flag()) {
		int mario_x = mario.get_mario_pos().get_x();
		int mario_y = mario.get_mario_pos().get_y();
		int mario_x_dir = mario.get_mario_dir();

		
		for (int j = 1; j <= 3; j++) {
			if (currentBoard[mario_y][mario_x + (mario_x_dir * j)] == 'o') {
				for (int i = 0; i < barrel.size(); i++) {
					int barrel_x = barrel[i].get_poss().get_x();
					int barrel_y = barrel[i].get_poss().get_y();
					if (barrel_x == (mario_x + (mario_x_dir * j)) && barrel_y == mario_y) {
						barrel.erase(barrel.begin() + i);
						currentBoard[barrel_y][barrel_x] = originalBoard[barrel_y][barrel_x];
						increase_score();
						break;
					}
				}

			}
			if (currentBoard[mario_y][mario_x + (mario_x_dir * j)] == 'x' || currentBoard[mario_y][mario_x + (mario_x_dir * j)] == 'X') {
				for (int i = 0; i < ghost_vec.size(); i++) {
					int curr_ghost_x = ghost_vec[i]->get_poss().get_x();
					int curr_ghost_y = ghost_vec[i]->get_poss().get_y();
					if (curr_ghost_x == (mario_x + (mario_x_dir * j)) && curr_ghost_y == mario_y) {
						ghost_vec.erase(ghost_vec.begin() + i);
						currentBoard[curr_ghost_y][curr_ghost_x] = originalBoard[curr_ghost_y][curr_ghost_x];
						increase_score();
						break;
					}
				}
			}
			hammer_effect(mario_x + (mario_x_dir * j), mario_y);
		}
	}
}
//Set a char in the original board
void Board::set_char_ob(int x, int y, char new_ch) {
	originalBoard[y][x] = new_ch;
}
//Checking if the board is valid
bool Board::check_board_is_valid() {
	bool floor_valid = true;
	bool queen_is_in_the_air = false;
	bool kong_is_in_the_air = false;
	int queen_on_board = 0;
	int kong_on_board = 0;
	int ghost_not_valid = 0;
	char under_ch;

	char ch;
	for (int row = 0; row < MAX_Y; row++) {
		for (int col = 0; col < MAX_X; col++) {
			ch = originalBoard[row][col];

			if (row == MAX_Y - 1 && col >= 1 && col <= 78) {
				if (ch != '=' && ch != '<' && ch != '>' && ch != '^') {
					floor_valid = false;
				}
			}

			switch (ch) {
			case '$':
				queen_on_board++;
				under_ch = originalBoard[row + 1][col];
				if (under_ch != '=' && under_ch != '<' && under_ch != '>' && under_ch != '^') {
					queen_is_in_the_air = true;
				}
				break;
			case '&':
				kong_on_board++;
				under_ch = originalBoard[row + 1][col];
				if (under_ch != '=' && under_ch != '<' && under_ch != '>' && under_ch != '^') {
					kong_is_in_the_air = true;
				}
				break;
			case 'Q':
				if (col < 79 && col > 0) {
					board_is_valid = false;
				}
				break;
			default:
				if (!valid_char(ch)) {
					board_is_valid = false;
				}
			}
		}
	}
	for (Ghost* curr_g : ghost_vec) {
		if (!floor_is_under(curr_g->get_poss())) {
			ghost_not_valid++;
		}
	}
	return check_and_print_errors(floor_valid, queen_on_board,
		kong_on_board, ghost_not_valid, queen_is_in_the_air, kong_is_in_the_air);
}
// This function checks the validity of the game board elements and prints error messages if any issues are found
bool Board::check_and_print_errors(bool floor_valid, int qOnB, int kOnB, int gOnB, bool qOnAir, bool kOnAir) {
	bool board_valid = true;
	int y = 1;

	if (!board_is_valid) {
		gotoxy(0, ++y);
		board_valid = false;
		std::cout << "The board is not valid.";
	}
	if (!floor_valid) {
		gotoxy(0, ++y);
		board_valid = false;
		std::cout << "The floor not valid.";
	}
	if (mario.get_amount_of_mario() != 1) {
		gotoxy(0, ++y);
		board_valid = false;
		std::cout << "Mario not valid, there are: "<< mario.get_amount_of_mario() << " marios on board.";
	}
	if (qOnB != 1) {
		gotoxy(0, ++y);
		board_valid = false;
		std::cout << "Queen not valid, there are: "<< qOnB << " queens on board.";
	}
	if (qOnAir) {
		gotoxy(0, ++y);
		board_valid = false;
		std::cout << "Queen is in the air.";
	}
	if (kOnB != 1) {
		gotoxy(0, ++y);
		board_valid = false;
		std::cout << "Kong not valid, there are: "<< kOnB << " kongs on board.";
	}
	if (kOnAir) {
		gotoxy(0, ++y);
		board_valid = false;
		std::cout << "Kong is in the air." ;
	}
	if (gOnB != 0) {
		gotoxy(0, ++y);
		board_valid = false;
		std::cout << "Ghost not valid, there are: "<< gOnB << " ghost not valid.";
	}

	return board_valid;
}
// Simulates the effect of a hammer hitting a position on the game board
void Board::hammer_effect(int x, int y) {
	// Check if the position (x, y) is within the bounds of the game board
	if (x < 80 && x > 0) {
		Position tmp(x, y);
		char c = originalBoard[y][x];
		tmp.draw('#');
		Sleep(2);
		tmp.draw(c);
	}
}

void Board::free_ghost_vec() {
	for (Ghost* curr_ghost : ghost_vec) {
		delete curr_ghost;
	}
}

void Board::increase_score() {
	score += INCREASE_SCORE;
	curr_board_score += INCREASE_SCORE;
	if (!silent) {
		gotoxy(L_x, L_y + 1);
		std::cout << "Score: " << get_score();
	}
}

bool Board::valid_char(char ch) {
	if (ch == '@' || ch == '=' || ch == '<' || ch == '>' || ch == '^' || ch == 'Q' || ch == '&' || ch == 'x' || ch == 'X' || ch == '&' || ch == 'L' || ch == 'H' || ch == 'p' || ch == ' ') {
		return true;
	}
	else {
		return false;
	}
}