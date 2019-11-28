#pragma once

#include <vector>
#include <string>
#include <iomanip>

#include "../DataContainer/ICCard.h"
#include "../DataContainer/WeUser.h"

class WeUser;
class ICCard;

typedef string AccountType;
constexpr auto CARDPREFIX = "621226101000";

using namespace std;

class ICCardsManager {
public:
	vector<ICCard*> icCards;
	void addCard(WeUser* usr, const string& password);
	bool delCard(ICCard* card);
	vector<ICCard*>::iterator searchCard(AccountType account);
	bool end(vector<ICCard*>::iterator item);
};
