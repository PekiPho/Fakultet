
// GL Kol 2 2019View.cpp : implementation of the CGLKol22019View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "GL Kol 2 2019.h"
#endif

#include "GL Kol 2 2019Doc.h"
#include "GL Kol 2 2019View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGLKol22019View

IMPLEMENT_DYNCREATE(CGLKol22019View, CView)

BEGIN_MESSAGE_MAP(CGLKol22019View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CGLKol22019View construction/destruction

CGLKol22019View::CGLKol22019View() noexcept
{
	// TODO: add construction code here

}

CGLKol22019View::~CGLKol22019View()
{
}

BOOL CGLKol22019View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGLKol22019View drawing

void CGLKol22019View::OnDraw(CDC* pDC)
{
	CGLKol22019Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_glRenderer.DrawScene(pDC);
}


// CGLKol22019View printing

BOOL CGLKol22019View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGLKol22019View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGLKol22019View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CGLKol22019View diagnostics

#ifdef _DEBUG
void CGLKol22019View::AssertValid() const
{
	CView::AssertValid();
}

void CGLKol22019View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGLKol22019Doc* CGLKol22019View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGLKol22019Doc)));
	return (CGLKol22019Doc*)m_pDocument;
}
#endif //_DEBUG


// CGLKol22019View message handlers

void CGLKol22019View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CDC* pDC = GetDC();
	m_glRenderer.Reshape(pDC, cx, cy);
	ReleaseDC(pDC);
}


BOOL CGLKol22019View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CGLKol22019View::OnDestroy()
{
	CView::OnDestroy();

	CDC* pDC = GetDC();
	m_glRenderer.DestroyScene(pDC);
	ReleaseDC(pDC);
}

int CGLKol22019View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CDC* pDC = GetDC();
	m_glRenderer.CreateGLContext(pDC);
	ReleaseDC(pDC);

	return 0;
}

void CGLKol22019View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
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
	case '7':
		m_glRenderer.ang4 += 5;
		break;
	case '8':
		m_glRenderer.ang4 -= 5;
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

void CGLKol22019View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CDC* pDC = GetDC();
	m_glRenderer.PrepareScene(pDC);
	ReleaseDC(pDC);
}
