#include "mario.h" 
#include "board.h"


void Mario::set_mario_board(Board* b)  
{
	pb = b;
};
// Move mario one step to the right
void Mario::right() { 
	mario_dir = RIGHT_MOVE;
	if (next_move_secure(mario_dir, STAND_MOVE)) {
		 mario_pos.move(mario, mario_dir, STAND_MOVE);
	}
}
// Move mario one step to the left
void Mario::left()  { 
	mario_dir = LEFT_MOVE;
	if (next_move_secure(mario_dir, STAND_MOVE)) {
		 mario_pos.move(mario, mario_dir, STAND_MOVE);
	}
}
// Putting mario in stand position
void Mario::stand() { mario_dir = STAND_MOVE, mario_dir_y = STAND_MOVE; mario_pos.move(mario, mario_dir, STAND_MOVE); };
// Move mario default direction
void Mario::move_mario() { 
	if (next_move_secure(mario_dir, STAND_MOVE)) {
		if (pb->is_last_level_of_ladder(mario_pos) && is_climbing) {
			climb(-2);
			mario_dir_y = 0;
			
		}
		else{
			mario_pos.move(mario, mario_dir, mario_dir_y);
			
		}
		update_climbing_flag();
		if (has_an_hammer) {
			set_super_mario();
		}
	}
	
};
// Move mario default x and input of y
void Mario::move_m(int dir_y) {
	if (next_move_secure(mario_dir, dir_y)) {
		mario_pos.move(mario, mario_dir, dir_y);
		if (has_an_hammer) {
			set_super_mario();
		}
	}
}
// Check if the move is a special character ('$'||'o')
bool Mario::next_move_secure(int dir_x, int dir_y) {
	int m_x = mario_pos.get_x();
	int m_y = mario_pos.get_y();
	const char mario_place = pb->get_char_cb(m_x, m_y);
	const char next_step_char = pb->get_char_cb(m_x + dir_x, m_y + dir_y);

	if (next_step_char == '$') {
		won = true;
		return true;
	}

	if (mario_place == 'o' || next_step_char == 'o' || next_step_char == 'x' || mario_place == 'x' || next_step_char == 'X' || mario_place == 'X') {
		alive = false;
		decrease_lives();
		return false;
	}
	if (next_step_char == 'p') {
		has_an_hammer = true;
	}
	return true;
}
// Climbing ladder function
void Mario::climb(int dir_y) {
	mario_pos.move(mario, STAND_MOVE, dir_y);

}
// Mario falling function
void Mario::fall() {
	mario_dir = DOWN_MOVE;
	mario_pos.move(mario, STAND_MOVE, mario_dir);
	stand();
}
// decrease the life of mario every death
void Mario::decrease_lives() {
	lives -= 1;
}
// return live by const
int Mario::get_lives() const { return lives; }
// Jump function 
void Mario::jump(int mario_dir){
	int poss_y = get_mario_pos().get_y();
	if (poss_y > 1) {
		// Allow Mario to jump up to twice
		if (jumpCounter < 2) {
			move_m(UP_MOVE); // Move mario up 
			is_jumping = true; // Set jumping state
			jumpCounter++;
		}
		// Simulate downward movement after upward jump
		else if (jumpCounter < 4) {
			move_m(DOWN_MOVE); // Move mario down
			jumpCounter++;

		}
		// Reset jump state after completing the jump cycle
		if (jumpCounter == 4) {
			jumpCounter = 0;
			is_jumping = false;
		}
	}
}
//reset mario after strike or win
void Mario::reset_mario() {
	jumpCounter = NONE;
	is_jumping = false;
	alive = true;
	won = false;
	mario_dir = STAND_MOVE;
	mario_dir_y = STAND_MOVE;
	has_an_hammer = false;
	mario = '@';
}

void Mario::update_climbing_flag()
{
	if (mario_dir_y == -1) {
		is_climbing = true;
	}
	else {
		is_climbing = false;
	}
}








