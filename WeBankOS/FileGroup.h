#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#define DEBUG

#ifdef DEBUG
#define DE(n) std::cout << "OK [" << n << "]" << std::endl;
#else
#define DE(n)
#endif // DEBUG

using namespace std;

typedef string AccountType;

class WeUser;
class ICCard;

class UserManager;
class ICCardsManager;
class FileManager;
class FundsManager;

class WeBankOS;

struct ReceiptAndDisbursement;

#include "WeBankOS.h"

#include "./DataContainer/ICCard.h"
#include "./DataContainer/WeUser.h"

#include "./Managers/FileManager.h"
#include "./Managers/ICCardsManager.h"
#include "./Managers/FundsManager.h"
#include "./Managers/UserManager.h"

#include "./XData/XData.h"
