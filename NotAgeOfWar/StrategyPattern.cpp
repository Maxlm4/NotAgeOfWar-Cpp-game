#include "StrategyPattern.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Square.h"
#include "Fighter.h"
#include <algorithm>
#include <vector>
using namespace std;

void StrategyPattern::use(Square* square, int* money, vector<string> classList) {
	string unit = pattern.at(0);
	if (*money >= Fighter::data.at(unit).at("Price")) {
		cout << unit << " bought" << endl;
		*money -= Fighter::data.at(unit).at("Price");
		square->place(Fighter::getInstanceOf(unit, -1));
		pattern.pop_front();
		pattern.push_back(unit);
	}
	else {
		cout << "next turn" << endl;
	}
}