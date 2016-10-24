// bt1_4.cpp : Defines the entry point for the console application.
//
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "stdafx.h"
#include "UI.h"
#define _WINSOCKAPI_
#include <Windows.h>
#include <winsock2.h>
#include <iostream>
#include <process.h>
#include <fstream>
#include <conio.h>

#pragma comment(lib, "Ws2_32.lib")

#define SERVER_PORT 12345
#define BUF_SIZE 4096  // block transfer size  
#define SERVER_ADDR "127.0.0.1" 

using namespace std;

CRITICAL_SECTION critical;
HANDLE ghSemaphore[3];
static SVController ds;
	
string recvMes(SOCKET client);
void sendMes(SOCKET client, string buff);

unsigned __stdcall FolderFilesWatchThread(LPVOID lpParam) // thread procedure
{
	WIN32_FIND_DATA file_data;
	ofstream file;
	SYSTEMTIME  st;
	FILETIME    ft;

	HANDLE hFileChange = FindFirstChangeNotification((LPTSTR)lpParam, // folder path
		FALSE,            // don't look in subfolders
		FILE_NOTIFY_CHANGE_FILE_NAME); 

	if(INVALID_HANDLE_VALUE == hFileChange)
	{
		cout << "\n ERROR: FindFirstChangeNotification function failed.\n";
		DWORD dwError = GetLastError();
		// handle error (see this FAQ)
		return dwError;
	}
	GetSystemTime(&st);
	WaitForSingleObject(hFileChange, INFINITE);

	while(TRUE)
	{
		int i = 0;
		//WaitForSingleObject(hFileChange, INFINITE);

		//while(!TryEnterCriticalSection(&critical)){}
		HANDLE listFile = FindFirstFile(L"DIEM_THI_2016\\*", &file_data);
		file.open("output.txt");
		while(listFile != INVALID_HANDLE_VALUE)
		{
			i++;
			if(i > 2){
				wstring tmp = L"DIEM_THI_2016\\";
				SystemTimeToFileTime(&st,&ft);
				if(CompareFileTime(&ft, &file_data.ftLastAccessTime) == -1){
					wstring dir1(file_data.cFileName);
					tmp += dir1;
					string dir2(tmp.begin(), tmp.end());
					file << dir2 << "\n";
				}
			}
			if(FindNextFile(listFile, &file_data) == FALSE)
				break;
		}
		file.close();
		if (!ReleaseSemaphore( 
			ghSemaphore[0],  // handle to semaphore
			1,            // increase count by one
			NULL) )       // not interested in previous count
		{
			printf("ReleaseSemaphore[0] error: %d\n", GetLastError());
		}
		FindNextChangeNotification(hFileChange);
		//LeaveCriticalSection(&critical);
		GetSystemTime(&st);
		WaitForSingleObject(hFileChange, INFINITE);
		WaitForSingleObject(ghSemaphore[1], INFINITE);


	}
	CloseHandle(hFileChange);
  	return 0;
}
unsigned __stdcall readData(void* Param) // thread procedure
{	
	ifstream file;
	//SVController ds = *(SVController*) Param;

	while(1)
	{
		WaitForSingleObject( ghSemaphore[0],   // handle to semaphore
			INFINITE);           // zero-second 
		//while(!TryEnterCriticalSection(&critical)){}
		WaitForSingleObject(ghSemaphore[2], INFINITE);

		ds.nhapFiles("output.txt");

		//LeaveCriticalSection(&critical);
		if (!ReleaseSemaphore( 
			ghSemaphore[2],  // handle to semaphore
			1,            // increase count by one
			NULL) )       // not interested in previous count
		{
			printf("ReleaseSemaphore[2] error: %d\n", GetLastError());
		}
		if (!ReleaseSemaphore( 
			ghSemaphore[1],  // handle to semaphore
			1,            // increase count by one
			NULL) )       // not interested in previous count
		{
			printf("ReleaseSemaphore error[1]: %d\n", GetLastError());
		}
	}
	return 0;
}

