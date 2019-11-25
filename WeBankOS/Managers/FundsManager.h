#pragma once

#pragma pack(1)
//#include "../FileGroup.h"

#include <string>
#include "../XData/XData.h"
#include "../DataContainer/ICCard.h"
#include "../DataContainer/WeUser.h"
#include "ICCardsManager.h"

class ICCardsManager;
class WeUser;
class ICCard;

using namespace std;

typedef string AccountType;
#define STRLENTH 21

class ReceiptAndDisbursement{
public:
	AccountType account;
	int amount;
	time_t optime;

	virtual ~ReceiptAndDisbursement();

	void* getData();

	size_t getSize();

	void loadData(void* data);
};

class FundsManager {
	ICCardsManager* icCardsManger;
	WeUser* usr;
	ReceiptAndDisbursement* addReceiptsAndDisbursementsRecord(ICCard* card,const int amount);
public:
	FundsManager(ICCardsManager* icCardManager, WeUser* usr);

	ICCard* verifyICCard(const AccountType& account, const string password) const;
	void registerICCard(const string& password) const;
	bool cancelICCard( ICCard* card) const;

	bool withdrawCash(ICCard* card,const int amount);
	void depositCash(ICCard* card,const int amount);

	vector<ReceiptAndDisbursement*>& getReceiptsAndDisbursementsDetails();
	double queryBalance(ICCard* card);
};

#pragma pack()
