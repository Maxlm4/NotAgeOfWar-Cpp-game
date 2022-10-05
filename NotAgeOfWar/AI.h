#pragma once
#include "Player.h"
#include "Strategy.h"
#include "Square.h"

class AI : public Player
{
private:
	Strategy* strategy;

public :
	AI(int m, Strategy* s) : Player(m, -1) { strategy = s; }

	void update(Square* square);
};

