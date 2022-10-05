#include "Catapult.h"
#include "Player.h"
class Fighter;
#include <vector>
using namespace std;

int Catapult::cpt = 0;

Fighter* Catapult::getInstance(int firstPlayer) {
	return new Catapult(firstPlayer);
}

Fighter* Catapult::getInstance(int h, int i, bool s, int firstPlayer) {
	return new Catapult(h, i, s, firstPlayer);
}

bool Catapult::action1(vector<Square*>* field, int* pos, Player* p) {
	failActionOne = !attack(field, pos, p);
	return !failActionOne;
}

bool Catapult::action2(vector<Square*>* field, int* pos, Player* p) {
	return true;
}

bool Catapult::action3(vector<Square*>* field, int* pos, Player* p) {
	return changePlace(field, pos);
}
