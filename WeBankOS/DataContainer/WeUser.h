#pragma once

#include "../FileGroup.h"

using namespace std;

class WeUser {
private:
	string name;
	string ID;
	string password;
	bool gender;
	string age;
	string TEL;
	vector<AccountType> cards;
	vector<ReceiptAndDisbursement *> receiptAndDisbursements;
public:
	WeUser() = default;
};
