#include "ICCardsManager.h"

void ICCardsManager::addCard(WeUser* usr, string password) {
	stringstream ss;
	ICCard* tmpICCard = new ICCard;
	int suffixNum;
	if (!ICCards.empty()) {
		string lastAccount = ICCards.back()->account;
		ss << string((lastAccount.begin() + 12), lastAccount.end());
	} else ss << 0;
	
	ss >> suffixNum;
	ss.clear();
	ss << CARDPREFIX << setw(8) <<setfill('0') <<++suffixNum;
	ss >> tmpICCard->account;
	tmpICCard->host = usr->name;
	tmpICCard->TEL = usr->TEL;
	tmpICCard->password = password;
	tmpICCard->balance = 0;
	ICCards.push_back(tmpICCard);
	usr->cards.push_back(tmpICCard->account);
}

bool ICCardsManager::delCard(ICCard* card) {
	auto rst = searchCard(card->account);
	if (rst != ICCards.end()) {
		ICCards.erase(rst);
		return true;
	}
	return false;
}

ICCard* ICCardsManager::verifyICCard(string account, string password) {
	auto rst = searchCard(account);
	if (rst!=ICCards.end()) {
		return *rst;
	}
	return nullptr;
}

vector<ICCard*>::iterator ICCardsManager::searchCard(AccountType account) {
	return find_if(ICCards.begin(),
				   ICCards.end(),
				   [&account](ICCard* card) {
		return card->account == account;
	});
}
