#include "ICCardsManager.h"
#include <algorithm>
#include <sstream>

void ICCardsManager::addCard(WeUser* usr, const string& password) {
	stringstream ss;
	auto tmpICCard = new ICCard;
	int suffixNum;
	if (!icCards.empty()) {
		string lastAccount = icCards.back()->account;
		ss << string((lastAccount.begin() + 12), lastAccount.end());
	} else ss << 0;

	ss >> suffixNum;
	ss.clear();
	ss << CARDPREFIX << setw(8) << setfill('0') << ++suffixNum;
	ss >> tmpICCard->account;
	tmpICCard->host = usr->name;
	tmpICCard->TEL = usr->TEL;
	tmpICCard->password = password;
	tmpICCard->balance = 0;
	icCards.push_back(tmpICCard);
	usr->cards.push_back(tmpICCard->account);
}

bool ICCardsManager::delCard(ICCard* card) {
	auto rst = searchCard(card->account);
	if (rst != icCards.end()) {
		icCards.erase(rst);
		return true;
	}
	return false;
}

vector<ICCard*>::iterator ICCardsManager::searchCard(AccountType account) {
	return find_if(icCards.begin(),
				   icCards.end(),
				   [&account](ICCard* card) {
		return card->account == account;
	});
}

bool ICCardsManager::end(vector<ICCard*>::iterator item) {
	return item == icCards.end();
}

