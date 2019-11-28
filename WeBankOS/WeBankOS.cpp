#include <iostream>
#include "WeBankOS.h"
#include <windows.h>
#include "TimeUtils.h"

std::string add(const std::string a, const std::string b);
std::string sub(const std::string a, const std::string b);

inline void flush() { cin.ignore(1024, '\n'); }

bool isLegalAccount(string account) {
	auto numberCount = true;
	const int accountSize = account.length();
	if (accountSize < 10 || accountSize >13)return false;
	for (auto i = 0; i < accountSize; i++) {
		numberCount = numberCount && isdigit(account[i]);
	}
	return numberCount;
}

bool isLegalPassword(string pwd) {
	auto alpha = 0;
	auto number = 0;
	auto dash = 0;
	const int len = pwd.length();
	if (len < 3 || pwd[len - 3] != '@') return false;

	for (int i = 0; i < len; i++) {
		alpha += isalpha(pwd[i]);
		number += isdigit(pwd[i]);
		dash += pwd[i] == '_';
	}
	return !!alpha && !!number && !!dash;
}

WeBankOS::Functions::Functions(WeBankOS* p) {
	os = p;
}

void WeBankOS::Functions::registerFunction(const string& name, const FunctionType func) {
	funMap[name] = func;
}

bool WeBankOS::Functions::callFunction(const string& name) {
	const auto tempFunction = funMap[name];
	if (tempFunction) {
		(os->*tempFunction)();
		return true;
	}
	return false;
}

// ReSharper disable CppMemberFunctionMayBeConst
void WeBankOS::printPrompt() {
	setTextColor(0x02);
	cout << getUserName();
	setTextColor(0x0F);
	cout << "@";
	setTextColor(0x03);
	cout << "Bank";
	setTextColor(0x0F);
	cout << ":";
	setTextColor(0x0B);
	cout << currentFunction;
	setTextColor(0x08);
	cout << "$ ";
	setTextColor(0x0F);
}

