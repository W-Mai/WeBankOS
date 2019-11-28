#pragma once

//#include "../FileGroup.h"
#include <string>
#include "../XData/XData.h"
#include <ctime>

using namespace std;

#define STRLENTH 21

//20λ: 62 1226 101000 + 8λ
class ICCard{

public:
	string account;
	string host;
	string TEL;
	string password;
	double balance;
	size_t getSize();
	void* getData();
	void loadData(void* data);
};

