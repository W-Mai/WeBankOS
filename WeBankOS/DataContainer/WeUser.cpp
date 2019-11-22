#include "WeUser.h"

size_t WeUser::getSize() {
	return PACKLEN(data);
}

void* WeUser::getData() {
	data.push((char*)name.c_str(), name.size() + 1);
	data.push((char*)ID.c_str(), ID.size() + 1);
	data.push((char*)password.c_str(), password.size() + 1);
	data.push(&gender, sizeof(gender));
	data.push(&age, sizeof(age));
	data.push((char*)TEL.c_str(), TEL.size() + 1);
	
	XData cardsData;
	for (auto it = cards.begin(); it != cards.end();it++) {
		cardsData.push((char *)(*it).c_str(), (*it).size());
	}
	data.push(cardsData, PACKLEN(cardsData));

	XData receiptAndDisbursementsData;
	for (auto it = receiptAndDisbursements.begin(); it != receiptAndDisbursements.end(); it++) {
		receiptAndDisbursementsData.push((*it)->getData(), (*it)->getSize());
	}
	data.push(receiptAndDisbursementsData, PACKLEN(receiptAndDisbursementsData));

	return data;
}

void WeUser::loadData(void* packData) {
	size_t tmpS = 0;
	char* str;
	XData data(packData, -1);
#define GETSTRING(var) data.get(&str);\
	                   var = str

	GETSTRING(name);data.next();
	GETSTRING(ID);data.next();
	GETSTRING(password);data.next();

	data.get(&str);data.next();
	gender = *(bool *)str;
	data.get(&str);data.next();
	age = *(int*)str;
	GETSTRING(TEL);data.next();

	data.get(&str);
	XData cardsData(str, -1);
	do {
		cardsData.get(&str);
		cards.push_back(str);
	} while (cardsData.next() != FAILED);


	data.get(&str);
	XData receiptAndDisbursementsData(str, -1);
	do {
		receiptAndDisbursementsData.get(&str);
		ReceiptAndDisbursement *tmpReceiptAndDisbursement = new ReceiptAndDisbursement;
		tmpReceiptAndDisbursement->loadData(str);
		receiptAndDisbursements.push_back(tmpReceiptAndDisbursement);
	} while (receiptAndDisbursementsData.next() != FAILED);
}
