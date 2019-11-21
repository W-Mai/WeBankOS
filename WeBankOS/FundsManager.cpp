#include "FundsManager.h"


ICCard* FundsManager::verifyICCard(AccountType account, string password) {
	// TODO: 在此处插入 return 语句
	return nullptr;
}

void FundsManager::registerICCard(WeUser* usr, string password) {}

void FundsManager::cancelICCard(WeUser* usr, ICCard* card) {}

void FundsManager::withdrawCash(ICCard* card, int amount) {}

void FundsManager::depositCash(ICCard* card, int amount) {}

void FundsManager::showReceiptsAndDisbursementsDetails(WeUser* usr) {}

double FundsManager::queryBalance(ICCard* card) {
	return 0.0f;
}
