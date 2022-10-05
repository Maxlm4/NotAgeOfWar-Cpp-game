#pragma once
using namespace std;
#include<vector>
#include<map>
class Player;
class Square;

class Fighter
{
protected:
	int price;
	int healthPoints;
	int attackPoints;
	int range; //minimum targettable range
	int rangeSize; //size of the range, ex range = 1 and rangeSize = 3, the targettable cases are 1, 2, 3
	int rangeZone; //how many cases are targetted from the first targetted case included, ex range = 1, rangeZone = 3, so fighters on 1, 2 and 3 will be targetted
	int firstPlayer;
	string unitClass;
	int id;
	bool super;
	bool failActionOne;

public:

	//getters
	int getPrice() {
		return price;
	}
	int getHealth() {
		return healthPoints;
	}
	int getStrength() {
		return attackPoints;
	}
	int getRange() {
		return range;
	}
	int getRangeSize() {
		return rangeSize;
	}
	int getRangeZone() {
		return rangeZone;
	}
	int getFirstPlayer() {
		return firstPlayer;
	}
	string getUnitClass() {
		return unitClass;
	}
	int getId() {
		return id;
	}
	bool getSuper() {
		return super;
	}
	bool getFailActionOne() {
		return failActionOne;
	}

	//setters
	void setHealth(int h) {
		healthPoints = h;
	}

	void upgrade() {
		super = true;
	}

	//modifiers
	void damage(int d) {
		healthPoints -= d;
	}

	static map<string, map<string, int>> data;
	static map<string, Fighter*> unitNames;
	static map<string, string> unitSymbols;

	virtual void setStats();
	static void setData(string fileName);
	static Fighter* getInstanceOf(string str, int firstPlayer);
	static Fighter* getInstanceOf(string str, int h, int i, bool s, int firstPlayer);
	virtual Fighter* getInstance(int firstPlayer)=0;
	virtual Fighter* getInstance(int h, int i, bool s, int firstPlayer) = 0;

	bool attack(vector<Square*>* field, int* pos, Player* p);
	bool changePlace(vector<Square*>* field, int* pos);
	virtual bool action1(vector<Square*>* field, int* pos, Player* p);
	virtual bool action2(vector<Square*>* field, int* pos, Player* p);
	virtual bool action3(vector<Square*>* field, int* pos, Player* p);
};

