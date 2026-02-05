
// OGLTestView.cpp : implementation of the COGLTestView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "OGLTest.h"
#endif

#include "OGLTestDoc.h"
#include "OGLTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COGLTestView

IMPLEMENT_DYNCREATE(COGLTestView, CView)

BEGIN_MESSAGE_MAP(COGLTestView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// COGLTestView construction/destruction

COGLTestView::COGLTestView() noexcept
{
	// TODO: add construction code here

}

COGLTestView::~COGLTestView()
{
}

BOOL COGLTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// COGLTestView drawing

void COGLTestView::OnDraw(CDC* pDC)
{
	COGLTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;



	m_glRenderer.DrawScene(pDC);

	// TODO: add draw code for native data here
}


// COGLTestView printing

BOOL COGLTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COGLTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COGLTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// COGLTestView diagnostics

#ifdef _DEBUG
void COGLTestView::AssertValid() const
{
	CView::AssertValid();
}

void COGLTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COGLTestDoc* COGLTestView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COGLTestDoc)));
	return (COGLTestDoc*)m_pDocument;
}
#endif //_DEBUG


// COGLTestView message handlers

BOOL COGLTestView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return true;

}

BOOL COGLTestView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	m_glRenderer.ZoomCamera(zDelta > 0 ? false : true);
	Invalidate();

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void COGLTestView::OnLButtonUp(UINT nFlags, CPoint point)
{
	rotationActive = false;

	CView::OnLButtonUp(nFlags, point);
}

void COGLTestView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CDC* pDC = GetDC();
	m_glRenderer.Reshape(pDC, cx, cy);
	ReleaseDC(pDC);

	// TODO: Add your message handler code here
}

int COGLTestView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;


	CDC* pDC = GetDC();
	m_glRenderer.CreateGLContext(pDC);
	ReleaseDC(pDC);

	return 0;
}

void COGLTestView::OnDestroy()
{
	CView::OnDestroy();

	CDC* pDC = GetDC();
	m_glRenderer.DestroyScene(pDC);
	ReleaseDC(pDC);
}

void COGLTestView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CDC* pDC = GetDC();
	m_glRenderer.PrepareScene(pDC);
	ReleaseDC(pDC);
}

void COGLTestView::OnMouseMove(UINT nFlags, CPoint point)
{
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

void COGLTestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	btnDown.x = point.x;
	btnDown.y = point.y;

	rotationActive = true;

	CView::OnLButtonDown(nFlags, point);
}

void COGLTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case '1':
		m_glRenderer.light1On = !m_glRenderer.light1On;
		break;
	case '2':
		m_glRenderer.light2On = !m_glRenderer.light2On;
		break;
	case '3':
		m_glRenderer.light3On = !m_glRenderer.light3On;
		break;
	case 'N':
		m_glRenderer.normalsOn = !m_glRenderer.normalsOn;
		break;
	case VK_LEFT:
		break;
	case VK_RIGHT:
		break;
	default:
		break;
	}
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
