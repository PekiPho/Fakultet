
// lab6View.cpp : implementation of the Clab6View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "lab6.h"
#endif

#include "lab6Doc.h"
#include "lab6View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Clab6View

IMPLEMENT_DYNCREATE(Clab6View, CView)

BEGIN_MESSAGE_MAP(Clab6View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// Clab6View construction/destruction

Clab6View::Clab6View() noexcept
{
	// TODO: add construction code here

}

Clab6View::~Clab6View()
{
}

BOOL Clab6View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Clab6View drawing

void Clab6View::OnDraw(CDC* pDC)
{
	Clab6Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_glRenderer.DrawScene(pDC);

	// TODO: add draw code for native data here
}


// Clab6View printing

BOOL Clab6View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Clab6View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Clab6View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// Clab6View diagnostics

#ifdef _DEBUG
void Clab6View::AssertValid() const
{
	CView::AssertValid();
}

void Clab6View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Clab6Doc* Clab6View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Clab6Doc)));
	return (Clab6Doc*)m_pDocument;
}
#endif //_DEBUG


// Clab6View message handlers



void Clab6View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CDC* pDC = GetDC();
	m_glRenderer.Reshape(pDC, cx, cy);
	ReleaseDC(pDC);
}

BOOL Clab6View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;
}

void Clab6View::OnLButtonDown(UINT nFlags, CPoint point)
{
	btnDown.x = point.x;
	btnDown.y = point.y;

	rotationActive = true;

	CView::OnLButtonDown(nFlags, point);
}

void Clab6View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	rotationActive = false;
	CView::OnLButtonUp(nFlags, point);
}

void Clab6View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (rotationActive) {
		int diffx = point.x - btnDown.x;
		int diffy = point.y - btnDown.y;

		double sensitivity = 1 / 4.0;

		m_glRenderer.RotateCamera(diffy * sensitivity, diffx * sensitivity);
		Invalidate();

	}
	btnDown.x = point.x;
	btnDown.y = point.y;

	CView::OnMouseMove(nFlags, point);
}

int Clab6View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CDC* pDC = GetDC();
	m_glRenderer.CreateGLContext(pDC);
	ReleaseDC(pDC);

	return 0;
}

void Clab6View::OnDestroy()
{
	CView::OnDestroy();

	CDC* pDC = GetDC();
	m_glRenderer.DestroyScene(pDC);
	ReleaseDC(pDC);
}

void Clab6View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CDC* pDC = GetDC();
	m_glRenderer.PrepareScene(pDC);
	ReleaseDC(pDC);
}