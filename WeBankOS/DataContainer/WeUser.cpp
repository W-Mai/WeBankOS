#include "WeUser.h"

size_t WeUser::getSize() {
	return PACKLEN(data) + LEADSIZE; //我忘记加了一个LEADSIZE，导致了窝两天没有改出来bug，艹。
}

void* WeUser::getData() {
	data.clear();
	data.push(const_cast<char*>(name.c_str()), name.size() + 1);
	data.push(const_cast<char*>(ID.c_str()), ID.size() + 1);
	data.push(const_cast<char*>(password.c_str()), password.size() + 1);
	data.push(&gender, sizeof(gender));
	data.push(&age, sizeof(age));
	data.push(const_cast<char*>(TEL.c_str()), TEL.size() + 1);
	
	XData cardsData;
	for (auto it = cards.begin(); it != cards.end();++it) {
		cardsData.push(const_cast<char *>((*it).c_str()), (*it).size() + 1);
	}
	data.push(cardsData, cardsData.size());

	XData receiptAndDisbursementsData;
	for (auto it = receiptAndDisbursements.begin(); it != receiptAndDisbursements.end(); ++it) {
		receiptAndDisbursementsData.push((*it)->getData(), (*it)->getSize());
	}
	data.push(receiptAndDisbursementsData, receiptAndDisbursementsData.size());

	return data;
}

void WeUser::loadData(void* packData) {
	size_t tmpS = 0;
	char* str;
	XData data(packData, -1);

	cards.clear();
	receiptAndDisbursements.clear();
#define GETSTRING(var) data.get(&str);\
	                   var = str

	GETSTRING(name);data.next();
	GETSTRING(ID);data.next();
	GETSTRING(password);data.next();

	data.get(&str);data.next();
	gender = *reinterpret_cast<bool *>(str);
	data.get(&str);data.next();
	age = *reinterpret_cast<int*>(str);
	GETSTRING(TEL);data.next();

	data.get(&str);data.next();
	XData cardsData(str, -1);
	;
	if (cardsData.size() > LEADSIZE) {
		do {
			cardsData.get(&str);
			cards.push_back(str);
		} while (cardsData.next() != FAILED);
	}

	data.get(&str);
	XData receiptAndDisbursementsData(str, -1);
	if (receiptAndDisbursementsData.size() >LEADSIZE) {
		do {
			receiptAndDisbursementsData.get(&str);
			auto tmpReceiptAndDisbursement = new ReceiptAndDisbursement;
			tmpReceiptAndDisbursement->loadData(str);
			receiptAndDisbursements.push_back(tmpReceiptAndDisbursement);
		} while (receiptAndDisbursementsData.next() != FAILED);
	}
	
}
