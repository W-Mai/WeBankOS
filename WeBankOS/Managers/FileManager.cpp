#include "FileManager.h"
#include <fstream>
#include <io.h>
#include <sstream>


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


FileManager::FileManager(const string& mainDir) {
	mainFilePath = mainDir;
}
void FileManager::loadData(UserManager* userManager) {
	fstream fs;
	auto users = userManager->weUsers;
	auto fileList = fileSearch(mainFilePath + "/Data/Users/");
	
	for (auto fileName:*fileList) {
		fs.open(mainFilePath + "/Data/Users/" + fileName, ios::in | ios::binary);
		if (fs) {
			size_t fileSize;
			fs.read(reinterpret_cast<char*>(&fileSize), sizeof(fileSize));
			//fileSize = 543;
			auto buffer = new char[fileSize + sizeof(fileSize)];
			*reinterpret_cast<size_t*> (buffer) = fileSize;
			fs.read(buffer + sizeof(fileSize), fileSize);
			auto tmpUser = new WeUser;
			tmpUser->loadData(buffer);
			users.push_back(tmpUser);
			delete buffer;
			fs.close();
		}

	}
}
void FileManager::loadData(ICCardsManager* icCardsManager) {}
void FileManager::loadData(FundsManager* fundsManager) {}
void FileManager::savedData(UserManager* userManager) const {
	fstream fs;
	auto users = userManager->weUsers;
	for (auto it = users.begin();it!=users.end();++it) {
		auto tmpUser = *it;
		fs.open(mainFilePath + "/Data/Users/" + tmpUser->name, ios::out | ios::binary);
		tmpUser->getData();
		fs.write((char*)tmpUser->getData(), tmpUser->getSize());
		fs.close();
	}
}
void FileManager::savedData(ICCardsManager* icCardsManager) {
	
}
void FileManager::savedData(FundsManager* fundsManager) {}

