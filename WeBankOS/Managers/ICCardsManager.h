#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>

#include "../DataContainer/ICCard.h"
#include "../DataContainer/WeUser.h"

class WeUser;
class ICCard;

typedef string AccountType;
#define CARDPREFIX "621226101000"

using namespace std;

class ICCardsManager {
private:
	vector<ICCard*> ICCards;
	vector<ICCard*>::iterator searchCard(AccountType account);
public:
	void addCard(WeUser* usr, string password);
	bool delCard(ICCard* card);
	ICCard* verifyICCard(string account, string password);
};
