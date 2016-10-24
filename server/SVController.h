#pragma once
#include "SVView.h"
#include "SV.h"
#include <string>
#include <vector>

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
	void nhapTay(int tmp, int index);// nhap "tmp" sinh vien tu vi tri index
	int nhapFile(const char *dir,int index);// nhap danh sach sinh vien tu file "dir" tu vi tri index  
	void nhapFiles(const char *dir);// nhap danh sach tu nhieu file torng folder "dir"
	bool luuDuLieu();// luu du lieu ra file
	void timkiem(string yeucau);// tim kiem sinh vien theo yeu cau
	void sapxep(string yeucau);// sap xep danh sach sinh vien theo yeu cau
	void xuatDs();// in danh sach sinh vien
	void capnhat(string yeucau);// thay doi thong tin sinh vien theo yeu cau
	void xoa(string yeucau);// xoa thong tin sinh vien
	void thongke(string yeucau);// thong ke danh sach sinh vien theo yeu cau
	string sendSV(int index);// parse object sinh vien thanh json string
	vector<string> timkiem2(string yeucau, string val);// tim kiem sinh vien, tra ve 1 vector json string
	vector<string> thongke2(string yeucau);// thong ke sinh vien, tra ve 1 vectro json string
	void recvSV(int index, string buff);// stringify json string thanh object  sinh vien
	string xoa2(string yeucau, string param);// phien ban cho socket 
	int capnhat2(string yeucau, string param);// phien ban cho socket
};
