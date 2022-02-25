#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma once
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <thread>
#include <string>
#include <mutex>
#include <vector>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

class cClientSocket
{
private : 
	WSADATA			wsaData;
	SOCKET			clnt;
	SOCKADDR_IN		addr;
	thread			recvThread;
	mutex			mtxPoint;
	LPVOID			pMfc;
	char*			cBuffer;
	
public :	
	bool			bConnectionFlag;
	bool			bRecvThreadFlag;
	vector<char*>	vec_Buffer;
	cClientSocket(LPVOID _pMfc);
	cClientSocket();
	~cClientSocket();

	void __init__();
	void _SetSocketInfo();
	void _SendMessageTo(CString _message);
	void _BreakConnection();
	static void _RecvDataFrom(LPVOID lp);
	string cGetBuffer();
	bool bCheckWindowSock();
	bool bCheckValidSocket();
	bool bCheckConnection(CString _IpNum, CString _PortNum);
};

