#include <iostream>

#include "FileGroup.h"
#include "WeBankOS.h"
#include "FileManager.h"

#include "ICCard.h"
#include "ICCardsManager.h"
#include "FundsManager.h"
#include "WeUser.h"
#include "UserManager.h"


WeBankOS g_WeBankOS;

int main() {
	g_WeBankOS.run();
	return 0;
}