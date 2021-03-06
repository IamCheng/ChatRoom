// Server.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "Server.h"
#include "ServiceThread.h"

class Service: public CServiceThread
{
	friend CServiceThread;
public:
	SOCKET  client;
	char buf[1000];
	Server * server;
	void init(SOCKET  s, Server *server)
	{
		client = s;
		this->server = server;
	}
	virtual bool RepetitionRun()
	{
		int len = 50;
		int res = recv(client, buf, len, 0);
		if( res == -1)
		{
			vector<SOCKET>::iterator it;
			for(it = server->clients.begin(); it != server->clients.end(); it++)
			{
				if(*it == client)
				{
					closesocket(client);
					server->clients.erase(it);
					break;
				}
			}			
			return false;//退出
		}
		server->mChatContent.push_back(buf);
		broadCast();
		return true;
	}
	int broadCast()
	{
		int index = server->mChatContent.size();
		for(int i = 0; i < server->clients.size(); i++)
		{
			SOCKET client = server->clients[i];
			const char * tmp = server->mChatContent[index-1].c_str();
			send(client, tmp, strlen(tmp)+1,  0);
		}
		return 1;
	}
};



void Server::init(char * addr, int port)
{
	strcpy(this->addr, addr);
	this->port = port;
	WSADATA wsadata;
	if(WSAStartup(MAKEWORD(1, 1), &wsadata)  !=  0)
		return ;	
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(this->addr);
	address.sin_port = this->port;	
	if(bind(serverSocket, (sockaddr*)&address, sizeof(sockaddr)) != 0)
	{
		int result = MessageBox( NULL , TEXT("绑定失败") , TEXT("") , MB_ICONINFORMATION|MB_YESNO);
		return ;
	};

	listen(serverSocket, 50);	
}
int Server::run()
{
	while(1)
	{	
		sockaddr_in clientAdress;
		int len = sizeof(clientAdress);
		SOCKET client = accept(serverSocket, (sockaddr *)&clientAdress, &len);
		if(client == INVALID_SOCKET)
		{
			continue;
			break;
		}
		clients.push_back(client);
		Service * tmp = new Service();
	//	mlist_Service.push_back(tmp);
		tmp->init(client, this);
		tmp->StartThead();
	}
}
