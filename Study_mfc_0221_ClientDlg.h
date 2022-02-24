#define _WINSOCK_DEPRECATED_NO_WARNINGS
// Study_mfc_0221_ClientDlg.h: 헤더 파일
//

#pragma once
#include "cClientSocket.h"
#include <thread>
#include <string>
#include <mutex>

// CStudymfc0221ClientDlg 대화 상자
class CStudymfc0221ClientDlg : public CDialogEx
{
private :
	cClientSocket*	clnt;

// 생성입니다.
public:
	CStudymfc0221ClientDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDY_MFC_0221_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON	m_hIcon;
	thread	readBufferThread;
	mutex	mtxPoint;
	bool	b_mfcConnectionFlag;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonConnect();
	CEdit m_IpInfo;
	CEdit m_PortInfo;
	CEdit m_LogMessage;
	CEdit m_InputMessage;
	afx_msg void OnBnClickedButtonSend();
	CButton m_SetDefault;
	afx_msg void OnBnClickedButtonSetDefault();
	afx_msg void OnEnChangeEditLog();
	CButton m_BtnConnection;
	static void _ReadBuffer(LPVOID lp);
	void _CallSetMessage();
};