unsigned __stdcall listenClient(void* param)
{
	//Step 1: Initiate WinSock
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2,2);
	if(WSAStartup(wVersion, &wsaData))
		cout << "Version is not supported\n";

	//Step 2: Construct socket	
	SOCKET listenSock;
	listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//Step 3: Bind address to socket
	sockaddr_in serverAddr;	
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

	if(bind(listenSock,(sockaddr *)&serverAddr, sizeof(serverAddr)))
	{
		cout << "Error! Cannot bind this address." << endl;
		_getch();
		return 0;
	}

	//Step 4: Listen request from client
	if(listen(listenSock, 10)){
		cout << "Error! Cannot listen." << endl;
		_getch();
		return 0;
	}

	cout << "Server started!" << endl;

	SOCKET connSock;

	sockaddr_in clientAddr;
	int clientAddrLen = sizeof(clientAddr);
	int ret;
	char buff[BUF_SIZE];
	string s = "";
	//accept request
	connSock = accept(listenSock, (sockaddr *) & clientAddr, &clientAddrLen);
	cout << "connSocket: " << connSock << endl;

	while(1){
		//receive message from client
		memset(buff, 0, BUF_SIZE);
		ret = recv(connSock, buff, BUF_SIZE, 0);
		if(ret == SOCKET_ERROR){
			cout << "Error : " << WSAGetLastError() << endl;
			break;
		}else if (strlen(buff) > 0){
			int i = atoi(buff);
			int sosv = ds.getSosv(), index;
			string sbd, ten, tong, temp1, temp2;
			vector<string> v;
			WaitForSingleObject(ghSemaphore[2], INFINITE);
			switch(i)
			{
			case 1:
				for(int count = 0; count < sosv; count ++){
					s = ds.sendSV(count);
					sendMes(connSock, s);
					recvMes(connSock);
				}
				sendMes(connSock, "done");
				break;
			case 2:
				sendMes(connSock, "ok");
				sbd = recvMes(connSock);
				v = ds.timkiem2("sbd", sbd);
				for(size_t i = 0; i < v.size(); i++){
					sendMes(connSock, v[i]);
					recvMes(connSock);
				}
				sendMes(connSock, "done");
				break;
			case 3:
				sendMes(connSock, "ok");
				ten = recvMes(connSock);
				v = ds.timkiem2("ten", sbd);
				for(size_t i = 0; i < v.size(); i++){
					sendMes(connSock, v[i]);
					recvMes(connSock);
				}
				sendMes(connSock, "done");
				break;
			case 4:
				sendMes(connSock, "ok");
				tong = recvMes(connSock);
				v = ds.timkiem2("tong", tong);
				for(size_t i = 0; i < v.size(); i++){
					sendMes(connSock, v[i]);
					recvMes(connSock);
				}
				sendMes(connSock, "done");
				break;
			case 5:
				sendMes(connSock, "ok");
				temp1 = recvMes(connSock);
				sendMes(connSock, "ok");
				temp2 = recvMes(connSock);
				if(temp1.compare("toan") == 0)
					v = ds.timkiem2("toan", temp2);
				if(temp1.compare("ly") == 0)
					v = ds.timkiem2("ly", temp2);
				if(temp1.compare("hoa") == 0)
					v = ds.timkiem2("hoa", temp2);
				for(size_t i = 0; i < v.size(); i++){
					sendMes(connSock, v[i]);
					recvMes(connSock);
				}
				sendMes(connSock, "done");
				break;
			case 6:
				ds.sapxep("ten");
				for(int count = 0; count < sosv; count ++){
					s = ds.sendSV(count);
					sendMes(connSock, s);
					recvMes(connSock);
				}
				sendMes(connSock, "done");
				break;
			case 7:
				ds.sapxep("sbd");
				for(int count = 0; count < sosv; count ++){
					s = ds.sendSV(count);
					sendMes(connSock, s);
					recvMes(connSock);
				}
				sendMes(connSock, "done");
				break;
			case 8:
				ds.sapxep("tong");
				for(int count = 0; count < sosv; count ++){
					s = ds.sendSV(count);
					sendMes(connSock, s);
					recvMes(connSock);
				}
				sendMes(connSock, "done");
				break;
			case 9:
				sendMes(connSock,"ok");
				s = recvMes(connSock);
				sendMes(connSock, "ok");
				if(s.compare("xoa") == 0){
					temp1 = recvMes(connSock);
					sendMes(connSock, "ok");
					temp2 = recvMes(connSock);
					sendMes(connSock,ds.xoa2(temp1, temp2));
				}
				if(s.compare("sua") == 0){
					temp1 = recvMes(connSock);
					sendMes(connSock, "ok");
					temp2 = recvMes(connSock);
					index = ds.capnhat2(temp1, temp2);
					if(index == -1)
						sendMes(connSock, "khong");
					else{
						sendMes(connSock, "ok");
						ds.recvSV(index, recvMes(connSock));
						sendMes(connSock, "ok");
					}
				}
				break;
			case 10:
				sendMes(connSock, "ok");
				while(1){
					s = recvMes(connSock);
					if( s.compare("done") == 0){
						sendMes(connSock, "ok");
						break;
					}
					ds.recvSV(ds.getSosv(), s);
					ds.setSosv(ds.getSosv() + 1);
					sendMes(connSock, "ok");
				}
				break;
			case 11:
				sendMes(connSock, "ok");
				s = recvMes(connSock);
				v = ds.thongke2(s);
				for(size_t i = 0; i < v.size(); i++){
					sendMes(connSock, v[i]);
					recvMes(connSock);
				}
				sendMes(connSock, "done");
				break;
			case 12:
				sendMes(connSock, "ok");
				closesocket(connSock);
				break;
			}
			if (!ReleaseSemaphore( 
				ghSemaphore[2],  // handle to semaphore
				1,            // increase count by one
				NULL) )       // not interested in previous count
			{
				printf("ReleaseSemaphore[2] error: %d\n", GetLastError());
			}
		}
	}
	return 0;
}

