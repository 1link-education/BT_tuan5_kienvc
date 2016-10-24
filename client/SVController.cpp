// SVController client
#undef max
#include "SVController.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <io.h>
#include <conio.h>
#include "rapidjson\document.h"
#include "rapidjson\stringbuffer.h"
#include "rapidjson\prettywriter.h"

using namespace std;
using namespace rapidjson;

SVController::SVController()
{
	sosv = 0;
	//ds = new SinhVien;
}

SVController::SVController(SVView view)
{
	//this->ds = ds;
	this->view = view;
	sosv = 0;
}

void SVController::setSosv(int n)
{
	sosv = n;
}
int SVController::getSosv()
{
	return sosv;
}
SinhVien SVController::nhapThongTin()
{
	SinhVien sv;
	string ten, diachi, sbd, gioitinh, temp;
	float toan, ly, hoa;
	fflush(stdin);
	cout << "\tTen: ";
	getline(cin, ten);
	cout << "\tSbd: ";
	getline(cin, sbd);
	cout << "\tDia chi: ";
	getline(cin, diachi);
	cout << "\tGioi tinh: ";
	getline(cin, gioitinh);
	do{
		fflush(stdin);
		cout << "\tDiem toan: ";
		getline(cin, temp);
		stringstream myStream(temp);
		myStream >> toan;
	}while(toan < 0 || toan > 10);
	do{
		fflush(stdin);
		cout << "\tDiem ly: ";
		getline(cin, temp);
		stringstream myStream(temp);
		myStream >> ly;
	}while(ly < 0 || ly > 10);
	do{
		cout << "\tDiem hoa: ";
		fflush(stdin);
		getline(cin, temp);
		stringstream myStream(temp);
		myStream >> hoa;
	}while(hoa < 0 || hoa > 10);
	sv = SinhVien(ten, sbd, diachi, gioitinh, toan, ly, hoa);
	return sv;
}

void SVController::xuatDs()
{
	cout << "Tong so sinh vien: " << sosv << "\n";
	for(int i = 0; i < sosv; i++){
		cout << "-------------------------\nSinh vien thu " << i+1 << ":\n";
		view.view(ds[i]);
	}
}

void SVController::recvSV(int index, string buff)
{
	Document jsondoc;
	StringBuffer sbuffer;
	PrettyWriter<StringBuffer> pwriter(sbuffer);
	jsondoc.Parse(buff.c_str());
	jsondoc.Accept(pwriter);

	string s = sbuffer.GetString();
	ds[index] = SinhVien(jsondoc["Ten"].GetString(), jsondoc["SBD"].GetString(), jsondoc["Dia chi"].GetString(), jsondoc["Gioi tinh"].GetString(),
		jsondoc["toan"].GetDouble(),jsondoc["ly"].GetDouble(),jsondoc["hoa"].GetDouble());	
}

string SVController::sendSV(int index)
{
	Document jsonDoc;
	StringBuffer sbuffer;
	PrettyWriter<StringBuffer> pwriter(sbuffer);

	ostringstream buffer1, buffer2, buffer3;
	buffer1 << ds[index].getToan();
	string toan = buffer1.str();
	buffer2 << ds[index].getLy();
	string ly = buffer2.str();
	buffer3 << ds[index].getHoa();
	string hoa = buffer3.str();


	string s = "{\"Ten\":\""+ds[index].getTen()+"\",\"SBD\":\""+ds[index].getSbd()+"\",\"Dia chi\":\""+ds[index].getDiachi()+"\",\"Gioi tinh\":\""+ds[index].getGioitinh()+"\",\"toan\":"+toan+",\"ly\":"+ly+",\"hoa\":"+hoa+"}";

	jsonDoc.Parse(s.c_str());
	jsonDoc.Accept(pwriter);

	string s2;
	s2=sbuffer.GetString();
	return s2;
}