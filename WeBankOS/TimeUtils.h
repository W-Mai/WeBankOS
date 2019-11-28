#pragma once
#include <ctime>
#include <string>

class TimeUtils {
public:
	static time_t getTimeStamp();
	static std::string toNormalTime(time_t time);
};

