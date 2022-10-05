#pragma once
using namespace std;
#include <vector>
#include "Square.h"
#include "Player.h"
#include "Human.h"
#include "Swordman.h"
#include "Bowman.h"
#include "Catapult.h"
#include "AI.h"
#include "StrategyRich.h"
#include "StrategyPattern.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
class Square;

class Field
{
protected:
	string gamemode;
	vector<Square*> field;
	Player* leftPlayer;
	Player* rightPlayer;
	int goldEachTurn;
	string content;
	int turn;
	int nbTurn;

public:

	Field(string gamemode) {
		field = vector<Square*>();
		nbTurn = 1;
		turn = 1;
		Swordman::setCpt(0);
		Bowman::setCpt(0);
		Catapult::setCpt(0);
		this->gamemode = gamemode;
		int size = 0;
		int castlesHealth = 0;
		int moneyAtBeginning = 0;
		content = "";
		ifstream infile("config.txt");
		string line;
		while (getline(infile, line))
		{
			content += line + "\n";
			string param = line.substr(0, line.find('='));
			string data = line.substr(param.size() + 1, line.size());

			if (param.compare("size") == 0) {
				size = stoi(data);
			}
			else if (param.compare("moneyAtBeginning") == 0) {
				moneyAtBeginning = stoi(data);
			}
			else if (param.compare("goldEachTurn") == 0) {
				goldEachTurn = stoi(data);
			}
			else if (param.compare("castleHealth") == 0) {
				castlesHealth = stoi(data);
			}
		}

		leftPlayer = new Human(moneyAtBeginning, 1);
		if (gamemode == "pvp") {
			rightPlayer = new Human(moneyAtBeginning, -1);
		}
		else {
			if (Strategy::strategies.find(gamemode) != Strategy::strategies.end()) {
				rightPlayer = new AI(moneyAtBeginning, Strategy::strategies.at(gamemode));
			}
			else {
				rightPlayer = new AI(moneyAtBeginning, new StrategyRich());
			}
		}

		for (int i = 0; i < size; i++) {
			if (i == 0) {
				field.push_back(new Square(new Castle(castlesHealth, 1)));
			}
			else if (i == size - 1) {
				field.push_back(new Square(new Castle(castlesHealth, -1)));
			}
			else {
				field.push_back(new Square());
			}
		}
	}

	Field() {
		field = vector<Square*>();
		int size = 0;
		int firstPlayerMoney = 0;
		int secondPlayerMoney = 0;
		Swordman::setCpt(0);
		Bowman::setCpt(0);
		Catapult::setCpt(0);

		ifstream infile("save.txt");
		string line;
		while (getline(infile, line))
		{
			string param = line.substr(0, line.find('='));
			string data = line.substr(param.size() + 1, line.size());

			if (param.compare("size") == 0) {
				size = stoi(data);
				break;
			}
		}

		for (int i = 0; i < size; i++) {
			if (i == 0) {
				field.push_back(new Square(new Castle(0, 1)));
			}
			else if (i == size - 1) {
				field.push_back(new Square(new Castle(0, -1)));
			}
			else {
				field.push_back(new Square());
			}
		}

		while (getline(infile, line))
		{
			string param = line.substr(0, line.find('='));
			string data = line.substr(param.size() + 1, line.size());

			if (param.compare("firstPlayerMoney") == 0) {
				firstPlayerMoney = stoi(data);
			}
			else if (param.compare("secondPlayerMoney") == 0) {
				secondPlayerMoney = stoi(data);
			}
			else if (param.compare("firstPlayerCastle") == 0) {
				field.at(0)->getBase()->damage(-stoi(data));
			}
			else if (param.compare("secondPlayerCastle") == 0) {
				field.at((int)field.size() - 1)->getBase()->damage(-stoi(data));
			}
			else if (param.compare("turn") == 0) {
				turn = stoi(data);
			}
			else if (param.compare("nbTurn") == 0) {
				nbTurn = stoi(data);
			}
			else if (param.compare("unit") == 0) {
				string unitClass = data.substr(0, data.find(','));
				data = data.substr(unitClass.size() + 1, data.size());
				string id = data.substr(0, data.find(','));
				data = data.substr(id.size() + 1, data.size());
				string health = data.substr(0, data.find(','));
				data = data.substr(health.size() + 1, data.size());
				string player = data.substr(0, data.find(','));
				data = data.substr(player.size() + 1, data.size());
				string super = data.substr(0, data.find(','));
				string pos = data.substr(super.size() + 1, data.size());
				field.at(stoi(pos))->place(Fighter::getInstanceOf(unitClass, stoi(health), stoi(id), stoi(super), stoi(player)));
			}
			else if (param.compare("goldEachTurn") == 0) {
				goldEachTurn = stoi(data);
			}
			else if (param.compare("gamemode") == 0) {
				gamemode = data;
			}
		}

		content = "";
		ifstream inConfigFile("config.txt");
		while (getline(inConfigFile, line))
		{
			content += line + "\n";
		}

		leftPlayer = new Human(firstPlayerMoney, 1);
		if (gamemode == "pvp") {
			rightPlayer = new Human(secondPlayerMoney, -1);
		}
		else {
			if (Strategy::strategies.find(gamemode) != Strategy::strategies.end()) {
				rightPlayer = new AI(secondPlayerMoney, Strategy::strategies.at(gamemode));
			}
			else {
				rightPlayer = new AI(secondPlayerMoney, new StrategyRich());
			}
		}
	}

	//getter
	vector<Square*> getField() { return field; }

	Player* getLeftPlayer() {
		return leftPlayer;
	}

	Player* getRightPlayer() {
		return rightPlayer;
	}

	int getNbTurn() {
		return nbTurn;
	}

	int getTurn() {
		return turn;
	}

	void update(int turn);

	void save(int cpt, int turn);

	void draw();

	int gameEnded();
	
};
