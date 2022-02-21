
// Study_mfc_0221_Client.h: PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// 주 기호입니다.

// CStudymfc0221ClientApp:
// 이 클래스의 구현에 대해서는 Study_mfc_0221_Client.cpp을(를) 참조하세요.
//

class CStudymfc0221ClientApp : public CWinApp
{
public:
	CStudymfc0221ClientApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.

	DECLARE_MESSAGE_MAP()
};

extern CStudymfc0221ClientApp theApp;
