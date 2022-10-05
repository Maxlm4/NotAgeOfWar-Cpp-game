#pragma once

class Castle
{
private: 
	int health;
	int firstPlayer;

public:
	Castle(int h, int p) {
		health = h;
		firstPlayer = p;
	}

	int getHealth() {
		return health;
	}

	int getFirstPlayer() {
		return firstPlayer;
	}

	void damage(int d) {
		health -= d;
	}
};

