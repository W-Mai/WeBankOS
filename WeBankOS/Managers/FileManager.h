#pragma once

#include "../FileGroup.h"

#define DATA_PATH       "/Data"
#define WEUSERS_PATH    DATA_PATH "/WeUsers"
#define ICCARD_PATH     DATA_PATH "/ICCards"

class FileManager {
	string mainFilePath;
public:
	void completeDirectors() const;
	vector<string>* fileSearch(string path);
	FileManager(const string& mainDir);
	void loadData(UserManager * userManager);
	void loadData(ICCardsManager* icCardsManager);

	void savedData(UserManager* userManager) const;
	void savedData(ICCardsManager* icCardsManager);

};

