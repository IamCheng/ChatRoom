#pragma once
#include "stdafx.h"
#include <WinSock2.h>
#include <iostream>
#include <vector>
using namespace std;
#pragma comment(lib,"ws2_32.lib")
class Service;
class Server
{
public:
	char addr[100];
	int port;
	vector <string> mChatContent;
	SOCKET serverSocket;
	vector <SOCKET > clients;
	void init(char * addr, int port);
	int run();
	vector <Service *> mlist_Service;

};