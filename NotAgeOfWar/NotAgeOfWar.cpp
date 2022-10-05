#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#include "Field.h"
#include "Fighter.h"
#include "Castle.h"
#include "Strategy.h"

int main()
{
	Strategy::initialize();

	Field field;

	while (true) {
		string s;
		printf("%c[%dm", 0x1B, 0);
		cout << "new game : 0 ; load game : 1" << endl;
		cin >> s;
		if (s == "0") {
			Fighter::setData("config.txt");
			while (true) {
				string t;
				cout << "Player VS Player : 0";
				int num = 1;
				for (auto it = Strategy::strategies.begin(); it != Strategy::strategies.end(); it++) {
					cout << " ; " << it->first << " : " << num;
					num++;
				}
				cout << endl;
				cin >> t;
				if (t == "0") {
					field = Field("pvp");
					break;
				}
				else {
					num = 1;
					bool verif = false;
					for (auto it = Strategy::strategies.begin(); it != Strategy::strategies.end(); it++) {
						if (to_string(num) == t) {
							field = Field(it->first);
							verif = true;
							break;
						}
						num++;
					}
					if (!verif) {
						cout << "unable to find " << t << " option" << endl;
					}
					else {
						break;
					}
				}
			}
			break;
		}
		else if (s == "1") {
			Fighter::setData("save.txt");
			field = Field();
			break;
		}
		else {
			cout << "unable to find " + s + " option" << endl;
		}
	}

	int turn = field.getTurn();
	int cpt = field.getNbTurn();
	while (cpt < 100) {
		printf("%c[%dm", 0x1B, 0);
		cout << "Turn " << to_string(cpt) << endl;
		if (turn != -1) {
			field.update(turn);
			field.save(cpt, turn);
			turn *= -1;
		}
		field.update(turn);
		field.save(cpt, turn);
		turn *= -1;
		int end = field.gameEnded();
		if (end < 0) {
			printf("%c[%dm", 0x1B, 34);
			cout << "\n================\nLeft player wins\n================\n\n";
			break;
		}
		else if (end > 0) {
			printf("%c[%dm", 0x1B, 31);
			cout << "\n=================\nRight player wins\n=================\n\n";
			break;
		}
		cpt++;
	}

	field.draw();
	
	if (cpt == 100) {
		printf("%c[%dm", 0x1B, 0);
		cout << "\n=========================\nTime elapsed, nobody wins\n=========================\n\n";
	}
}
