#include "FundsManager.h"


FundsManager::FundsManager(ICCardsManager* iccrdmnger) {
	this->icCardsManger = iccrdmnger;
}

ICCard* FundsManager::verifyICCard(AccountType account, string password) {
	return icCardsManger->verifyICCard(account, password);
}

void FundsManager::registerICCard(WeUser* usr, string password) {
	icCardsManger->addCard(usr, password);
}

void FundsManager::cancelICCard(WeUser* usr, ICCard* card) {
	if (icCardsManger->delCard(card)) {
		search(usr->cards.begin(), usr->cards.end(), [&card](AccountType tmpCard) {return tmpCard == card->account; });
	}
}

bool FundsManager::withdrawCash(ICCard* card, int amount) {}

void FundsManager::depositCash(ICCard* card, int amount) {}

vector<ReceiptAndDisbursement*>& FundsManager::getReceiptsAndDisbursementsDetails(WeUser* usr) {}

double FundsManager::queryBalance(ICCard* card) {
	return 0.0f;
}
