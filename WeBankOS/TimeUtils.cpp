#include "TimeUtils.h"

#include <ctime>
time_t TimeUtils::getTimeStamp() {
	return std::time(nullptr);
}
