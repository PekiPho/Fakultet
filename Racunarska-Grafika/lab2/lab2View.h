
// lab2View.h : interface of the Clab2View class
//

#pragma once


class Clab2View : public CView
{
protected: // create from serialization only
	Clab2View() noexcept;
	DECLARE_DYNCREATE(Clab2View)

// Attributes
public:
	Clab2Doc* GetDocument() const;

// Operations
public:
	HENHMETAFILE  m_hCactusLight;
	HENHMETAFILE  m_hCactusDark;
	bool showGrid = false;
	float lightRotation = 0.0f;
	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Scale(CDC* pDC, float sX, float sY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void DrawFigure(CDC* pDC);
	void DrawCactus(CDC* pDC);
	void DrawPart(CDC* pDC, float sx, float sy, float angle, bool light);


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
	virtual ~Clab2View();
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

#ifndef _DEBUG  // debug version in lab2View.cpp
inline Clab2Doc* Clab2View::GetDocument() const
   { return reinterpret_cast<Clab2Doc*>(m_pDocument); }
#endif

