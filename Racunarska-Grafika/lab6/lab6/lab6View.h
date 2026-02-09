
// lab6View.h : interface of the Clab6View class
//

#pragma once
#include "CRenderer.h"


class Clab6View : public CView
{
protected: // create from serialization only
	Clab6View() noexcept;
	DECLARE_DYNCREATE(Clab6View)

// Attributes
public:
	Clab6Doc* GetDocument() const;

	CRenderer m_glRenderer;
	bool is_clicked;
	CPoint old_point;

	CPoint btnDown{};
	bool rotationActive = false;

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
	virtual ~Clab6View();
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
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // debug version in lab6View.cpp
inline Clab6Doc* Clab6View::GetDocument() const
   { return reinterpret_cast<Clab6Doc*>(m_pDocument); }
#endif

