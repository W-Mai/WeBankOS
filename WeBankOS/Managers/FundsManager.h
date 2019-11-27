#pragma once

//#include "../FileGroup.h"

#include <string>
#include "../XData/XData.h"
#include "../DataContainer/ICCard.h"
#include "../DataContainer/WeUser.h"
#include "ICCardsManager.h"

using namespace std;

#define STRLENTH 21

class FundsManager {
	ICCardsManager* icCardsManger;
	WeUser* usr;
	ReceiptAndDisbursement* addReceiptsAndDisbursementsRecord(ICCard* card,const int amount);
public:
	FundsManager(ICCardsManager* icCardManager, WeUser* usr);

	[[nodiscard]] ICCard* verifyICCard(const AccountType& account, const string password) const;
	void registerICCard(const string& password) const;
	bool cancelICCard( ICCard* card) const;

	bool withdrawCash(ICCard* card,const int amount);
	void depositCash(ICCard* card,const int amount);

	vector<ReceiptAndDisbursement*>& getReceiptsAndDisbursementsDetails();
	double queryBalance(ICCard* card);
};
