#include "Strategy.h"
#include "StrategyPattern.h"
#include "StrategyRich.h"
#include <map>
using namespace std;

map<string, Strategy*> Strategy::strategies = map<string, Strategy*>();

void Strategy::initialize() {
	strategies.insert(pair<string,Strategy*>("Player VS PatternBot", new StrategyPattern()));
	strategies.insert(pair<string, Strategy*>("Player VS RicherBot", new StrategyRich()));
}