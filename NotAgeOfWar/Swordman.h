#pragma once
#include "Fighter.h"
#include "Player.h"
class Square;
#include <vector>
using namespace std;

class Swordman : public Fighter
{
private:
	static int cpt;

public:
	Swordman(int firstPlayer) {
		unitClass = "swordman";
		setStats();
		this->firstPlayer = firstPlayer;
		id = cpt;
		cpt++;
		super = false;
	}

	Swordman(int h, int i, bool s, int f)
	{
		unitClass = "swordman";
		setStats();
		healthPoints = h;
		firstPlayer = f;
		id = i;
		super = s;
		cpt++;
	}

	Fighter* getInstance(int firstPlayer);
	Fighter* getInstance(int h, int i, bool s, int firstPlayer);

	bool action1(vector<Square*>* field, int* pos, Player* p);
	bool action2(vector<Square*>* field, int* pos, Player* p);
	bool action3(vector<Square*>* field, int* pos, Player* p);

	static void setCpt(int i) {
		cpt = i;
	}
};

