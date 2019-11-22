#pragma once

//#include "../FileGroup.h"

#include <string>
#include "../XData/XData.h"
#include "../Managers/FundsManager.h"

using namespace std;

class WeUser: virtual public DataPack {
private :
	XData data;
public:
	string name;
	string ID;
	string password;
	bool gender;
	int age;
	string TEL;
	vector<AccountType> cards;
	vector<ReceiptAndDisbursement*> receiptAndDisbursements;

	WeUser() = default;
	size_t getSize();
	void* getData();
	void loadData(void * packData);
};
