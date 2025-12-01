
// Priprema za labView.h : interface of the CPripremazalabView class
//

#pragma once


class CPripremazalabView : public CView
{
private:
	bool showGrid = true;
protected: // create from serialization only
	CPripremazalabView() noexcept;
	DECLARE_DYNCREATE(CPripremazalabView)

// Attributes
public:
	CPripremazalabDoc* GetDocument() const;

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
	virtual ~CPripremazalabView();
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

#ifndef _DEBUG  // debug version in Priprema za labView.cpp
inline CPripremazalabDoc* CPripremazalabView::GetDocument() const
   { return reinterpret_cast<CPripremazalabDoc*>(m_pDocument); }
#endif

