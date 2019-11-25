#include <iostream>
#include <sstream>
#include "FileGroup.h"
#include <corecrt_io.h>

WeBankOS g_WeBankOS;


void unitTest() {
	WeUser usr;

	usr.age = 19;

	usr.gender = true;
	usr.ID = "41045281999112365556";
	usr.name = "W-Mai";
	usr.password = "Xbn";

	usr.getData();
	cout << usr.getSize() << endl;

	WeUser usr2;

	usr2.loadData(usr.getData());

	usr2.name = "X_Tu";
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
	//usrmnger.cancelUser(&usr2);
	//usrmnger.cancelUser(&usr2);
	cout << usrmnger.registerUser(&usr2) << endl;

	cout << "Verify: " << usrmnger.verifyUser("23333333333333", "Xbn") << endl;


	stringstream ss;
	string s = "123456789";

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

	FileManager fm(".");

	fm.savedData(&usrmnger);
}

vector<string>* fileSearch(string path) {
	long hFile = 0;
	auto rtn = new vector<string>;
	struct _finddata_t fileInfo;
	string pathName;
	
	if ((hFile = _findfirst(pathName.assign(path).append("/*").c_str(), &fileInfo)) == -1)
		return rtn;
	do {
		/*
			_A_SUBDIR 表示文件夹属性;
		*/
		if (strcmp(fileInfo.name, "..") && strcmp(fileInfo.name, "."))
			rtn->push_back(fileInfo.name);
	} while (_findnext(hFile, &fileInfo) == 0);

	_findclose(hFile);
	return rtn;
}

int main() {
	//unitTest();
	for(auto x: *fileSearch("./Data/Users")) {
		cout << x << endl;
	}
	//struct Data {
	//	string name;
	//	int card;
	//};
	//
	//struct Node {
	//	Data data;
	//	Node* next;
	//};

	//Node* result=search(Head, val);

	//result->data = newdata;
	g_WeBankOS.run();
	return 0;
}
