
// GL Kol 2 2023View.cpp : implementation of the CGLKol22023View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "GL Kol 2 2023.h"
#endif

#include "GL Kol 2 2023Doc.h"
#include "GL Kol 2 2023View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGLKol22023View

IMPLEMENT_DYNCREATE(CGLKol22023View, CView)

BEGIN_MESSAGE_MAP(CGLKol22023View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CGLKol22023View construction/destruction

CGLKol22023View::CGLKol22023View() noexcept
{
	// TODO: add construction code here

}

CGLKol22023View::~CGLKol22023View()
{
}

BOOL CGLKol22023View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGLKol22023View drawing

void CGLKol22023View::OnDraw(CDC* pDC)
{
	CGLKol22023Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_glRenderer.DrawScene(pDC);
}


// CGLKol22023View printing

BOOL CGLKol22023View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGLKol22023View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGLKol22023View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CGLKol22023View diagnostics

#ifdef _DEBUG
void CGLKol22023View::AssertValid() const
{
	CView::AssertValid();
}

void CGLKol22023View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGLKol22023Doc* CGLKol22023View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGLKol22023Doc)));
	return (CGLKol22023Doc*)m_pDocument;
}
#endif //_DEBUG


// CGLKol22023View message handlers

void CGLKol22023View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CDC* pDC = GetDC();
	m_glRenderer.Reshape(pDC, cx, cy);
	ReleaseDC(pDC);
}

BOOL CGLKol22023View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

int CGLKol22023View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CDC* pDC = GetDC();
	m_glRenderer.CreateGLContext(pDC);
	ReleaseDC(pDC);

	return 0;
}

void CGLKol22023View::OnDestroy()
{
	CView::OnDestroy();

	CDC* pDC = GetDC();
	m_glRenderer.DestroyScene(pDC);
	ReleaseDC(pDC);
}

void CGLKol22023View::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	
	CDC* pDC = GetDC();
	m_glRenderer.PrepareScene(pDC);
	ReleaseDC(pDC);
}

void CGLKol22023View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar) {
	case '1':
		m_glRenderer.ang1 += 5;
		break;
	case '2':
		m_glRenderer.ang1 -= 5;
		break;
	case '3':
		m_glRenderer.ang2 += 5;
		break;
	case '4':
		m_glRenderer.ang2 -= 5;
		break;
	case '5':
		m_glRenderer.ang3 += 5;
		break;
	case '6':
		m_glRenderer.ang3 -= 5;
		break;
	case VK_UP:
		m_glRenderer.beta += 0.1;
		break;
	case VK_DOWN:
		m_glRenderer.beta -= 0.1;
		break;
	case VK_LEFT:
		m_glRenderer.alpha += 0.1;
		break;
	case VK_RIGHT:
		m_glRenderer.alpha -= 0.1;
		break;
	case VK_OEM_4:
		m_glRenderer.cameraDist -= 1;
		break;
	case VK_OEM_6:
		m_glRenderer.cameraDist += 1;
		break;
	default:
		break;

	}

	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
