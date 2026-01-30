
// Kolok22View.h : interface of the CKolok22View class
//

#pragma once
#include "DImage.h"

class CKolok22View : public CView
{
protected: // create from serialization only
	CKolok22View() noexcept;
	DECLARE_DYNCREATE(CKolok22View)

// Attributes
public:
	CKolok22Doc* GetDocument() const;

// Operations
public:
	float ang1 = -90.0f, ang2 = 0.0f, hAng=150.0f;
	DImage* base;
	DImage* arm1, * arm2;
	DImage* head;
	DImage* pozadina;
	DImage* bShadow, * a1Shadow, *a2Shadow, *hShadow;

	void Translate(CDC* pDC, float dx, float dy, bool rightMultiply);
	void Scale(CDC* pDC, float sx, float sy, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);

	void DrawBackground(CDC* pDC);
	void DrawImgTransparent(CDC* pDC, DImage* pImage);

	void DrawLampBase(CDC* pDC, bool bIsShadow);
	void DrawLampArm1(CDC* pDC, bool bIsShadow);
	void DrawLampArm2(CDC* pDC, bool bIsShadow);
	void DrawLampHead(CDC* pDC, bool bIsShadow);
	void DrawLamp(CDC* pDC, bool bIsShadow);
	void DrawLampShadow(CDC* pDC);


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
	virtual ~CKolok22View();
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

#ifndef _DEBUG  // debug version in Kolok22View.cpp
inline CKolok22Doc* CKolok22View::GetDocument() const
   { return reinterpret_cast<CKolok22Doc*>(m_pDocument); }
#endif

