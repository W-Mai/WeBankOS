#include <iostream>
#include "WeBankOS.h"
#include <windows.h>

std::string add(const std::string a, const std::string b);
std::string sub(const std::string a, const std::string b);

WeBankOS::Functions::Functions(WeBankOS* p) {
	os = p;
}

void WeBankOS::Functions::registerFunction(const string& name, FunctionType func) {
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
		"Type \"help\", \"copyright\" for more information." << endl << endl;

	//Register all the functions BEGIN.
	functions->registerFunction("login", static_cast<FunctionType>(&WeBankOS::login));
	functions->registerFunction("logout", static_cast<FunctionType>(&WeBankOS::logout));
	functions->registerFunction("register", static_cast<FunctionType>(&WeBankOS::registerUser));
	functions->registerFunction("exit", static_cast<FunctionType>(&WeBankOS::exitOS));
	functions->registerFunction("q", static_cast<FunctionType>(&WeBankOS::exitOS));
	functions->registerFunction("help", static_cast<FunctionType>(&WeBankOS::help));
	functions->registerFunction("load_conf", static_cast<FunctionType>(&WeBankOS::loadConfigurations));
	functions->registerFunction("cls", static_cast<FunctionType>(&WeBankOS::clearScreen));
	functions->registerFunction("calc", static_cast<FunctionType>(&WeBankOS::calcBigNum));

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
	showOneItemOfHelp("help", "to show the help of this OS.");
	showOneItemOfHelp("logout", "login out your account.");
	showOneItemOfHelp("register", "register a new user step by step.");
	showOneItemOfHelp("load_conf", "load all the configurations.");
	showOneItemOfHelp("calc", "calc big number(only + and - support).");

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
			cout << endl << "	Command Error: Bad Command \"" << command << "\"" << endl << endl;
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

	showSomeInfo("	" + getUserName() + ".Logout successfully.");

	delete loggedUser;
	loggedUser = nullptr;
	currentFunction = "HOMEPAGE";
}

void WeBankOS::registerUser() {
/*	if (!loggedUser) {
		showErrorInfo("\tNo Permission. Please LOGIN first.");
		return;
	}*/

	currentFunction = "LOGIN";


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

void WeBankOS::clearScreen() {
	system("cls");
}

bool WeBankOS::isRunning() const {
	return running;
}

void WeBankOS::exitOS() {
	running = false;
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

