
// 2018KolokView.h : interface of the CMy2018KolokView class
//

#pragma once
#include "C:/Users/peki/source/repos/GrafikaKolok/DImage.h"

class CMy2018KolokView : public CView
{
protected: // create from serialization only
	CMy2018KolokView() noexcept;
	DECLARE_DYNCREATE(CMy2018KolokView)

// Attributes
public:
	CMy2018KolokDoc* GetDocument() const;

// Operations
public:
	int kretanjeBagera = 0;
	float arm1Ang = -90.0f;
	float arm2Ang = -90.0f;
	float forkAng = -90.0f;

	DImage* bager;
	DImage* arm1;
	DImage* arm2;
	DImage* pozadina;

	HENHMETAFILE viljuska;
	ENHMETAHEADER viljuskaHeader;

	void Translate(CDC* pDC, float dx, float dy, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void Scale(CDC* pDC, float sx, float sy, bool rightMultiply);
	void DrawBackground(CDC* pDC);
	void DrawImgTransparent(CDC* pDC, DImage* pImage);
	void DrawBody(CDC* pDC);
	void DrawArm1(CDC* pDC);
	void DrawArm2(CDC* pDC);
	void DrawFork(CDC* pDC);

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
	virtual ~CMy2018KolokView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in 2018KolokView.cpp
inline CMy2018KolokDoc* CMy2018KolokView::GetDocument() const
   { return reinterpret_cast<CMy2018KolokDoc*>(m_pDocument); }
#endif

