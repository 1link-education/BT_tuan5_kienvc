// client.cpp : Defines the entry point for the console application.
//
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "UI.h"
#include "stdafx.h"
#include "winsock2.h"
#include "conio.h"
#include "rapidjson\document.h"
#include "rapidjson\stringbuffer.h"
#include "rapidjson\prettywriter.h"
#include <string>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

#define SERVER_PORT 12345
#define SERVER_ADDR "127.0.0.1"
#define BUFF_SIZE 4096

using namespace std;
using namespace rapidjson;


int main(int argc, char* argv[])
{
	SVController ds;
	UI ui;
	
	//Step 1: Inittiate WinSock
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2,2);
	if(WSAStartup(wVersion, &wsaData))
		printf("Version is not supported\n");

	//Step 2: Construct socket	
	SOCKET client;
	client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//(optional) Set time-out for receiving
	int tv = 10000; //Time-out interval: 10000ms
	setsockopt(client, SOL_SOCKET, SO_RCVTIMEO,	(const char*)(&tv), sizeof(int));

	//Step 3: Specify server address
	sockaddr_in serverAddr;	
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

	//Step 4: Request to connect server
	if(connect(client, (sockaddr *) &serverAddr, sizeof(serverAddr))){
		printf("Error! Cannot connect server. %d",WSAGetLastError());
		_getch();
		return 0;
	}
	printf("Connected server!\n");
	
	ui.xuly(&ds, client);

	return 0;
}

