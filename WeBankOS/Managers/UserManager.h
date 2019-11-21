#pragma once

#include "../FileGroup.h"

using namespace std;


class UserManager {
private:
	WeUser* searchUser(string ID);
	
public:
	bool registerUser(WeUser* usr);
	bool registerUser(string name, string ID, bool gender, string age, string TEL);
	bool cancelUser(WeUser* usr);
	bool cancelUser(string ID);

	WeUser* verifyUser(string name, string password);
};

