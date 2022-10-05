#pragma once
#include "Square.h"

class Player
{
protected:
	int money;
	int firstPlayer;

public:

	Player(int m, int f) {
		money = m;
		if (f >= 0) {
			firstPlayer = 1;
		}
		else {
			firstPlayer = -1;
		}
		
	}

	int getMoney() {
		return money;
	}

	int getFirstPlayer() {
		return firstPlayer;
	}

	void giveMoney(int m) {
		money += m;
	}

	virtual void update(Square* square) = 0;
};

