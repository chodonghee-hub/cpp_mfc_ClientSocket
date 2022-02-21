#include "pch.h"
#include "cClientSocket.h"

cClientSocket::cClientSocket()
{
}

cClientSocket::~cClientSocket()
{
}

void cClientSocket::__init__()
{
}

void cClientSocket::_SetSocketInfo()
{
	clnt = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void cClientSocket::_SendMessageTo(CString _message)
{
	//const char* cBuffer;
	//cBuffer = (char*)(LPCTSTR)_message;
	
	//send(clnt, cBuffer, strlen(cBuffer), 0);
	int length = _message.GetLength();
	//char* st = LPSTR(LPCTSTR(_message));
	string str = CT2CA(_message);
	send(clnt, str.c_str(), length, 0);
}

bool cClientSocket::bCheckWindowSock()
{
	if (WSAStartup(WINSOCK_VERSION, &wsaData) != 0)
	{
		WSACleanup();
		return false;
	}
	return true;
}

bool cClientSocket::bCheckValidSocket()
{
	if (clnt == INVALID_SOCKET)
	{
		WSACleanup();
		return false;
	}
	return true;
}

bool cClientSocket::bCheckConnection(CString _IpNum, CString _PortNum)
{
	const char* _nIpNum = (char*)(LPCTSTR)_IpNum;
	int _nPortNum = _ttoi(_PortNum);
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(_nPortNum);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (connect(clnt, (SOCKADDR*)&addr, sizeof(addr)) != 0)
	{
		WSACleanup();
		return false;
	}
	bConnectionFlag = true;
	return true;
}
