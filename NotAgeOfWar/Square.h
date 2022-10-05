#pragma once
class Fighter;
class Castle;
#include "Fighter.h"
#include "Castle.h"

class Square
{
private:
	Castle* base;
	Fighter* fighterOn;

public:

	Square() { base = nullptr; fighterOn = nullptr; }

	Square(Castle* c) { fighterOn = nullptr; base = c; }

	//getter
	Castle* getBase() {
		return base;
	}
	Fighter* getFighterOn() {
		return fighterOn;
	}

	//setter
	void place(Fighter* fighter) {
		fighterOn = fighter;
	}

	void destroy() {
		base = nullptr;
	}
};