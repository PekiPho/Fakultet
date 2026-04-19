
// GL Kol 2016View.h : interface of the CGLKol2016View class
//

#pragma once

#include "CGLRenderer.h"

class CGLKol2016View : public CView
{
protected: // create from serialization only
	CGLKol2016View() noexcept;
	DECLARE_DYNCREATE(CGLKol2016View)

// Attributes
public:
	CGLKol2016Doc* GetDocument() const;

protected:
	CGLRenderer m_glRenderer;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CGLKol2016View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // debug version in GL Kol 2016View.cpp
inline CGLKol2016Doc* CGLKol2016View::GetDocument() const
   { return reinterpret_cast<CGLKol2016Doc*>(m_pDocument); }
#endif

