#include <iostream>

#include "FileGroup.h"

WeBankOS g_WeBankOS;

int main() {

	WeUser usr;

	usr.age = 19;
	usr.cards.push_back("asdasdasdasdas");
	usr.cards.push_back("asdasdasdsadasdd");
	usr.gender = 1;
	usr.ID = "41045281999112365556";
	usr.name = "W-Mai";
	usr.password = "Xbn";
	
	usr.getData();
	cout<<usr.getSize() << endl;

	WeUser usr2;

	usr2.loadData(usr.getData());

	cout << usr2.age << endl;
	cout << usr2.gender << endl;
	cout << usr2.ID  << endl;
	cout << usr2.name << endl;
	cout << usr2.password << endl;
	for (auto it = usr.cards.begin(); it != usr.cards.end(); it++) {
		cout << "Cards: " << (*it) << endl;
	}

	g_WeBankOS.run();
	return 0;
}
