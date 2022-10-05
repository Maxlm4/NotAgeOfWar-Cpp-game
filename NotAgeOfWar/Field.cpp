#include "Field.h"
#include <iostream>
#include "Bowman.h"
#include "Swordman.h"
#include "Catapult.h"
using namespace std;

void Field::update(int turn) {
	Player* currentPlayer;
	int baseIndex;
	int startIndex;
	string leftState;
	string rightState;
	if (turn == 1) {
		currentPlayer = leftPlayer;
		baseIndex = 0;
		startIndex = (int)field.size() - 2;
		printf("%c[%dm", 0x1B, 34);
		cout << "===========================" << endl;
		cout << "It is your turn LEFT player " << endl;
		cout << "===========================" << endl;
		leftState = "your castle has ";
		rightState = "enemy s castle has ";
	}
	else {
		currentPlayer = rightPlayer;
		baseIndex = (int)field.size() - 1;
		startIndex = 1;
		printf("%c[%dm", 0x1B, 31);
		cout << "============================" << endl;
		cout << "It is your turn RIGHT player " << endl;
		cout << "============================" << endl;
		leftState = "enemy s castle has ";
		rightState = "your castle has ";
	}
	
	currentPlayer->giveMoney(goldEachTurn);
	cout << endl;

	printf("%c[%dm", 0x1B, 35);

	for (int i = baseIndex; turn * (i) <= turn * (startIndex) ; i+=turn) {
		if (field.at(i)->getFighterOn() != nullptr) {
			if (field.at(i)->getFighterOn()->getFirstPlayer() == turn) {
				int k = i;
				field.at(i)->getFighterOn()->action1(&field, &k, currentPlayer);
			}
		}
	}

	for (int i = startIndex; turn * (i) >= turn * (baseIndex); i -= turn) {
		if (field.at(i)->getFighterOn() != nullptr) {
			if (field.at(i)->getFighterOn()->getFirstPlayer() == turn) {
				int k = i;
				field.at(i)->getFighterOn()->action2(&field, &k, currentPlayer);
			}
		}
	}

	for (int i = startIndex; turn * (i) >= turn * (baseIndex); i -= turn) {
		if (field.at(i)->getFighterOn() != nullptr) {
			if (field.at(i)->getFighterOn()->getFirstPlayer() == turn && field.at(i)->getFighterOn()->getFailActionOne()) {
				int k = i;
				field.at(i)->getFighterOn()->action3(&field, &k, currentPlayer);
			}
		}
	}

	printf("%c[%dm", 0x1B, 32);

	cout << endl;
	for (int i = 0; i < (int)field.size(); i++) {
		if (i == 0) {
			cout << leftState << to_string(field.at(0)->getBase()->getHealth()) << " health points left" << endl;
		}
		if (field.at(i)->getFighterOn() != nullptr) {
			cout << field.at(i)->getFighterOn()->getUnitClass() << " " << to_string(field.at(i)->getFighterOn()->getId()) << " has " << to_string(field.at(i)->getFighterOn()->getHealth()) << " health points left" << endl;
		}
		if (i == (int)field.size() - 1) {
			cout << rightState << to_string(field.at((int)field.size() - 1)->getBase()->getHealth()) << " health points left" << endl;
		}
	}
	cout << endl;
	draw();
	cout << endl;
	currentPlayer->update(field.at(baseIndex));
}

void Field::save(int cpt, int turn) {
	ofstream saveFile;
	saveFile.open("save.txt");
	saveFile << content;
	saveFile << "gamemode=" + gamemode + "\n";
	if (turn == 1) {
		saveFile << "nbTurn=" + to_string(cpt) + "\n";
	}
	else {
		saveFile << "nbTurn=" + to_string(cpt + 1) + "\n";
	}
	saveFile << "turn=" + to_string(-turn) + "\n";
	saveFile << "firstPlayerMoney=" + to_string(leftPlayer->getMoney()) + "\n";
	saveFile << "secondPlayerMoney=" + to_string(rightPlayer->getMoney()) + "\n";
	saveFile << "firstPlayerCastle=" + to_string(field.at(0)->getBase()->getHealth()) + "\n";
	saveFile << "secondPlayerCastle=" + to_string(field.at((int)field.size() - 1)->getBase()->getHealth()) + "\n";
	for (int i = 0; i < (int)field.size(); i++) {
		if (field.at(i)->getFighterOn() != nullptr) {
			saveFile << "unit=" + field.at(i)->getFighterOn()->getUnitClass() + "," + to_string(field.at(i)->getFighterOn()->getId()) + "," + to_string(field.at(i)->getFighterOn()->getHealth()) + "," + to_string(field.at(i)->getFighterOn()->getFirstPlayer()) + "," + to_string(field.at(i)->getFighterOn()->getSuper()) + "," + to_string(i) + "\n";
		}
	}
	saveFile.close();
}

void Field::draw() {
	for (int i = 0; i < (int)field.size(); i++) {
		if (field.at(i)->getFighterOn() == nullptr) {
			cout << ' ';
		}
		else {
			if (field.at(i)->getFighterOn()->getFirstPlayer() == 1) {
				printf("%c[%dm", 0x1B, 34);
			}
			else {
				printf("%c[%dm", 0x1B, 31);
			}
			if (Fighter::unitSymbols.find(field.at(i)->getFighterOn()->getUnitClass()) != Fighter::unitSymbols.end()) {
				if (field.at(i)->getFighterOn()->getSuper()) {
					cout << Fighter::unitSymbols.at(field.at(i)->getFighterOn()->getUnitClass()).substr(2, 3);
				}
				else {
					cout << Fighter::unitSymbols.at(field.at(i)->getFighterOn()->getUnitClass()).substr(0, 1);
				}
			}
			else {
				cout << ' ';
			}
		}
	}
	cout << endl;
	for (int i = 0; i < (int)field.size(); i++) {
		printf("%c[%dm", 0x1B, 0);
		if (field.at(i)->getBase() != nullptr) {
			if (field.at(i)->getBase()->getFirstPlayer() == 1) {
				printf("%c[%dm", 0x1B, 34);
			}
			else {
				printf("%c[%dm", 0x1B, 31);
			}
			cout << 'M';
		}
		else {	
			cout << '_';
		}
	}
	cout << endl;
}

int Field::gameEnded() {
	if (field.at(0)->getBase()->getHealth() <= 0) {
		field.at(0)->destroy();
		return 1;
	}
	else if (field.at((int)field.size() - 1)->getBase()->getHealth() <= 0) {
		field.at((int)field.size() - 1)->destroy();
		return -1;
	}
	else {
		return 0;
	}
}

