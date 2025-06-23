#include "position.h"
#include "board.h"
#include <windows.h>

// Static variable definition for enabling or disabling color.
bool Position::with_color = false; 


bool Position::is_silent = false; 


//check if the next step is valid for staying in bounderies 
bool Position::next_step_vailed()   
{
	if (x < 79 && x > 0 && y >= 0 && y < 24)
		return true;
	else 
		return false;

}
//Print space in x y
void Position::erase() {
	gotoxy(x, y);
	std::cout << " ";
}
// Draw char input
void Position::draw(char player) {
	if (!is_silent) {                   //draw only if it's not silent mode
		if (with_color) {               //change color my player
			change_color(player);
		}
		gotoxy(x, y);
		std::cout << player;
		if (with_color) {
			change_to_white();
		}
	}
}
// Moving object by the last direction or user command 
void Position::move(char player, int dir_x, int dir_y) {
		erase();
		
		x += dir_x;
		y += dir_y;
		if (!next_step_vailed()) {
			x -= dir_x;
			y -= dir_y;
		}
		draw(player);
}
//Chat_gpt finction to add colors
void Position::setColor(int color) {   
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}
//Handle the colors for the characters
void Position::change_color(char player) {
	if (player == '@' || player == '#') {
		setColor(FOREGROUND_RED); // red 
	}
	else if (player == 'M') {	
			setColor(FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE); //red color mario, background blue 
	}
	else if (player == 'o') {
		setColor(FOREGROUND_GREEN | FOREGROUND_BLUE); // turquoise
	}
	else if (player == 'x') {
		setColor(FOREGROUND_RED | FOREGROUND_BLUE); // purple
	}
	else if (player == 'X') {
		setColor(FOREGROUND_GREEN | FOREGROUND_RED); //yellow
	}
}
//Return to white color
void Position::change_to_white() {
	setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}