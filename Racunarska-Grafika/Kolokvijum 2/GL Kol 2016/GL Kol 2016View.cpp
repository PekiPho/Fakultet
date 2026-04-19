
// GL Kol 2016View.cpp : implementation of the CGLKol2016View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "GL Kol 2016.h"
#endif

#include "GL Kol 2016Doc.h"
#include "GL Kol 2016View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGLKol2016View

IMPLEMENT_DYNCREATE(CGLKol2016View, CView)

BEGIN_MESSAGE_MAP(CGLKol2016View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CGLKol2016View construction/destruction

CGLKol2016View::CGLKol2016View() noexcept
{
	// TODO: add construction code here

}

CGLKol2016View::~CGLKol2016View()
{
}

BOOL CGLKol2016View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGLKol2016View drawing

void CGLKol2016View::OnDraw(CDC* pDC)
{
	CGLKol2016Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_glRenderer.DrawScene(pDC);

}


// CGLKol2016View printing

BOOL CGLKol2016View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGLKol2016View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGLKol2016View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CGLKol2016View diagnostics

#ifdef _DEBUG
void CGLKol2016View::AssertValid() const
{
	CView::AssertValid();
}

void CGLKol2016View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGLKol2016Doc* CGLKol2016View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGLKol2016Doc)));
	return (CGLKol2016Doc*)m_pDocument;
}
#endif //_DEBUG


// CGLKol2016View message handlers

void CGLKol2016View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CDC* pDC = GetDC();
	m_glRenderer.Reshape(pDC, cx, cy);
	ReleaseDC(pDC);
}

int CGLKol2016View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CDC* pDC = GetDC();
	m_glRenderer.CreateGLContext(pDC);
	ReleaseDC(pDC);

	return 0;
}

void CGLKol2016View::OnDestroy()
{
	CView::OnDestroy();

	CDC* pDC = GetDC();
	m_glRenderer.DestroyScene(pDC);
	ReleaseDC(pDC);
}

BOOL CGLKol2016View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CGLKol2016View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	switch (nChar) {
	case VK_UP:
		m_glRenderer.camBeta -= 0.25;
		break;
	case VK_DOWN:
		m_glRenderer.camBeta+= 0.25;
		break;
	case VK_LEFT:
		m_glRenderer.camAlpha -= 0.25;
		break;
	case VK_RIGHT:
		m_glRenderer.camAlpha += 0.25;
		break;
	case 'W':
		m_glRenderer.camDist -= 1;
		break;
	case 'S':
		m_glRenderer.camDist += 1;
		break;
	case 'Q':
		m_glRenderer.ang += 10;
	}

	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGLKol2016View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CDC* pDC = GetDC();
	m_glRenderer.PrepareScene(pDC);
	ReleaseDC(pDC);
}