int main(int argc, char argv[])
{

	SVView view;
	ds = SVController(view);
	UI ui;


	ghSemaphore[0] = CreateSemaphore( NULL, 0, 1, NULL);
	ghSemaphore[1] = CreateSemaphore( NULL, 0, 1, NULL);
	ghSemaphore[2] = CreateSemaphore( NULL, 1, 1, NULL);

	_beginthreadex(0, 0, FolderFilesWatchThread, _T("DIEM_THI_2016") , 0, 0);
	_beginthreadex(0, 0 ,readData, NULL , 0, 0);
	_beginthreadex(0, 0 ,listenClient, NULL, 0, 0);

	ui.xuly(&ds,&ghSemaphore[2]);

	CloseHandle(ghSemaphore[0]);
	CloseHandle(ghSemaphore[1]);
	CloseHandle(ghSemaphore[2]);


	return 0;
}

string recvMes (SOCKET client)
{
	char buff[BUF_SIZE];
	int ret;

	//Receive echo message
	ret = recv(client, buff, BUF_SIZE, 0);
	if(ret  == SOCKET_ERROR){
		if (WSAGetLastError() == WSAETIMEDOUT)
			printf("Time-out!");
		else cout << "Error! Cannot receive message." << endl;
	}
	else if (strlen(buff) > 0){
		buff[ret] = 0;
	}
	
	string s = string(buff);
	return s;
}

void sendMes (SOCKET client, string buff)
{	
	int ret;

	ret = send(client, buff.c_str(), strlen(buff.c_str()), 0);
	if(ret  == SOCKET_ERROR)
		cout << "Error! Cannot send mesage." << endl;

}