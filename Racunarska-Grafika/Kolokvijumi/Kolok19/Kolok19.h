
// Kolok19.h : main header file for the Kolok19 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CKolok19App:
// See Kolok19.cpp for the implementation of this class
//

class CKolok19App : public CWinApp
{
public:
	CKolok19App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CKolok19App theApp;
