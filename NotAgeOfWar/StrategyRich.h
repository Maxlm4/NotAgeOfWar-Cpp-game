#pragma once
#include "Strategy.h"
#include "Square.h"

class StrategyRich : public Strategy
{
public :
	void use(Square*, int* money, vector<string> classList);
};

