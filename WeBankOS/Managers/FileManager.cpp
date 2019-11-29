#include "FileManager.h"
#include <fstream>
#include <io.h>
#include <sstream>
#include <direct.h>

void FileManager::completeDirectors() const {
	if (_access((mainFilePath + DATA_PATH).c_str(), 0)) {
		_mkdir((mainFilePath +DATA_PATH).c_str());
	}
	if (_access((mainFilePath + WEUSERS_PATH).c_str(), 0)) {
		_mkdir((mainFilePath + WEUSERS_PATH).c_str());
	}
	if (_access((mainFilePath + ICCARD_PATH).c_str(), 0)) {
		_mkdir((mainFilePath + ICCARD_PATH).c_str());
	}
	if (_access("./lock", 0)) {
		_mkdir("./lock");
	}
}

vector<string>* FileManager::fileSearch(string path) {
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
	completeDirectors();
}
void FileManager::loadData(UserManager* userManager) {
	fstream fs;
	auto users = &userManager->weUsers;
	const auto fileList = fileSearch(mainFilePath + WEUSERS_PATH);
	
	for (const auto& fileName:*fileList) {
		fs.open(mainFilePath + WEUSERS_PATH"/" + fileName, ios::in | ios::binary);
		if (fs) {
			size_t fileSize;
			fs.read(reinterpret_cast<char*>(&fileSize), sizeof(fileSize));
			//fileSize = 543;
			auto buffer = new char[fileSize + sizeof(fileSize)];
			*reinterpret_cast<size_t*> (buffer) = fileSize;
			fs.read(buffer + sizeof(fileSize), fileSize);
			auto tmpUser = new WeUser;
			tmpUser->loadData(buffer);
			users->push_back(tmpUser);
			delete[] buffer;
			fs.close();
		}
	}
}
void FileManager::loadData(ICCardsManager* icCardsManager) {
	fstream fs;
	fs.open(mainFilePath + ICCARD_PATH"/" + "ICCards.icard", ios::in | ios::binary);
	if (fs) {
		auto cards = &icCardsManager->icCards;
		const auto cardSize = ICCard().getSize();
		while(fs.peek(), !fs.eof()) {
			auto buffer = new char[cardSize];
			auto tempCard = new ICCard;
			fs.read(buffer, cardSize);
			tempCard->loadData(buffer);
			cards->push_back(tempCard);
			//cout << "#### " << tempCard->account << endl;
			delete[] buffer;
		}
		fs.close();
	}
}

void FileManager::savedData(UserManager* userManager) const {
	fstream fs;

	auto users = userManager->weUsers;
	for (auto it = users.begin();it!=users.end();++it) {
		auto tmpUser = *it;
		fs.open(mainFilePath + WEUSERS_PATH"/" + tmpUser->name, ios::out | ios::binary);
		tmpUser->getData();
		fs.write(static_cast<char*>(tmpUser->getData()), tmpUser->getSize());
		fs.close();
	}
}
void FileManager::savedData(ICCardsManager* icCardsManager) {
	fstream fs;
	fs.open(mainFilePath + ICCARD_PATH"/" + "ICCards.icard", ios::out | ios::binary);
	if (fs) {
		auto cards = icCardsManager->icCards;
		for (auto it : cards) {
			fs.write(static_cast<char*>(it->getData()), it->getSize());
		}
		fs.close();
	}
}


