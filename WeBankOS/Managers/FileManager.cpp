#include "FileManager.h"
#include <fstream>
#include <io.h>





FileManager::FileManager(const string& mainDir) {
	mainFilePath = mainDir;
}
void FileManager::loadData(UserManager* userManager) {
	
}
void FileManager::loadData(ICCardsManager* icCardsManager) {}
void FileManager::loadData(FundsManager* fundsManager) {}
void FileManager::savedData(UserManager* userManager) const {
	fstream fs;
	auto users = userManager->weUsers;
	for (auto it = users.begin();it!=users.end();++it) {
		auto tmpUser = *it;
		fs.open(mainFilePath + "/Data/Users/" + tmpUser->name, ios::out | ios::binary);
		(char*)tmpUser->getData();
		fs.write((char*)tmpUser->getData(), tmpUser->getSize());
		fs.close();
	}
	
}
void FileManager::savedData(ICCardsManager* icCardsManager) {}
void FileManager::savedData(FundsManager* fundsManager) {}

