
// GL Kol 2016.h : main header file for the GL Kol 2016 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGLKol2016App:
// See GL Kol 2016.cpp for the implementation of this class
//

class CGLKol2016App : public CWinApp
{
public:
	CGLKol2016App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGLKol2016App theApp;
