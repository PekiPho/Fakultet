
// MonapuzzleView.h : interface of the CMonapuzzleView class
//

#pragma once


class CMonapuzzleView : public CView
{
protected: // create from serialization only
	CMonapuzzleView() noexcept;
	DECLARE_DYNCREATE(CMonapuzzleView)

// Attributes
public:
	CMonapuzzleDoc* GetDocument() const;

	int tranX[9];
	int tranY[9];
	int rot[9];
	bool mirX[9];
	bool mirY[9];


// Operations
public:

// Overrides
public:

	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply = true);
	void Scale(CDC* pDC, float sX, float sY, bool rightMultiply = true);
	void Rotate(CDC* pDC, float angle, bool rightMultiply = true);
	void Mirror(CDC* pDC, bool mx, bool my, bool rightMultiply = true);


	void Postavi(CDC* pDC, CString imeSlike, int x, int y, int angle = 0, bool mirrorX = false, bool mirrorY = false, bool samoPlava = false);
	void Filtriraj(CBitmap* bmpImage, bool boja);
	void Cela(CDC* pDC);


	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMonapuzzleView();
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
};

#ifndef _DEBUG  // debug version in MonapuzzleView.cpp
inline CMonapuzzleDoc* CMonapuzzleView::GetDocument() const
   { return reinterpret_cast<CMonapuzzleDoc*>(m_pDocument); }
#endif

