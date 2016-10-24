// UI client
#pragma once
#include "SVController.h"
#include "winsock2.h"
#include <string>

#pragma comment(lib, "Ws2_32.lib")

class UI
{
public:
	int xuatMenu();
	void xuly(SVController *ds, SOCKET client);
	string recvMes(SOCKET client);// nhan buffer, tra ve string nhan duoc
	void sendMes(SOCKET client, string buff);// gui buffer, param: string gui di
};