#pragma once
#include "SVController.h"
#include <Windows.h>

class UI
{
public:
	int xuatMenu(); // in menu, tra ve lua chon
	void xuly(SVController *ds, HANDLE* ghSemaphore);// xu ly cac case menu
};