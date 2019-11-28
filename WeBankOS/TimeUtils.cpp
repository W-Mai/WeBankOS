#include "TimeUtils.h"

#include <ctime>


time_t TimeUtils::getTimeStamp() {
	return std::time(nullptr);
}

std::string TimeUtils::toNormalTime(time_t time) {
	tm time_s;
	char buffer[100];
	localtime_s(&time_s, &time);
	strftime(buffer, 100, "%F %T", &time_s);
	return buffer;
}