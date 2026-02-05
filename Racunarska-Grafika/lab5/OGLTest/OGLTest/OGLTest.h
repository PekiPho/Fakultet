
// OGLTest.h : main header file for the OGLTest application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// COGLTestApp:
// See OGLTest.cpp for the implementation of this class
//

class COGLTestApp : public CWinApp
{
public:
	COGLTestApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COGLTestApp theApp;
