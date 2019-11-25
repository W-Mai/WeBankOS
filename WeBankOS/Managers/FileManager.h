#pragma once

#include "../FileGroup.h"

class FileManager {
	string mainFilePath;
public:
	FileManager(const string& mainDir);
	void loadData(UserManager * userManager);
	void loadData(ICCardsManager* icCardsManager);
	void loadData(FundsManager* fundsManager);

	void savedData(UserManager* userManager) const;
	void savedData(ICCardsManager* icCardsManager);
	void savedData(FundsManager* fundsManager);
};

