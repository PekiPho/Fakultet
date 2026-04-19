
// GL Kol 2 2023.h : main header file for the GL Kol 2 2023 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGLKol22023App:
// See GL Kol 2 2023.cpp for the implementation of this class
//

class CGLKol22023App : public CWinApp
{
public:
	CGLKol22023App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGLKol22023App theApp;
