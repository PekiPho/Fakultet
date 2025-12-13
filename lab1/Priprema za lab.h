
// Priprema za lab.h : main header file for the Priprema za lab application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CPripremazalabApp:
// See Priprema za lab.cpp for the implementation of this class
//

class CPripremazalabApp : public CWinApp
{
public:
	CPripremazalabApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPripremazalabApp theApp;
