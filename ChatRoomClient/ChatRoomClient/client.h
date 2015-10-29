// client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <WinSock2.h>

 #pragma comment(lib,"ws2_32.lib")
#include <vector>
using namespace std;

class Client
{
public :
	SOCKET server;
	char addr[100], dAddr;
	int port;
	sockaddr_in address;
	vector <string> con;
	void init(char * addr, int port)
	{
		strcpy_s(this->addr, addr);
		this->port = port;
		WSADATA wsa;
		WSAStartup(MAKEWORD(1, 1), &wsa);
		server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = inet_addr(this->addr);
		address.sin_port = port;
	}
	int run()
	{
		int flag = connect(server, (sockaddr*)&address, sizeof(sockaddr));
		if(flag != 0)
		{
			MessageBox( NULL , TEXT("连接失败") , TEXT("") , MB_ICONINFORMATION|MB_YESNO);
			return 0;
		}
		return 1;
	}
	int sendData(const char * buf, int lenth)
	{
		send(server, buf, lenth,  0);
		return 0;
	}
};

