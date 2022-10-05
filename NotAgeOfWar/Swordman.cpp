#include "Swordman.h"
class Fighter;
#include <vector>
using namespace std;

int Swordman::cpt = 0;

Fighter* Swordman::getInstance(int firstPlayer) {
	return new Swordman(firstPlayer);
}

Fighter* Swordman::getInstance(int h, int i, bool s, int firstPlayer) {
	return new Swordman(h,i,s,firstPlayer);
}

bool Swordman::action1(vector<Square*>* field, int* pos, Player* p){
	if (super) {
		attack(field, pos, p);
		failActionOne = true;
		return false;
	}
	else {
		failActionOne = !attack(field, pos, p);
		return !failActionOne;
	}
}

bool Swordman::action2(vector<Square*>* field, int* pos, Player* p) {
	return changePlace(field, pos);
}

bool Swordman::action3(vector<Square*>* field, int* pos, Player* p) {
	return attack(field, pos, p);
}
