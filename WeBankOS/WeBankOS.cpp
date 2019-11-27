#include <iostream>
#include "WeBankOS.h"
#include <windows.h>


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
	functions->registerFunction("exit", static_cast<FunctionType>(&WeBankOS::exitOS));
	functions->registerFunction("q", static_cast<FunctionType>(&WeBankOS::exitOS));
	functions->registerFunction("help", static_cast<FunctionType>(&WeBankOS::help));
	functions->registerFunction("load_conf", static_cast<FunctionType>(&WeBankOS::loadConfigurations));
	//Register all the functions END.

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
}

void WeBankOS::login() {
	string name, password;
	cin >> name >> password;
	cout << "Welcome " << name << endl;
}

void WeBankOS::loadConfigurations() {
	fileManager->loadData(&userManager);
	fileManager->loadData(&icCardsManager);
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

string WeBankOS::getUserName() const {
	return loggedUser ? loggedUser->name : "Guest";
}

void WeBankOS::help() {
	setTextColor(HIGHLIGHT_COLOR);
	cout << endl;
	
	showOneItemOfHelp("help", "to show the help of this OS.");
	showOneItemOfHelp("q,exit", "exit this OS.");
	showOneItemOfHelp("login", "usage: \"login username password\" to login your account.");
	showOneItemOfHelp("load_conf", "load all the configurations.");
	
	cout << endl;
	setTextColor(0x0F);
}

/**
 * \brief 
 * \param cmd the command you want to show;
 * \param description the description of this command;
 */
void WeBankOS::showOneItemOfHelp(const string& cmd, const string& description) {
	setTextColor(HIGHLIGHT_COLOR);
	cout << "\t" << cmd <<"\t";
	setTextColor(0x09);
	cout << description << endl;
	setTextColor(0x0F);
}