void WeBankOS::setTextColor(const char color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

WeBankOS::WeBankOS(const string& dataFilePath) {
	system("mode con cols=80 lines=10240");

	functions = new Functions(this);

	fundsManager = nullptr;
	fileManager = new FileManager(dataFilePath);
	running = true;

	currentFunction = "HOMEPAGE";

	running = true;

	init();
}

void WeBankOS::init() const {
	cout << "WeBankOS 1.0.1 (tags/v1.0.1:e26112019e, 11 2019) [MSC v.1941] on win32.\n"
		"Type \"help/?\", \"copyright\" for more information." << endl << endl;

	//Register all the functions BEGIN.
	functions->registerFunction("login", static_cast<FunctionType>(&WeBankOS::login));
	functions->registerFunction("logout", static_cast<FunctionType>(&WeBankOS::logout));
	functions->registerFunction("register", static_cast<FunctionType>(&WeBankOS::registerUser));
	functions->registerFunction("exit", static_cast<FunctionType>(&WeBankOS::exitOS));
	functions->registerFunction("q", static_cast<FunctionType>(&WeBankOS::exitOS));
	functions->registerFunction("help", static_cast<FunctionType>(&WeBankOS::help));
	functions->registerFunction("?", static_cast<FunctionType>(&WeBankOS::help));
	functions->registerFunction("load_conf", static_cast<FunctionType>(&WeBankOS::loadConfigurations));
	functions->registerFunction("cls", static_cast<FunctionType>(&WeBankOS::clearScreen));
	functions->registerFunction("calc", static_cast<FunctionType>(&WeBankOS::calcBigNum));
	functions->registerFunction("ls", static_cast<FunctionType>(&WeBankOS::listCards));
	functions->registerFunction("card", static_cast<FunctionType>(&WeBankOS::cardsFunc));


	//Register all the functions END.


	functions->callFunction("load_conf");
}

void WeBankOS::help() {
	setTextColor(HIGHLIGHT_COLOR);
	cout << endl;

	//Register all the Help_Info BEGIN.
	showOneItemOfHelp("cls", "	clear screen.");
	showOneItemOfHelp("q,exit", "exit this OS.");
	showOneItemOfHelp("login", "usage: \"login ID password\" to login your account.");
	showOneItemOfHelp("help/?", "to show the help of this OS.");
	showOneItemOfHelp("logout", "login out your account.");
	showOneItemOfHelp("register", "register a new user step by step.");
	showOneItemOfHelp("load_conf", "load all the configurations.");
	showOneItemOfHelp("calc", "calc big number(only + and - support).");
	showOneItemOfHelp("ls", "\tlist all your IC card.");
	showOneItemOfHelp("card",
					  "-add	add a new card.\n"
					  "\t\t-cancel	delete a card from your account.\n"
					  "\t\t-dep	deposit cash.\n"
					  "\t\t-wit	withdraw cash.\n"
					  "\t\t-det	show your receipts and disbursements details.");

	//Register all the Help_Info END.

	cout << endl;
	setTextColor(0x0F);
}

void WeBankOS::run() {
	string command;
	printPrompt();
	if (cin >> command) {
		const auto rtn = functions->callFunction(command);
		if (!rtn) {
			setTextColor(HIGHLIGHT_COLOR);
			cout << endl << "	Command Error: Bad Command \"" << command << "\"." << endl << endl
				<< "	Type `help/?` for more commands."<< endl<<endl;
			flush();
			setTextColor(0x0F);
		}
	} else exitOS();

	//currentFunction = "HOMEPAGE";
}

void WeBankOS::login() {
	if (loggedUser) {
		showSomeInfo("	You have been Logged in before. Please logged out first.");
		cin.ignore(1024, '\n');
		return;
	}
	currentFunction = "LOGGED";

	string name, password;
	cin >> name >> password;
	loggedUser = userManager.verifyUser(name, password);
	if (loggedUser) {
		fundsManager = new FundsManager(&icCardsManager, loggedUser);
		showSomeInfo("	Welcome " + getUserName() + ". Logged In Successfully.");
	} else {
		currentFunction = "HOMEPAGE";
		showSomeInfo("	Logged Failed. Please check your ID or Password.");
	}
}

void WeBankOS::logout() {
	if (!loggedUser) {
		showSomeInfo("	You haven't Logged in before. Please logged in first.");
		cin.ignore(1024, '\n');
		return;
	}
	saveConfigurations();
	showSomeInfo("	" + getUserName() + ".Logout successfully.");

	delete fundsManager;
	fundsManager = nullptr;
	loggedUser = nullptr;
	currentFunction = "HOMEPAGE";
}

void WeBankOS::registerUser() {
	if (loggedUser) {
		showSomeInfo("\tYou've logged in. Please logged out first.");
		return;
	}
	auto usr = new WeUser;
	showSomeInfo("Input some info to register a new account.\n"
				 "You will use your ID to log in later.");
	cout << "\tYour name >>> ";
	cin >> usr->name;

	cout << "\tYour login ID";
	showSomeInfo("only numbers in 10~13 chars");
	auto idCount = 0;
	do {
		if (idCount) showSomeInfo("Bad ID format. Please input again.");
		cout << "\t\t>>> ";
		cin >> usr->ID;
		idCount++;
	} while (!isLegalAccount(usr->ID));

	cout << "\tYour password";
	showSomeInfo("must have 'letter' 'number' '_' \nthe last third char must be @");
	auto passwordCount = 0;
	do {
		if (passwordCount) showSomeInfo("Bad password format. Please input again.");
		cout << "\t\t>>> ";
		cin >> usr->password;
		passwordCount++;
	} while (!isLegalPassword(usr->password));

	cout << "\tYour age >>> ";
	cin >> usr->age;
	showSomeInfo("male is 0, female is 1");
	cout << "\tYour gender >>> ";
	cin >> usr->gender;
	cout << "\tYour Telephone number >>> ";
	cin >> usr->TEL;
	if (userManager.registerUser(usr)) {
		showSomeInfo("Welcome " + usr->name + ". \n"
					 "Please remember your ID: " + usr->ID +
					 ". That's a significant info for you to log in.");
		saveConfigurations();
	} else {
		showSomeInfo("Sorry, the ID:" + usr->ID + " you've used, has been registered in this system.\n"
					 "Please change another one.");
	}
	currentFunction = "HOMEPAGE";
}

void WeBankOS::cardsFunc() {
	if (!loggedUser) {
		showSomeInfo("	No permission here. Please logged in first.");
		cin.ignore(1024, '\n');
		return;
	}
	string op;
	cin >> op;
	flush();
	if (op == "-add") {
		addCard();
	} else if (op == "-cancel") {
		cancelCard();
	} else if (op == "-dep") {
		depositCash();
	} else if (op == "-wit") {
		withdrawCash();
	} else if (op == "-det") {
		showReceiptsAndDisbursementsDetails();
	} else { showSomeInfo("Bad argument `" + op + "` for command `card`."); }

}

void WeBankOS::addCard() {
	cout << endl;

	string password;
	cout << "\tInput your new card's password >>> ";
	cin >> password;
	fundsManager->registerICCard(password);
	showSomeInfo("Your new card number is: " + loggedUser->cards.back() + ".\n"
				 "You needn't to remember your card. \n"
				 "You can get the number by input `ls` as free.");

}
void WeBankOS::cancelCard() {
	cout << endl;

	string cardID, password;
	cout << "\tInput your card's ID >>> ";
	cin >> cardID;
	cout << "\tInput your card's password >>> ";
	cin >> password;

	const auto tempICCard = fundsManager->verifyICCard(cardID, password);
	if (tempICCard) {
		showSomeInfo("Your card[ " + cardID + " ] will be deleted from our system.\n"
					 "Balance:[" + to_string(tempICCard->balance) + "].Confirm? [Y/n]");
		printPrompt();
		string res;
		cin >> res;
		if (std::tolower(res[0]) == 'y') {
			fundsManager->cancelICCard(tempICCard);
		} else { showSomeInfo("You canceled."); }
	} else { showSomeInfo("Can't verify your account. Please check you password and account."); }
}
void WeBankOS::depositCash() {
	cout << endl;
	string cardID, password;
	auto cash = 0;
	cout << "Please input your CardID >>> ";
	cin >> cardID;
	cout << "Please input your Password >>> ";
	cin >> password;

	auto badCount = 0;
	do {
		if (badCount) showSomeInfo("\tCash must > 0.");
		cout << "Cash >>> ";
		cin >> cash;
		badCount++;
	} while (cash <= 0);

	const auto tempICCard = fundsManager->verifyICCard(cardID, password);
	if (tempICCard) {
		fundsManager->depositCash(tempICCard, cash);
		showSomeInfo("Delta Cash \t[" + std::to_string(cash) + "]\n"
					 "Current Time \t[" + TimeUtils::toNormalTime(TimeUtils::getTimeStamp()) + "]\n"
					 "Current Balance \t[" + std::to_string(tempICCard->balance) + "]");
	} else { showSomeInfo("Can't verify your account. Please check you password and account."); }
}
void WeBankOS::withdrawCash() {
	cout << endl;
	string cardID, password;
	auto cash = 0;
	cout << "Please input your CardID >>> ";
	cin >> cardID;
	cout << "Please input your Password >>> ";
	cin >> password;

	const auto tempICCard = fundsManager->verifyICCard(cardID, password);
	if (tempICCard) {
		showSomeInfo("\tCurrent Balance [ " + std::to_string(tempICCard->balance) + " ]");

		auto badCount = 0;
		do {
			if (badCount) showSomeInfo("\tCash must be multiple of 100.");
			cout << "Cash >>> ";
			cin >> cash;
			badCount++;
		} while (cash < 0 || cash % 100);
		
		if (fundsManager->withdrawCash(tempICCard, cash)) {
			showSomeInfo("Delta Cash \t[" + std::to_string(cash) + "]\n"
						 "Current Time \t[" + TimeUtils::toNormalTime(TimeUtils::getTimeStamp()) + "]\n"
						 "Current Balance \t[" + std::to_string(tempICCard->balance) + "]");
		} else { showSomeInfo("Sorry. Please check you balance. Deal failed."); }

	} else { showSomeInfo("Can't verify your account. Please check you password and account."); }
}
void WeBankOS::showReceiptsAndDisbursementsDetails() {
	showSomeInfo("Your Receipts and disbursements details: ");

	auto allDetails = fundsManager->getReceiptsAndDisbursementsDetails();

	const auto perPageCount = 5;
	int curIndex = 1;
	int maxIndex = allDetails.size() / perPageCount + !!(allDetails.size() % perPageCount);

	while (true) {
		cout << "Pages: ";
		for (int i = 1; i <= maxIndex; i++) {
			if (i == curIndex) {
				cout << "[" << i << "]";
			} else { cout << " " << i << " "; }
		}
		cout << "`0` to be back" << endl;
		cout << ">>> ";
		cin >> curIndex;
		cout << endl;
		if (!curIndex) {
			break;
		}
		const auto tempIndex = (curIndex - 1) * perPageCount;
		for (auto i = 0; i < perPageCount && tempIndex + i < allDetails.size(); i++) {
			cout << "\t" <<TimeUtils::toNormalTime(allDetails[tempIndex+i]->opTime)<<"	"<< allDetails[tempIndex + i]->account << "\t";
			if (allDetails[tempIndex + i]->amount < 0) {
				cout << "outcome : [ " << -allDetails[tempIndex + i]->amount << " ]" << endl;
			} else {
				cout << "income  : [ " << allDetails[tempIndex + i]->amount << " ]" << endl;
			}
		}
		cout << endl;
	}
}

void WeBankOS::listCards() {
	if (!loggedUser) {
		showSomeInfo("	No permission here. Please logged in first.");
		flush();
		return;
	}
	cout << endl;
	for (const auto& card : loggedUser->cards) {
		cout << "\t" << card << endl;
	}
	cout << endl << "All your cards have(s) been list above." << endl;
}

void WeBankOS::calcBigNum() {
	string num1, op, num2;
	cin >> num1 >> op >> num2;
	if (op == "+") {
		cout << add(num1, num2) << endl;
	} else if (op == "-") {
		cout << sub(num1, num2) << endl;
	} else { showSomeInfo("	Bad Operator: Only support + and -."); }
}

void WeBankOS::loadConfigurations() {
	fileManager->loadData(&userManager);
	fileManager->loadData(&icCardsManager);
}

void WeBankOS::saveConfigurations() {
	fileManager->savedData(&userManager);
	fileManager->savedData(&icCardsManager);
}

void WeBankOS::clearScreen() {
	system("cls");
}

bool WeBankOS::isRunning() const {
	return running;
}

void WeBankOS::exitOS() {
	running = false;
	saveConfigurations();
	setTextColor(HIGHLIGHT_COLOR);
	cout << endl << getUserName() << ".Thank you for using this OS." << endl << endl;
	setTextColor(0x0F);
}

void WeBankOS::showSomeInfo(const string& errorInfo) {
	setTextColor(HIGHLIGHT_COLOR);
	cout << endl << errorInfo << endl << endl;
	setTextColor(0x0F);
}

string WeBankOS::getUserName() const {
	return loggedUser ? loggedUser->name : "Guest";
}

/**
 * \brief
 * \param cmd the command you want to show;
 * \param description the description of this command;
 */
// ReSharper disable once CppMemberFunctionMayBeStatic
void WeBankOS::showOneItemOfHelp(const string& cmd, const string& description) {
	setTextColor(HIGHLIGHT_COLOR);
	cout << "    " << cmd << "\t";
	setTextColor(0x09);
	cout << description << endl;
	setTextColor(0x0F);
}
