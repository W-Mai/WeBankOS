#pragma once

#pragma pack(1)
#include "../FileGroup.h"

using namespace std;

const size_t STRLENTH = 21;

struct ReceiptAndDisbursement {
	AccountType account;
	int amount;
	time_t optime;

	void* getData() {//���ṹ������ת��Ϊvoid*���ڴ洢
		char* rtn = new char[getSize()];
		memcpy(rtn, (char*)account.c_str(), STRLENTH);
		memcpy(rtn + STRLENTH, &amount, sizeof(amount));
		memcpy(rtn + STRLENTH + sizeof(optime), &optime, sizeof(optime));
		return rtn;
	}
	size_t getSize() {//�������ݴ�С
		return STRLENTH + sizeof(amount) + sizeof(optime);
	}
};

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

#pragma pack()
