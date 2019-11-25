#include <iostream>
#include <sstream>
#include "FileGroup.h"

WeBankOS g_WeBankOS;


void unitTest() {
	WeUser usr;

	usr.age = 19;

	usr.gender = 1;
	usr.ID = "41045281999112365556";
	usr.name = "W-Mai";
	usr.password = "Xbn";

	usr.getData();
	cout << usr.getSize() << endl;

	WeUser usr2;

	usr2.loadData(usr.getData());

	cout << usr2.age << endl;
	cout << usr2.gender << endl;
	cout << usr2.ID << endl;
	cout << usr2.name << endl;
	cout << usr2.password << endl;
	for (auto it = usr.cards.begin(); it != usr.cards.end(); it++) {
		cout << "Cards: " << (*it) << endl;
	}

	UserManager usrmnger;
	usr2.ID = "233333333333333";
	cout << usrmnger.registerUser(&usr) << endl;
	cout << usrmnger.registerUser(&usr2) << endl;
	cout << usrmnger.registerUser(&usr2) << endl;
	usrmnger.cancelUser(&usr2);
	usrmnger.cancelUser(&usr2);
	cout << usrmnger.registerUser(&usr2) << endl;

	cout << "Verify: " << usrmnger.verifyUser("23333333333333", "Xbn") << endl;


	stringstream ss;
	string s = "123456789";
	int a;
	//cout << string(s.begin() + 5, s.end()) << endl;
	//ss << 123;
	//ss >> a;
	//ss << "123456";
	//cout << a << endl;
	//cout << ss.str() << endl;
	ICCardsManager* icdmnger = new ICCardsManager;

	icdmnger->addCard(&usr, "1234");
	icdmnger->addCard(&usr, "1234");
	icdmnger->addCard(&usr, "1234");
	icdmnger->addCard(&usr, "1234");
	icdmnger->addCard(&usr, "1234");
	icdmnger->addCard(&usr, "1234");
	icdmnger->addCard(&usr, "1234");
	icdmnger->addCard(&usr, "1234");
	icdmnger->addCard(&usr, "1234");
	icdmnger->addCard(&usr, "1234");
	icdmnger->addCard(&usr, "1234");
	icdmnger->addCard(&usr, "1234");
	icdmnger->addCard(&usr, "1234");

	/*cout << icdmnger.verifyICCard(CARDPREFIX + string("00000007"), "1234")->host << endl;*/

	FundsManager fundsManager(icdmnger, &usr);
	for (auto x : usr.cards) {
		//cout << x << endl;
		cout << fundsManager.verifyICCard(x, "1234")->host << endl;
		/*cout << (*icdmnger.searchCard(x))->password << endl;*/

	}
}

int main() {
	unitTest();

	g_WeBankOS.run();
	return 0;
}
