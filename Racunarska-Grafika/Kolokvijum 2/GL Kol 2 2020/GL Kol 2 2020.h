
// GL Kol 2 2020.h : main header file for the GL Kol 2 2020 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGLKol22020App:
// See GL Kol 2 2020.cpp for the implementation of this class
//

class CGLKol22020App : public CWinApp
{
public:
	CGLKol22020App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGLKol22020App theApp;
