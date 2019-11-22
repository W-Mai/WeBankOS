#include "ICCard.h"

size_t ICCard::getSize() {
	return STRLENTH * 4 + sizeof(balance);
}

void* ICCard::getData() {
	char* rtn = new char[getSize()];
	memcpy(rtn, (char*)account.c_str(), STRLENTH);
	memcpy(rtn + STRLENTH, (char*)host.c_str(), STRLENTH);
	memcpy(rtn + STRLENTH * 2, (char*)TEL.c_str(), STRLENTH);
	memcpy(rtn + STRLENTH * 3, (char*)password.c_str(), STRLENTH);
	memcpy(rtn + STRLENTH * 4, &balance, sizeof(balance));

	rtn[STRLENTH - 1] = '\0';
	rtn[STRLENTH * 2 - 1] = '\0';
	rtn[STRLENTH * 3 - 1] = '\0';
	rtn[STRLENTH * 4 - 1] = '\0';
	return rtn;
}

void ICCard::loadData(void* data) {
	char* str;
	str = new char[STRLENTH];
	memcpy(str, data, STRLENTH);
	account = str;

	str = new char[STRLENTH];
	memcpy(str, (char*)data + STRLENTH * 1, STRLENTH);
	host = str;

	str = new char[STRLENTH];
	memcpy(str, (char*)data + STRLENTH * 2, STRLENTH);
	TEL = str;

	str = new char[STRLENTH];
	memcpy(str, (char*)data + STRLENTH * 3, STRLENTH);
	password = str;

	memcpy(&balance, (char*)data + STRLENTH * 4, sizeof(balance));

}
