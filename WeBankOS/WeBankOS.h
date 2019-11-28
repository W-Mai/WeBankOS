#pragma once

#include "FileGroup.h"
#include <map>

#define HIGHLIGHT_COLOR 0x0E

class WeBankOS {
	typedef void(WeBankOS::* FunctionType)();

	class Functions {
		map<string, FunctionType> funMap;
		WeBankOS* os;
	public:
		explicit Functions(WeBankOS* p);
		void registerFunction(const string& name, FunctionType func);
		bool callFunction(const string& name);
	};
	
	Functions* functions;

	bool running;
	UserManager userManager;
	ICCardsManager icCardsManager;
	FundsManager* fundsManager;
	FileManager* fileManager;

	WeUser* loggedUser = nullptr;

	string currentFunction;
	void printPrompt();
	static void setTextColor(char color);
	void exitOS();
	void showSomeInfo(const string& errorInfo);
	
	string getUserName() const;
	void login();
	void logout();
	void registerUser();

	void queryBalance();
	void cardsFunc();
	void addCard();
	void cancelCard();
	void depositCash();
	void withdrawCash();
	void showReceiptsAndDisbursementsDetails();
	
	void listCards();
	void calcBigNum();
	void loadConfigurations();
	void saveConfigurations();

	void clearScreen();
	void help();
	void showOneItemOfHelp(const string& cmd, const string& description);
public:
	explicit WeBankOS(const string& dataFilePath);
	void init() const;
	void run();

	bool isRunning() const;




};

