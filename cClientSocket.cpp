#include "pch.h"
#include "cClientSocket.h"
#include "Study_mfc_0221_ClientDlg.h"

cClientSocket::cClientSocket(LPVOID _pMfc)
{
	pMfc = _pMfc;
	cBuffer = new char;
	ZeroMemory(cBuffer, strlen(cBuffer));
	bConnectionFlag = false;
}

cClientSocket::cClientSocket()
{
	cBuffer = new char;
}

cClientSocket::~cClientSocket(){ }

void cClientSocket::__init__()
{

	ZeroMemory(cBuffer, strlen(cBuffer));
}

void cClientSocket::_SetSocketInfo()
{
	clnt = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void cClientSocket::_SendMessageTo(CString _message)
{
	// length + 1 (null index size : 1) 
	int length = _message.GetLength() + 1;
	string str = CT2CA(_message);
	send(clnt, str.c_str(), length, 0);
}

void cClientSocket::_BreakConnection()
{
	while (bRecvThreadFlag)
	{
		Sleep(10);
	}
	//delete[] cBuffer;
	//cBuffer = nullptr;
	closesocket(clnt);
	WSACleanup();
	delete this;
}

void cClientSocket::_RecvDataFrom(LPVOID lp)
{
	cClientSocket* p = nullptr;
	p = (cClientSocket*)lp;
	p->bRecvThreadFlag = p->bConnectionFlag;
	CStudymfc0221ClientDlg* pDlg = (CStudymfc0221ClientDlg*)p->pMfc;

	int recv_result;
	while (p->bRecvThreadFlag) 
	{
		while (p->bConnectionFlag)
		{
			try
			{

				recv(p->clnt, p->cBuffer, 1024, 0);
				if (strncmp(p->cBuffer, "exit", strlen(p->cBuffer)) == 0)
				{
					p->bConnectionFlag = false;
				}
				else
				{
					p->vec_Buffer.push_back(p->cBuffer);
					pDlg->_CallSetMessage();
				}
			}

			catch (int e)
			{
				cout << "** Termiante connection from Server ..." << endl;
				p->bConnectionFlag = false;
			}
			ZeroMemory(p->cBuffer, strlen(p->cBuffer) + 1);
			Sleep(1);
		}
		p->bRecvThreadFlag = false;
	}
}

string cClientSocket::cGetBuffer()
{
	if (!vec_Buffer.empty())
	{
		return vec_Buffer.at(0);
	}
	return "none";
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
	bConnectionFlag = true;
	ZeroMemory(cBuffer, strlen(cBuffer));

	mtxPoint.lock();		// set mutex
	const char* _nIpNum = (char*)(LPCTSTR)_IpNum;
	int _nPortNum = _ttoi(_PortNum);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(_nPortNum);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (connect(clnt, (SOCKADDR*)&addr, sizeof(addr)) != 0)
	{
		WSACleanup();
		mtxPoint.unlock();	// remove mutex
		return false;
	}


	while (!bConnectionFlag) { Sleep(1); }
  	recvThread = thread(_RecvDataFrom, this);
	recvThread.detach();
	mtxPoint.unlock();		// remove mutex
	return true;
}