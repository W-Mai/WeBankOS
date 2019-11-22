#pragma once

#pragma pack(1)
//#include "../FileGroup.h"
#include <iostream>
#include <string>
#include "../XData/XData.h"

class WeUser;
class ICCard;

using namespace std;

typedef string AccountType;
#define STRLENTH 21

class ReceiptAndDisbursement:virtual public DataPack {
public:
	AccountType account;
	int amount;
	time_t optime;

	void* getData() {//将结构体数据转化为void*便于存储
		char* rtn = new char[getSize()];
		memcpy(rtn, (char*)account.c_str(), STRLENTH);
		memcpy(rtn + STRLENTH, &amount, sizeof(amount));
		memcpy(rtn + STRLENTH + sizeof(optime), &optime, sizeof(optime));

		rtn[STRLENTH - 1] = '\0';

		return rtn;
	}
	size_t getSize() {//返回数据大小
		return STRLENTH + sizeof(amount) + sizeof(optime);
	}
	void loadData(void * data) {
		char* str;
		str = new char[STRLENTH];
		memcpy(str, data, STRLENTH);
		account = str;
		memcpy(&amount, (char*)data + STRLENTH, sizeof(amount));
		memcpy(&optime, (char*)data + STRLENTH + sizeof(amount), sizeof(optime));
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
