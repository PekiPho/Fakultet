
// GL Kol 2 2020View.cpp : implementation of the CGLKol22020View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "GL Kol 2 2020.h"
#endif

#include "GL Kol 2 2020Doc.h"
#include "GL Kol 2 2020View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGLKol22020View

IMPLEMENT_DYNCREATE(CGLKol22020View, CView)

BEGIN_MESSAGE_MAP(CGLKol22020View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CGLKol22020View construction/destruction

CGLKol22020View::CGLKol22020View() noexcept
{
	// TODO: add construction code here

}

CGLKol22020View::~CGLKol22020View()
{
}

BOOL CGLKol22020View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGLKol22020View drawing

void CGLKol22020View::OnDraw(CDC* pDC)
{
	CGLKol22020Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	m_glRenderer.DrawScene(pDC);
}


// CGLKol22020View printing

BOOL CGLKol22020View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGLKol22020View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGLKol22020View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CGLKol22020View diagnostics

#ifdef _DEBUG
void CGLKol22020View::AssertValid() const
{
	CView::AssertValid();
}

void CGLKol22020View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGLKol22020Doc* CGLKol22020View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGLKol22020Doc)));
	return (CGLKol22020Doc*)m_pDocument;
}
#endif //_DEBUG


// CGLKol22020View message handlers

void CGLKol22020View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CDC* pDC = GetDC();
	m_glRenderer.Reshape(pDC, cx, cy);
	ReleaseDC(pDC);
}

void CGLKol22020View::OnDestroy()
{
	CView::OnDestroy();

	CDC* pDC = GetDC();
	m_glRenderer.DestroyScene(pDC);
	ReleaseDC(pDC);
}

void CGLKol22020View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
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

int CGLKol22020View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CDC* pDC = GetDC();
	m_glRenderer.CreateGLContext(pDC);
	ReleaseDC(pDC);

	return 0;
}

void CGLKol22020View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CDC* pDC = GetDC();
	m_glRenderer.PrepareScene(pDC);
	ReleaseDC(pDC);
}

BOOL CGLKol22020View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}
