#pragma once

#include "FileGroup.h"

using namespace std;

class FundsManager {

public:
	ICCard* verifyICCard(AccountType account, string password);
	void registerICCard(WeUser* usr, string password);
	void cancelICCard(WeUser* usr, ICCard* card);

	void withdrawCash(ICCard* card, int amount);
	void depositCash(ICCard* card, int amount);

	void showReceiptsAndDisbursementsDetails(WeUser* usr);
	double queryBalance(ICCard* card);
};

