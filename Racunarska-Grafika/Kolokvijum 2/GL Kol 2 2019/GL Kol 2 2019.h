
// GL Kol 2 2019.h : main header file for the GL Kol 2 2019 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGLKol22019App:
// See GL Kol 2 2019.cpp for the implementation of this class
//

class CGLKol22019App : public CWinApp
{
public:
	CGLKol22019App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGLKol22019App theApp;
