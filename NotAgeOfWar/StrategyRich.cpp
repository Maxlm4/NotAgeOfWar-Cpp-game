#include "StrategyRich.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Square.h"
#include "Fighter.h"
#include <algorithm>
#include <vector>
using namespace std;

bool maxPrice(string i, string j) { return (Fighter::data.at(i).at("Price") > Fighter::data.at(j).at("Price")); }

void StrategyRich::use(Square* square, int* money, vector<string> classList) {
	sort(classList.begin(), classList.end(), maxPrice);
	for (int i = 0; i < (int)classList.size(); i++) {
		if (*money >= Fighter::data.at(classList.at(i)).at("Price")) {
			cout << classList.at(i) << " bought" << endl;
			*money -= Fighter::data.at(classList.at(i)).at("Price");
			square->place(Fighter::getInstanceOf(classList.at(i), -1));
			break;
		}
	}

}