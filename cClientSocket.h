#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma once
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma commeqnt(lib, "ws2_32.lib")

using namespace std;

class cClientSocket
{
private : 
	WSADATA		wsaData;
	SOCKET		clnt;
	SOCKADDR_IN	addr;
	bool		bConnectionFlag;

public :
	cClientSocket();
	~cClientSocket();

	void __init__();
	void _SetSocketInfo();
	void _SendMessageTo(CString _message);
	bool bCheckWindowSock();
	bool bCheckValidSocket();
	bool bCheckConnection(CString _IpNum, CString _PortNum);
};

