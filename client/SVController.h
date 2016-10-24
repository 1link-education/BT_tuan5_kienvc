//SVController client
#pragma once
#include "SVView.h"
#include "SV.h"
#include <string>

class SVController
{
private:
	int sosv;
	SVView view;
public:
	SinhVien ds[1000];

	//constructor
	SVController();
	SVController(SVView view);

	void setSosv(int n);
	int getSosv();
	SinhVien nhapThongTin();
	void xuatDs();
	void recvSV(int index, string buff);
	string sendSV(int index);
};
