
// Priprema za labView.cpp : implementation of the CPripremazalabView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Priprema za lab.h"
#endif

#include "Priprema za labDoc.h"
#include "Priprema za labView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPripremazalabView

IMPLEMENT_DYNCREATE(CPripremazalabView, CView)

BEGIN_MESSAGE_MAP(CPripremazalabView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CPripremazalabView construction/destruction

CPripremazalabView::CPripremazalabView() noexcept
{
	// TODO: add construction code here

}

CPripremazalabView::~CPripremazalabView()
{
}

BOOL CPripremazalabView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPripremazalabView drawing

void CPripremazalabView::OnDraw(CDC* pDC)
{
	CPripremazalabDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CBrush redBrush(RGB(255, 0, 0));
	CBrush pinkBrush(RGB(255, 140, 161));
	CBrush purpleBrush(RGB(170, 40, 170));
	CBrush yellowBrush(RGB(255,255,0));
	CBrush greenBrush(RGB(0, 250, 0));
	CBrush whiteBrush(RGB(255, 255, 255));
	CBrush blueBrush(RGB(0, 0, 255));

	CPen bluePen(PS_SOLID, 1, RGB(0,0, 255));

	//narandzast
	CBrush fillBrush(RGB(255, 165, 0));
	CBrush* oldBrush = pDC->SelectObject(&fillBrush);

	CPen borderPen(PS_SOLID, 4, RGB(0, 180, 0));
	CPen* oldPen = pDC->SelectObject(&borderPen);

	POINT pts[3] = {
		{25,25},
		{25,450},
		{240,240}
	};

	pDC->Polygon(pts, 3);

	//pink
	
	pDC->SelectObject(&pinkBrush);
	pDC->Rectangle(325,25,475,175);


	//purpl
	pDC->SelectObject(&purpleBrush);


	pts[0] = {325, 175};
	pts[1] = { 475,175 };
	pts[2] = {475, 325};
	
	pDC->Polygon(pts, 3);

	//yelou
	POINT skewed[4] = {
		{325,175},
		{475,325},
		{475,475},
		{325,325}
	};

	pDC->SelectObject(&yellowBrush);
	pDC->Polygon(skewed, 4);

	//green
	pDC->SelectObject(&greenBrush);

	pts[0] = { 475,475 };
	pts[1] = { 50,475 };
	pts[2] = { 265,265 };

	pDC->Polygon(pts, 3);

	//beli
	pDC->SelectObject(&whiteBrush);

	pts[0] = { 325,25 };
	pts[1] = { 325,175 };
	pts[2] = { 175,175 };

	pDC->Polygon(pts, 3);

	pDC->SelectObject(&bluePen);
	for (float y = 25; y < 175; y += 8.3) {
		pDC->MoveTo(175, y);
		pDC->LineTo(325, y);
	}

	//crveni
	pDC->SelectObject(&borderPen);
	pDC->SelectObject(&redBrush);

	pts[1] = { 325,25 };
	pts[2] = { 175,175 };
	pts[0] = { 25,25 };

	pDC->Polygon(pts, 3);


	pDC->SelectStockObject(NULL_BRUSH);
	pDC->SelectObject(&borderPen);

	DrawRegularPolygon(pDC, 175, 90, 35, 8, 0.0f);
	DrawRegularPolygon(pDC, 280, 140, 15, 4, 0.0f);
	DrawRegularPolygon(pDC, 440, 220, 17, 6, 0.0f);
	DrawRegularPolygon(pDC, 110, 235, 40, 5, 0.0f);
	DrawRegularPolygon(pDC, 250, 385, 50, 7, 0.0f);



	//grid
	if (showGrid) {
		CPen gridPen(PS_SOLID, 1, RGB(255, 255, 255));
		pDC->SelectObject(&gridPen);

		CRect rr;
		GetClientRect(&rr);

		for (int x = 0; x < rr.Width(); x += 25) {
			pDC->MoveTo(x, 0);
			pDC->LineTo(x, rr.Height());
		}

		for (int y = 0; y < rr.Width(); y += 25) {
			pDC->MoveTo(0,y);
			pDC->LineTo(rr.Width(),y);
		}

	}

	


	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
}


void CPripremazalabView::DrawRegularPolygon(CDC* pDC, int cx, int cy, int r, int n, float rotAngle) {

	float rot = rotAngle * 3.14159 / 180.0f;

	CPoint* p = new CPoint[n];

	for (int i = 0; i < n; i++) {

		float a = rot + 2.0f * 3.14159 * i / n;

		float x = cx + r * cos(a);
		float y = cy + r * sin(a);

		p[i] = CPoint((int)x, (int)y);

	}


	pDC->Polygon(p, n);
	delete[] p;
}


// CPripremazalabView printing

BOOL CPripremazalabView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPripremazalabView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPripremazalabView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CPripremazalabView diagnostics

#ifdef _DEBUG
void CPripremazalabView::AssertValid() const
{
	CView::AssertValid();
}

void CPripremazalabView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPripremazalabDoc* CPripremazalabView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPripremazalabDoc)));
	return (CPripremazalabDoc*)m_pDocument;
}
#endif //_DEBUG


// CPripremazalabView message handlers


void CPripremazalabView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 'g' || nChar == 'G') {
		showGrid = !showGrid;
		Invalidate();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CPripremazalabView::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	CBrush brush(RGB(200, 200, 200));
	pDC->FillRect(&rect, &brush);

	return TRUE;
}
