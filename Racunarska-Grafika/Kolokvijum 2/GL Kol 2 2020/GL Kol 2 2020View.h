
// GL Kol 2 2020View.h : interface of the CGLKol22020View class
//

#pragma once
#include "CGLRenderer.h"


class CGLKol22020View : public CView
{
protected: // create from serialization only
	CGLKol22020View() noexcept;
	DECLARE_DYNCREATE(CGLKol22020View)

// Attributes
public:
	CGLKol22020Doc* GetDocument() const;

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
	virtual ~CGLKol22020View();
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
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in GL Kol 2 2020View.cpp
inline CGLKol22020Doc* CGLKol22020View::GetDocument() const
   { return reinterpret_cast<CGLKol22020Doc*>(m_pDocument); }
#endif

