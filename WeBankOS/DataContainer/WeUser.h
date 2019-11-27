#pragma once

//#include "../FileGroup.h"

#include <string>
#include "../XData/XData.h"
#include <iostream>

typedef std::string AccountType;
class ReceiptAndDisbursement {
public:
	AccountType account;
	int amount;
	time_t opTime;

	void* getData();

	size_t getSize();

	void loadData(void* data);
};
using namespace std;
typedef string AccountType;

class WeUser{
	XData data;
public:
	bool gender;
	int age;
	string name;
	string ID;
	string password;
	string TEL;
	vector<AccountType> cards;
	vector<ReceiptAndDisbursement*> receiptAndDisbursements;

	size_t getSize();
	void* getData();
	void loadData(void * packData);
};
