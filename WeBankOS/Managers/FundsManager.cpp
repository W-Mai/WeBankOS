#include "FundsManager.h"
#include <iostream>
#include <algorithm>
#include "../TimeUtils.h"

ReceiptAndDisbursement::~ReceiptAndDisbursement() = default;

void* ReceiptAndDisbursement::getData() {
	//将结构体数据转化为void*便于存储
	char* rtn = new char[getSize()];
	memcpy(rtn, const_cast<char*>(account.c_str()), STRLENTH);
	memcpy(rtn + STRLENTH, &amount, sizeof(amount));
	memcpy(rtn + STRLENTH + sizeof(optime), &optime, sizeof(optime));

	rtn[STRLENTH - 1] = '\0';

	return rtn;
}

size_t ReceiptAndDisbursement::getSize()  {
	//返回数据大小
	return STRLENTH + sizeof(amount) + sizeof(optime);
}

void ReceiptAndDisbursement::loadData(void* data) {
	char* str;
	str = new char[STRLENTH];
	memcpy(str, data, STRLENTH);
	account = str;
	memcpy(&amount, static_cast<char*>(data) + STRLENTH, sizeof(amount));
	memcpy(&optime, static_cast<char*>(data) + STRLENTH + sizeof(amount), sizeof(optime));
}

ReceiptAndDisbursement* FundsManager::addReceiptsAndDisbursementsRecord(ICCard* card, const int amount) {
	if (queryBalance(card)-amount >= 0) {
		card->balance -= amount;
		auto rtn = new ReceiptAndDisbursement;
		rtn->account = card->account;
		rtn->amount = amount;
		rtn->optime = TimeUtils::getTimeStamp();
		return rtn;
	}
	return nullptr;
}

FundsManager::FundsManager(ICCardsManager* icCardManager, WeUser* usr) {
	this->icCardsManger = icCardManager;
	this->usr = usr;
}

ICCard* FundsManager::verifyICCard(const AccountType & account, const string password) const {
	auto searchRst = icCardsManger->searchCard(account);

	if (!icCardsManger->end(searchRst) && (*searchRst)->password==password) {
		return *searchRst;
	}
	return nullptr;
}

void FundsManager::registerICCard(const string& password) const {
	icCardsManger->addCard(usr, password);
}

bool FundsManager::cancelICCard(ICCard * card) const {
	if (icCardsManger->delCard(card)) {
		const auto tmpAccount = std::find_if(
			usr->cards.begin(),
			usr->cards.end(),
			[&card](const AccountType& tmpCard) {
			return tmpCard == card->account;
		});
		if (tmpAccount != usr->cards.end()) {
			usr->cards.erase(tmpAccount);
			return true;
		}
	}
	return false;
}

bool FundsManager::withdrawCash( ICCard * card, const int amount) {
	const auto tmpReceiptsAndDisbursementsRecord = addReceiptsAndDisbursementsRecord(card, amount);
	if (tmpReceiptsAndDisbursementsRecord) {
		usr->receiptAndDisbursements.push_back(tmpReceiptsAndDisbursementsRecord);
	}
	return true;
}

void FundsManager::depositCash(ICCard * card,const int amount) {
	withdrawCash(card, -amount);
}

vector<ReceiptAndDisbursement*>& FundsManager::getReceiptsAndDisbursementsDetails() {
	return usr->receiptAndDisbursements;
}

double FundsManager::queryBalance(ICCard * card) {
	return card->balance;
}
