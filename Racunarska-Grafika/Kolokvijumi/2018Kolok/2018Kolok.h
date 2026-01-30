
// 2018Kolok.h : main header file for the 2018Kolok application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy2018KolokApp:
// See 2018Kolok.cpp for the implementation of this class
//

class CMy2018KolokApp : public CWinApp
{
public:
	CMy2018KolokApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy2018KolokApp theApp;
