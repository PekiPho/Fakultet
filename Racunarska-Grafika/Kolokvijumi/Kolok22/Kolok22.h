
// Kolok22.h : main header file for the Kolok22 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CKolok22App:
// See Kolok22.cpp for the implementation of this class
//

class CKolok22App : public CWinApp
{
public:
	CKolok22App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CKolok22App theApp;
