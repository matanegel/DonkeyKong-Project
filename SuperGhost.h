#pragma once
#include "ghost.h"
#include "mario.h"


class SuperGhost : public Ghost
{
private:
	
public:
	SuperGhost(char symbol, int x, int y) : Ghost(symbol, x, y) {};

/*
לחשוב אם לעשות לה שהיא לא יכולה לטפס יותר מגובה 0
*/
	virtual void move()override;
	virtual bool check_probability_to_change_dir()const override{
	return false;
}
	
	void hunting_mario(); 
		
};



