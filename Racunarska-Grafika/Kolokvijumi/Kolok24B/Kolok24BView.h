
// Kolok24BView.h : interface of the CKolok24BView class
//

#pragma once
#include "DImage.h"

class CKolok24BView : public CView
{
protected: // create from serialization only
	CKolok24BView() noexcept;
	DECLARE_DYNCREATE(CKolok24BView)

// Attributes
public:
	CKolok24BDoc* GetDocument() const;

// Operations
public:
	float o = 0.0f;
	float a = 0.0f;
	float b = 0.0f;
	float ang = 0.0f;

	DImage* background;
	DImage* basket;
	DImage* arm;

	void DrawBackground(CDC* pDC);
	void DrawImageTransparent(CDC* pDC, DImage* pImage);
	void Translate(CDC* pDC, float dx, float dy, bool rightMultiply);
	void Scale(CDC* pDC, float sx, float sy, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void DrawArm(CDC* pDC);
	void DrawBasket(CDC* pDC, int r);
	void DrawBasketCouple(CDC* pDC, int l, int r, float angle);
	void DrawPlatform(CDC* pDC, int l, int r, double angle);
	void DrawCarousel(CDC* pDC, int h, int r, double offset, double alpha, double beta, double angle);

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
	virtual ~CKolok24BView();
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
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in Kolok24BView.cpp
inline CKolok24BDoc* CKolok24BView::GetDocument() const
   { return reinterpret_cast<CKolok24BDoc*>(m_pDocument); }
#endif

