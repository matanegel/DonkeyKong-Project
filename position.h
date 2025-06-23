#pragma once
#include <iostream> 
#include <windows.h> 
#include <conio.h> 
#include "utils.h" 


class Position {
private:
	int x, y;
	static bool with_color;
	static bool is_silent;
	
public:
	Position() : Position(1, 23) {};
	Position(int x, int y) : x(x), y(y) {};

	const int get_x() const { return x; };
	const int get_y() const { return y; };

	bool next_step_vailed();
	void print_coord() { std::cout << "( " << x << "," << y << ")" << std::endl; };
	void set_xy(int x, int y) { Position::x = x; Position::y = y; }
	void draw(char player);
	void erase();
	void move(char player, int dir_x, int dir_y);	
	bool operator==(const Position& other) const {
		return (x == other.x && y == other.y);
	}
	void setColor(int color);
	void change_color(char player);
	void change_to_white();
	void set_color_definition() {
		if (with_color) {
			with_color = false;
		}
		else {
			with_color = true;
		}
	}
	void set_silent() { is_silent = true; }
};
