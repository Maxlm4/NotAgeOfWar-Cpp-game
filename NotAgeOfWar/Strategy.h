#pragma once
#include "Square.h"
#include <map>
class Strategy
{
public :
	virtual void use(Square* square, int* money, vector<string> classList)=0;

	static map<string, Strategy*> strategies;
	static void initialize();
};

