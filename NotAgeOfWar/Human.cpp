#include "Human.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Square.h"
#include "Fighter.h"
#include "Swordman.h"
#include "Catapult.h"
#include "Bowman.h"
#include <algorithm>
#include <map>
using namespace std;

bool minPriceHuman(string i, string j) { return (Fighter::data.at(i).at("Price") < Fighter::data.at(j).at("Price")); }

void Human::update(Square* square) {

	printf("%c[%dm", 0x1B, 33);

	cout << "gold : " << to_string(money) << endl;
	if (square->getFighterOn() == nullptr) {
		vector<string> classList;
		for (auto it = Fighter::unitNames.begin(); it != Fighter::unitNames.end(); it++) {
			classList.push_back(it->first);
		}
		sort(classList.begin(), classList.end(), minPriceHuman);
		if (money >= Fighter::data.at(classList.at(0)).at("Price")) {
			while (true) {
				string input = "";
				cout << "0 = end turn ; ";
				for (int i = 0; i < (int)classList.size(); i++) {
					cout << std::to_string(i + 1) << " = " << classList.at(i) << " (" << std::to_string(Fighter::data.at(classList.at(i)).at("Price")) << ") ; ";
				}
				cout << endl;
				cin >> input;

				if (input == "0") {
					cout << "next turn" << endl;
					break;
				}
				else {
					bool verif = false;
					for (int i = 0; i < (int)classList.size(); i++) {
						if (to_string(i + 1) == input) {
							if (money >= Fighter::data.at(classList.at(i)).at("Price")) {
								cout << classList.at(i) << " bought" << endl;
								money -= Fighter::data.at(classList.at(i)).at("Price");
								square->place(Fighter::getInstanceOf(classList.at(i), firstPlayer));
								verif = true;
								break;
							}
							else {
								cout << "not enough gold" << endl;
								break;
							}
						}
					}
					if (!verif) {
						cout << "unexistant unit" << endl;
					}
					else {
						break;
					}
				}
			}
		}
		else {
			std::cout << "can t buy anything" << endl;
		}
	}
	else {
		std::cout << "can t summon unit, castle is full" << endl;
	}
	getchar();
	std::cout << endl;
}