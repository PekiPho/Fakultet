
// Kolok19View.h : interface of the CKolok19View class
//

#pragma once
#include "DImage.h"

class CKolok19View : public CView
{
protected: // create from serialization only
	CKolok19View() noexcept;
	DECLARE_DYNCREATE(CKolok19View)

// Attributes
public:
	CKolok19Doc* GetDocument() const;

// Operations
public:
	float a1ang = 0.0f, a2ang = 0.0f, l1ang = 0.0f, l2ang = 0.0f, bang = 0.0f, kretanje = 0.0f;

	DImage* body;
	DImage* arm1, * arm2;
	DImage* leg1, * leg2;
	DImage* pozadina;

	void DrawBackground(CDC* pDC, CRect rc);
	void DrawImgTransparent(CDC* pDC, DImage* pImage);
	void Translate(CDC* pDC, float dx, float dy, bool rightMultiply);
	void Scale(CDC* pDC, float sx, float sy, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void DrawArm1(CDC* pDC);
	void DrawArm2(CDC* pDC);
	void DrawLeg1(CDC* pDC);
	void DrawLeg2(CDC* pDC);
	void DrawBody(CDC* pDC);
	void DrawTransformer(CDC* pDC);
	

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
	virtual ~CKolok19View();
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

#ifndef _DEBUG  // debug version in Kolok19View.cpp
inline CKolok19Doc* CKolok19View::GetDocument() const
   { return reinterpret_cast<CKolok19Doc*>(m_pDocument); }
#endif

