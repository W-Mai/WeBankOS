#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#define DEBUG

using namespace std;



class WeUser;
class ICCard;

class UserManager;
class ICCardsManager;
class FileManager;
class FundsManager;

class WeBankOS;

class ReceiptAndDisbursement;

class DataPack;
class XData;

#include "./XData/XData.h"

#include "WeBankOS.h"

#include "./DataContainer/ICCard.h"
#include "./DataContainer/WeUser.h"

#include "./Managers/FileManager.h"
#include "./Managers/ICCardsManager.h"
#include "./Managers/FundsManager.h"
#include "./Managers/UserManager.h"