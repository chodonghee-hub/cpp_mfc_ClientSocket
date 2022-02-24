﻿
// Study_mfc_0221_ClientDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Study_mfc_0221_Client.h"
#include "Study_mfc_0221_ClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CStudymfc0221ClientDlg 대화 상자



CStudymfc0221ClientDlg::CStudymfc0221ClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STUDY_MFC_0221_CLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStudymfc0221ClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_IP_info, m_IpInfo);
	DDX_Control(pDX, IDC_EDIT_PORT_info, m_PortInfo);
	DDX_Control(pDX, IDC_EDIT_LOG, m_LogMessage);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_InputMessage);
	DDX_Control(pDX, IDC_BUTTON_SET_DEFAULT, m_SetDefault);
	//  DDX_Control(pDX, IDC_BUTTON_CONNECT, m_btnConnection);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_BtnConnection);
}

BEGIN_MESSAGE_MAP(CStudymfc0221ClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CStudymfc0221ClientDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CStudymfc0221ClientDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_SET_DEFAULT, &CStudymfc0221ClientDlg::OnBnClickedButtonSetDefault)
	ON_EN_CHANGE(IDC_EDIT_LOG, &CStudymfc0221ClientDlg::OnEnChangeEditLog)
END_MESSAGE_MAP()


// CStudymfc0221ClientDlg 메시지 처리기

BOOL CStudymfc0221ClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	b_mfcConnectionFlag = false;
	clnt = new cClientSocket(this);

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CStudymfc0221ClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CStudymfc0221ClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CStudymfc0221ClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CStudymfc0221ClientDlg::OnBnClickedButtonConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// cClientSocket -> __Init__()
	if (b_mfcConnectionFlag == false) {
		if (clnt->bCheckWindowSock())
		{
			AfxMessageBox(_T("WSAStartup"));
		}


		clnt->_SetSocketInfo();
		if (clnt->bCheckValidSocket())
		{
			AfxMessageBox(_T("ValidSocket"));
		}
		CString _IpInfo;
		CString _PortInfo;
		CString _tmp;
		m_IpInfo.GetWindowTextW(_IpInfo);


		m_PortInfo.GetWindowTextW(_PortInfo);



		if (clnt->bCheckConnection(_IpInfo, _PortInfo))
		{
			b_mfcConnectionFlag = true;
			AfxMessageBox(_T("Connect Success"));
			_tmp.Format(_T("▶ connection	: O \r\n▶ recvThread	: O"));
			m_LogMessage.SetWindowTextW(_tmp);
			m_BtnConnection.SetWindowTextW(_T("Break"));
			//readBufferThread = thread(_ReadBuffer, this);
		}
	}
	else
	{
		m_BtnConnection.SetWindowTextW(_T("Connect"));	
		b_mfcConnectionFlag = false;
		// break function
	}
	
}


void CStudymfc0221ClientDlg::OnBnClickedButtonSend()
{
	CString _MessageBuffer;
	m_InputMessage.GetWindowTextW(_MessageBuffer);
	m_LogMessage.SetWindowTextW(_MessageBuffer);
	clnt->_SendMessageTo(_MessageBuffer);
	m_InputMessage.SetWindowTextW(_T(""));
}


void CStudymfc0221ClientDlg::OnBnClickedButtonSetDefault()
{
	m_IpInfo.SetWindowTextW(_T("127.0.0.1"));
	m_PortInfo.SetWindowTextW(_T("8080"));
}


void CStudymfc0221ClientDlg::OnEnChangeEditLog()
{
}

void CStudymfc0221ClientDlg::_ReadBuffer(LPVOID lp)
{
	CStudymfc0221ClientDlg* p = (CStudymfc0221ClientDlg*)lp;
	// check init thread
	CString tmp; 
	
	while (p->b_mfcConnectionFlag)
	{
		tmp.Format(_T("** now read buffer ..."));
		p->m_LogMessage.SetWindowTextW(tmp);
		Sleep(1000);

		string _rs = p->clnt->cGetBuffer();
		const char* rs = _rs.c_str();
		if (strcmp(rs, "none") != 0)
		{
			p->m_LogMessage.SetWindowTextW((CString) rs);
			p->clnt->vec_Buffer.pop_back();
			Sleep(5000);
		}

		Sleep(1000);
	}
}

void CStudymfc0221ClientDlg::_CallSetMessage()
{
	CString tmp;
	tmp.Format(_T("** now read buffer ..."));
	m_LogMessage.SetWindowTextW(tmp);
	Sleep(1000);

	string _rs = clnt->cGetBuffer();
	const char* rs = _rs.c_str();
	if (strcmp(rs, "none") != 0)
	{
		m_LogMessage.SetWindowTextW((CString)rs);
		clnt->vec_Buffer.pop_back();
		Sleep(5000);
	}
}


