#include "UserManager.h"

vector<WeUser*>::iterator UserManager::searchUser(string ID) {
	return find_if(weUsers.begin(), weUsers.end(), [&ID](WeUser* usr) {return usr->ID == ID; });
}

bool UserManager::registerUser(WeUser* usr) {
	if (searchUser(usr->ID)==weUsers.end()) {
		weUsers.push_back(usr);
		return true;
	}
	return false;
}

bool UserManager::registerUser(string name, string ID, bool gender, int age, string TEL) {
	WeUser* usr = new WeUser;
	usr->name = name;
	usr->ID = ID;
	usr->gender = gender;
	usr->age = age;
	usr->TEL = TEL;
	return registerUser(usr);
}

bool UserManager::cancelUser(WeUser* usr) {
	return cancelUser(usr->ID);
}

bool UserManager::cancelUser(string ID) {
	auto rst = searchUser(ID);
	if (rst != weUsers.end()) {
		weUsers.erase(rst);
		return true;
	}
	return false;
}

WeUser* UserManager::verifyUser(string ID, string password) {
	vector<WeUser*>::iterator usr = searchUser(ID);
	if (usr!=weUsers.end() && (*usr)->password == password) {
		return *usr;
	}
	return nullptr;
}

