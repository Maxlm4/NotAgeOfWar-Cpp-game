#include "Bowman.h"
#include "Player.h"
class Fighter;
#include <vector>
using namespace std;

int Bowman::cpt = 0;

Fighter* Bowman::getInstance(int firstPlayer) {
	return new Bowman(firstPlayer);
}

Fighter* Bowman::getInstance(int h, int i, bool s, int firstPlayer) {
	return new Bowman(h, i, s, firstPlayer);
}

bool Bowman::action1(vector<Square*>* field, int* pos, Player* p) {
	failActionOne = !attack(field, pos, p);
	return !failActionOne;
}

bool Bowman::action2(vector<Square*>* field, int* pos, Player* p) {
	return changePlace(field, pos);
}

bool Bowman::action3(vector<Square*>* field, int* pos, Player* p) {
	return true;
}
