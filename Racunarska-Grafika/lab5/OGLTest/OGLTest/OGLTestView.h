
// OGLTestView.h : interface of the COGLTestView class
//

#pragma once
#include "CRenderer.h"
#include "CRenderer.h"

class COGLTestView : public CView
{
protected: // create from serialization only
	COGLTestView() noexcept;
	DECLARE_DYNCREATE(COGLTestView)

// Attributes
public:
	COGLTestDoc* GetDocument() const;

// Operations
public:
	CRenderer m_glRenderer;
	CPoint btnDown{};
	bool rotationActive = false;
	virtual void OnInitialUpdate();

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
	virtual ~COGLTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in OGLTestView.cpp
inline COGLTestDoc* COGLTestView::GetDocument() const
   { return reinterpret_cast<COGLTestDoc*>(m_pDocument); }
#endif

