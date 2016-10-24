// UI client
#include "UI.h"
#include <iostream>
#include <conio.h>

#define BUFF_SIZE 4096

int UI::xuatMenu()
{
	system("CLS");
	cout << "\n*******************************************************";
	cout << "\n*  1. Danh sach sinh vien                             *";
	cout << "\n*                                                     *";
	cout << "\n*  2. Tim kiem theo so bao danh                       *";
	cout << "\n*  3. Tim kiem theo ten sinh vien                     *";
	cout << "\n*  4. Tim kiem theo tong diem                         *";
	cout << "\n*  5. Tim kiem theo diem tung mon                     *";
	cout << "\n*                                                     *";
	cout << "\n*  6. Sap xep danh sach theo alphabet                 *";
	cout << "\n*  7. Sap xep danh sach theo so bao danh              *";
	cout << "\n*  8. Sap xep danh sach theo tong diem                *";
	cout << "\n*                                                     *";
	cout << "\n*  9. Thay doi thong tin sinh vien                    *";
	cout << "\n*  10. Them sinh vien vao danh sach                   *";
	cout << "\n*  11. Thong ke                                       *";
	cout << "\n*  12. Thoat chuong trinh                             *";
	cout << "\n*                                                     *";
	cout << "\n*******************************************************";
	cout << "\nChon chuc nang: ";
	int i = 0;
	cin >> i;
	system("CLS");
	return i;
}
void UI::xuly(SVController *ds_tmp, SOCKET client)
{
	int i = 0, n;
	char c;
	string s, tmp;
	SVView view;
	
	system("CLS");
	while (i = xuatMenu())
	{
		fflush(stdin);
		SVController ds = SVController(view);
		switch (i)
		{
		case 1:
			sendMes(client, "1");
			while(1){
				s = recvMes(client);
				if( s.compare("done") == 0)
					break;
				ds.recvSV(ds.getSosv(), s);
				ds.setSosv(ds.getSosv() + 1);
				sendMes(client, "ok");
			}
			ds.xuatDs();
			break;
		case 2:
			sendMes(client, "2");
			recvMes(client);
			cout << "Nhap so bao danh: ";
			fflush(stdin);
			getline(cin, tmp);
			sendMes(client, tmp);
			while(1){
				s = recvMes(client);
				if( s.compare("done") == 0)
					break;
				if( s.compare("khong") == 0){
					sendMes(client, "ok");
					continue;
				}
				ds.recvSV(ds.getSosv(), s);
				ds.setSosv(ds.getSosv() + 1);
				sendMes(client, "ok");
			}
			ds.xuatDs();
			break;
		case 3:
			sendMes(client, "3");
			recvMes(client);
			cout << "Nhap ten: ";
			fflush(stdin);
			getline(cin, tmp);
			sendMes(client, tmp);
			while(1){
				s = recvMes(client);
				if( s.compare("done") == 0)
					break;
				if( s.compare("khong") == 0){
					sendMes(client, "ok");
					continue;
				}
				ds.recvSV(ds.getSosv(), s);
				ds.setSosv(ds.getSosv() + 1);
				sendMes(client, "ok");
			}
			ds.xuatDs();
			break;
		case 4:
			sendMes(client, "4");
			recvMes(client);
			cout << "Nhap tong diem: ";
			fflush(stdin);
			getline(cin, tmp);
			sendMes(client, tmp);
			while(1){
				s = recvMes(client);
				if( s.compare("done") == 0)
					break;
				if( s.compare("khong") == 0){
					sendMes(client, "ok");
					continue;
				}
				ds.recvSV(ds.getSosv(), s);
				ds.setSosv(ds.getSosv() + 1);
				sendMes(client, "ok");
			}
			ds.xuatDs();
			break;
		case 5:
			sendMes(client, "5");
			recvMes(client);
			cout << "Nhap mon hoc: ";
			fflush(stdin);
			getline(cin, tmp);
			sendMes(client, tmp);
			recvMes(client);
			cout << "Nhap diem: ";
			fflush(stdin);
			getline(cin, tmp);
			sendMes(client, tmp);
			while(1){
				s = recvMes(client);
				if( s.compare("done") == 0)
					break;
				if( s.compare("khong") == 0){
					sendMes(client, "ok");
					continue;
				}
				ds.recvSV(ds.getSosv(), s);
				ds.setSosv(ds.getSosv() + 1);
				sendMes(client, "ok");
			}
			ds.xuatDs();
			break;
		case 6:
			sendMes(client, "6");
			while(1){
				s = recvMes(client);
				if( s.compare("done") == 0)
					break;
				ds.recvSV(ds.getSosv(), s);
				ds.setSosv(ds.getSosv() + 1);
				sendMes(client, "ok");
			}
			ds.xuatDs();
			break;
		case 7:
			sendMes(client, "7");
			while(1){
				s = recvMes(client);
				if( s.compare("done") == 0)
					break;
				ds.recvSV(ds.getSosv(), s);
				ds.setSosv(ds.getSosv() + 1);
				sendMes(client, "ok");
			}
			ds.xuatDs();
			break;
		case 8:
			sendMes(client, "8");
			while(1){
				s = recvMes(client);
				if( s.compare("done") == 0)
					break;
				ds.recvSV(ds.getSosv(), s);
				ds.setSosv(ds.getSosv() + 1);
				sendMes(client, "ok");
			}
			ds.xuatDs();
			break;
		case 9:
			sendMes(client, "9");
			recvMes(client);
			cout << "Chon chuc nang:\n1.Cap nhat thong tin sinh vien\n2.Xoa thong tin sinh vien\n";
			cin >> i;
			if(i == 1){
				sendMes(client, "sua");
				recvMes(client);
				cout << "Chon sinh vien theo: 1.Ten\t2.So bao danh\n";
				cin >> i;
				if(i == 1){
					cout << "Nhap ten: ";
					fflush(stdin);
					getline(cin, tmp);
					sendMes(client, "ten");
				}
				if(i == 2){
					cout << "Nhap so bao danh ";
					fflush(stdin);
					getline(cin, tmp);
					sendMes(client, "sbd");
				}
				recvMes(client);
				sendMes(client, tmp);
				s = recvMes(client);
				if (s.compare("khong") == 0)
					cout << "Khong ton tai sinh vien\n";
				else{
					ds.ds[0] = ds.nhapThongTin(); 
					sendMes(client, ds.sendSV(0));
					recvMes(client);
				}
			}else if(i == 2){
				sendMes(client,"xoa");
				recvMes(client);
				cout << "Xoa theo: 1.Ten\t2.So bao danh\n";
				cin >> i;
				if( i == 1){
					cout << "Nhap ten: ";
					fflush(stdin);
					getline(cin, tmp);
					sendMes(client, "ten");
				}
				if(i == 2){
					cout << "Nhap so bao danh: ";
					fflush(stdin);
					getline(cin, tmp);
					sendMes(client, "sbd");
				}
				recvMes(client);
				sendMes(client, tmp);
				cout << recvMes(client);
			}
			break;
		case 10:
			sendMes(client, "10");
			recvMes(client);
			cout << "Nhap so sinh vien can them: ";
			cin >> n;
			for ( i = 0; i < n; i++){
				cout << "***********\n";
				ds.ds[i] = ds.nhapThongTin();
				sendMes(client, ds.sendSV(i));
				recvMes(client);
			}
			sendMes(client, "done");
			recvMes(client);
			break;
		case 11:
			sendMes(client, "11");
			recvMes(client);
			cout << "Nhap yeu cau thong ke:\n1. Sinh vien co diem nho hon 15\n2. Sinh vien co diem tu 15 den 20\n3. Sinh vien co diem tu 20 den 25\n4. Sinh vien co diem lon hon 25\n";
			cin >> i;
			if(i == 1)	sendMes(client,"< 15");
			if(i == 2)	sendMes(client,">= 15 && < 20");
			if(i == 3)	sendMes(client,">= 20 && < 25");
			if(i == 4)	sendMes(client,"> 25");
			while(1){
				s = recvMes(client);
				if( s.compare("done") == 0)
					break;
				if( s.compare("khong") == 0){
					sendMes(client, "ok");
					continue;
				}
				ds.recvSV(ds.getSosv(), s);
				ds.setSosv(ds.getSosv() + 1);
				sendMes(client, "ok");
			}
			ds.xuatDs();
			break;
		case 12:
			sendMes(client, "11");
			recvMes(client);
			closesocket(client);
			return;
		default: 
			continue;
		}
		do{
			cout << "Quay tro lai menu(y/n): ";
			fflush(stdin);
			c = getchar();
		}while(c != 'y');
	}

}

string UI::recvMes (SOCKET client)
{
	char buff[BUFF_SIZE];
	int ret;
	
	//Receive echo message
	ret = recv(client, buff, BUFF_SIZE, 0);
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

void UI::sendMes (SOCKET client, string buff)
{	
	int ret;

	ret = send(client, buff.c_str(), strlen(buff.c_str()), 0);
	if(ret  == SOCKET_ERROR)
		cout << "Error! Cannot send mesage." << endl;
	
}