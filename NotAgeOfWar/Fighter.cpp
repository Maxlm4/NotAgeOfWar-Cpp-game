#include "Fighter.h"
#include "Square.h"
#include "Swordman.h"
#include "Bowman.h"
#include "Catapult.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

map<string, map<string, int>> Fighter::data = map<string, map<string, int>>();
map<string, Fighter*> Fighter::unitNames = map<string, Fighter*>();
map<string, string> Fighter::unitSymbols = map <string,string>();

void Fighter::setStats() {
	price = Fighter::data.at(unitClass).at("Price");
	healthPoints = Fighter::data.at(unitClass).at("Health");
	attackPoints = Fighter::data.at(unitClass).at("Strength");
	range = Fighter::data.at(unitClass).at("Range");
	rangeSize = Fighter::data.at(unitClass).at("RangeSize");
	rangeZone = Fighter::data.at(unitClass).at("RangeZone");
}

void Fighter::setData(string fileName) {

	Fighter::data = map<string, map<string, int>>();

	map<string, int> dataList = map<string, int>();
	dataList.insert(pair<string, int>("Price", 0));
	dataList.insert(pair<string, int>("Health", 0));
	dataList.insert(pair<string, int>("Strength", 0));
	dataList.insert(pair<string, int>("Range", 0));
	dataList.insert(pair<string, int>("RangeSize", 0));
	dataList.insert(pair<string, int>("RangeZone", 0));

	unitNames.insert(pair<string, Fighter*>("swordman",new Swordman(1)));
	unitNames.insert(pair<string, Fighter*>("bowman",new Bowman(1)));
	unitNames.insert(pair<string, Fighter*>("catapult",new Catapult(1)));

	unitSymbols.insert(pair<string, string>("swordman", "s-S"));
	unitSymbols.insert(pair<string, string>("bowman", "b-B"));
	unitSymbols.insert(pair<string, string>("catapult", "c-C"));

	for (auto it = unitNames.begin(); it != unitNames.end(); it++) {
		Fighter::data.insert(pair<string, map<string, int>>(it->first, dataList));
	}

	ifstream infile(fileName);
	string line;
	while (getline(infile, line))
	{
		string param = line.substr(0, line.find('='));
		string data = line.substr(param.size() + 1, line.size());

		for (auto it = unitNames.begin(); it != unitNames.end(); it++) {
			if (param.compare(it->first + "Price") == 0) { Fighter::data.at(it->first).at("Price") = stoi(data); break; }
			else if (param.compare(it->first + "Health") == 0){ Fighter::data.at(it->first).at("Health") = stoi(data); break; }
			else if (param.compare(it->first + "Strength") == 0){ Fighter::data.at(it->first).at("Strength") = stoi(data); break; }
			else if (param.compare(it->first + "Range") == 0){ Fighter::data.at(it->first).at("Range") = stoi(data); break; }
			else if (param.compare(it->first + "RangeSize") == 0){ Fighter::data.at(it->first).at("RangeSize") = stoi(data); break; }
			else if (param.compare(it->first + "RangeZone") == 0){ Fighter::data.at(it->first).at("RangeZone") = stoi(data); break; }
		}
	}
}

Fighter* Fighter::getInstanceOf(string str, int firstPlayer) {
	if(unitNames.find(str) != unitNames.end()){ return unitNames.at(str)->getInstance(firstPlayer); }
	else { return nullptr; }
}

Fighter* Fighter::getInstanceOf(string str, int h, int i, bool s, int firstPlayer) {
	if (unitNames.find(str) != unitNames.end()){ return unitNames.at(str)->getInstance(h, i, s, firstPlayer); }
	else { return nullptr; }
}

//Essayer d'opti ça en condensant le code répété
bool Fighter::attack(vector<Square*>* field, int* pos, Player* p) {
	for (int target = *pos + range * firstPlayer; firstPlayer * target <= firstPlayer * ( *pos + firstPlayer * (range + rangeSize - 1)); target += firstPlayer) {
		if (target * firstPlayer <= firstPlayer * ((int)field->size() - 1 + firstPlayer * ((int)field->size() - 1)) / 2) {
			if (field->at(target)->getFighterOn() != nullptr) {
				if (field->at(target)->getFighterOn()->getFirstPlayer() != firstPlayer) {
					for (int victim = target; firstPlayer * victim < firstPlayer * (target + rangeZone * firstPlayer); victim += firstPlayer) {
						if (field->at(victim)->getFighterOn() != nullptr) {
							field->at(victim)->getFighterOn()->damage(attackPoints);
							cout << unitClass + " " + to_string(id) << " damaged " << field->at(victim)->getFighterOn()->getUnitClass() + " " + to_string(field->at(victim)->getFighterOn()->getId()) << endl;
							if (field->at(victim)->getFighterOn()->getHealth() <= 0) {
								if (field->at(victim)->getFighterOn()->getUnitClass() == "swordman" && unitClass == "swordman") {
									upgrade();
									cout << unitClass + " " + to_string(id) << " became stronger" << endl;
								}
								cout << field->at(victim)->getFighterOn()->getUnitClass() + " " + to_string(field->at(victim)->getFighterOn()->getId()) << " died" << endl;
								cout << "you won " << to_string(field->at(victim)->getFighterOn()->getPrice() / 2) << " gold" << endl;
								p->giveMoney(field->at(victim)->getFighterOn()->getPrice() / 2);
								field->at(victim)->place(nullptr);
							}
						}
					}
					return true;
				}
			}
			else if (field->at(target)->getBase() != nullptr) {
				field->at(target)->getBase()->damage(attackPoints);
				cout << unitClass << to_string(id) << "damaged enemy s castle " << endl;
			}
		}
		else {
			break;
		}
	}
	return false;
}

bool Fighter::changePlace(vector<Square*>* field, int* pos) {
	if ( firstPlayer * (*pos + firstPlayer) < firstPlayer * ((int)field->size() - 1 + firstPlayer * ((int)field->size() - 1)) / 2 ) {
		if (field->at(*pos + firstPlayer)->getFighterOn() == nullptr) {
			field->at(*pos + firstPlayer)->place(this);
			field->at(*pos)->place(nullptr);
			*pos += firstPlayer;
			cout << field->at(*pos)->getFighterOn()->getUnitClass() << " " << to_string(field->at(*pos)->getFighterOn()->getId()) << " moved to " << to_string(*pos) << endl;
			return true;
		}
	}
	return false;

}

bool Fighter::action1(vector<Square*>* field, int* pos, Player* p) { return false; }
bool Fighter::action2(vector<Square*>* field, int* pos, Player* p) { return false; }
bool Fighter::action3(vector<Square*>* field, int* pos, Player* p) { return false; }

