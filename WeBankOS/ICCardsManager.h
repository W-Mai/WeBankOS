#pragma once

#include <vector>
#include "FileGroup.h"

using namespace std;

class ICCardsManager {
private:
	vector<ICCard> ICCards;
public:
	void addCard(WeUser& usr, string password);
	void delCard(ICCard& card);
	void searchCard(AccountType account);
};