#include "AI.h"
#include "Square.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

bool minPriceAI(string i, string j) { return (Fighter::data.at(i).at("Price") < Fighter::data.at(j).at("Price")); }

void AI::update(Square* square) {
	printf("%c[%dm", 0x1B, 33);

	cout << "gold : " << to_string(money) << endl;
	if (square->getFighterOn() == nullptr) {
		vector<string> classList = vector<string>();
		for (auto it = Fighter::unitNames.begin(); it != Fighter::unitNames.end(); it++) {
			classList.push_back(it->first);
		}
		sort(classList.begin(), classList.end(), minPriceAI);
		if (money >= Fighter::data.at(classList.at(0)).at("Price")) {
			cout << "0 = end turn ; ";
			for (int i = 0; i < (int)classList.size(); i++) {
				cout << std::to_string(i + 1) << " = " << classList.at(i) << " (" << std::to_string(Fighter::data.at(classList.at(i)).at("Price")) << ") ; ";
			}
			cout << endl;
			strategy->use(square, &money, classList);
		}
		else {
			cout << "can t buy anything" << endl;
		}
	}
	else {
		cout << "can t summon unit, castle is full" << endl;
	}
	getchar();
	cout << endl;
}