
// GL Kol 2 2023View.h : interface of the CGLKol22023View class
//

#pragma once
#include "CGLRenderer.h"


class CGLKol22023View : public CView
{
protected: // create from serialization only
	CGLKol22023View() noexcept;
	DECLARE_DYNCREATE(CGLKol22023View)

// Attributes
public:
	CGLKol22023Doc* GetDocument() const;

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
	virtual ~CGLKol22023View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CGLRenderer m_glRenderer;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	virtual void OnInitialUpdate();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in GL Kol 2 2023View.cpp
inline CGLKol22023Doc* CGLKol22023View::GetDocument() const
   { return reinterpret_cast<CGLKol22023Doc*>(m_pDocument); }
#endif

