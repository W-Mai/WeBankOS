#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include "../DataContainer/WeUser.h"
class WeUser;

using namespace std;

class UserManager {
	
	vector<WeUser*>::iterator searchUser(string ID);

public:
	vector<WeUser*> weUsers;
	bool registerUser(WeUser* usr);
	bool registerUser(string name, string ID, bool gender, int age, string TEL);
	bool cancelUser(WeUser* usr);
	bool cancelUser(string ID);

	WeUser* verifyUser(string ID, string password);
};
