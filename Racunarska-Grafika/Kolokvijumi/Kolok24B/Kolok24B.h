
// Kolok24B.h : main header file for the Kolok24B application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CKolok24BApp:
// See Kolok24B.cpp for the implementation of this class
//

class CKolok24BApp : public CWinApp
{
public:
	CKolok24BApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CKolok24BApp theApp;
