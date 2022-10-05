#pragma once
#include "Strategy.h"
#include <deque>
using namespace std;

class StrategyPattern : public Strategy
{
private :
	deque<string> pattern;


public:

	StrategyPattern() {
		pattern.push_back("catapult");
		pattern.push_back("bowman");
		pattern.push_back("bowman");
	}

	void use(Square*, int* money, vector<string> classList);
};

