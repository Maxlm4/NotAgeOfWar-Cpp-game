#pragma once
#include "Player.h"
#include "Square.h"

class Human : public Player
{
public:
	Human(int m, int f) : Player(m, f) {	}

	void update(Square* square);
};

