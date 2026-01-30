
// Kolok19View.cpp : implementation of the CKolok19View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Kolok19.h"
#endif

#include "Kolok19Doc.h"
#include "Kolok19View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKolok19View

IMPLEMENT_DYNCREATE(CKolok19View, CView)

BEGIN_MESSAGE_MAP(CKolok19View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CKolok19View construction/destruction

CKolok19View::CKolok19View() noexcept
{
	// TODO: add construction code here
	arm1 = new DImage();
	arm2 = new DImage();
	leg1 = new DImage();
	leg2 = new DImage();
	body = new DImage();
	pozadina = new DImage();


	arm1->Load(CString("arm1.png"));
	arm2->Load(CString("arm2.png"));
	leg1->Load(CString("leg1.png"));
	leg2->Load(CString("leg2.png"));
	body->Load(CString("body1.png"));
	pozadina->Load(CString("background.jpg"));
}

CKolok19View::~CKolok19View()
{
	delete arm1, arm2, leg1, leg2, body, pozadina;
}

BOOL CKolok19View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CKolok19View drawing

void CKolok19View::OnDraw(CDC* pDC)
{
	CKolok19Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	CBitmap* obmp = memDC.SelectObject(&bmp);

	int oldMode;
	oldMode= memDC.SetGraphicsMode(GM_ADVANCED);
	int osrc = memDC.SaveDC();

	//crtanje
	
	DrawBackground(&memDC, rect);
	DrawTransformer(&memDC);

	memDC.RestoreDC(osrc);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.SetGraphicsMode(oldMode);
	memDC.SelectObject(obmp);
	memDC.DeleteDC();
	delete memDC;
	// TODO: add draw code for native data here
}


// CKolok19View printing

BOOL CKolok19View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKolok19View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKolok19View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CKolok19View diagnostics

#ifdef _DEBUG
void CKolok19View::AssertValid() const
{
	CView::AssertValid();
}

void CKolok19View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKolok19Doc* CKolok19View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKolok19Doc)));
	return (CKolok19Doc*)m_pDocument;
}
#endif //_DEBUG


// CKolok19View message handlers

void CKolok19View::DrawBackground(CDC* pDC, CRect rc)
{
	CRect srcRect(0, 0, pozadina->Width(), pozadina->Height());

	CRect dstRect(rc.left, rc.top, rc.left + pozadina->Width(), rc.top + pozadina->Height());

	pozadina->Draw(pDC, dstRect, srcRect);
}

void CKolok19View::DrawImgTransparent(CDC* pDC, DImage* pImage)
{
	unsigned char* bits = pImage->GetDIBBits();

	unsigned char b = bits[0];
	unsigned char g = bits[1];
	unsigned char r = bits[2];

	CRect rect(0, 0, pImage->Width(), pImage->Height());

	pImage->DrawTransparent(pDC, rect, rect, RGB(r, g, b));
}

void CKolok19View::Translate(CDC* pDC, float dx, float dy, bool rightMultiply)
{
	XFORM x;
	x.eDx = dx; x.eDy = dy;
	x.eM11 = 1.0f; x.eM12 = 0.0f;
	x.eM21 = 0.0f; x.eM22 = 1.0f;

	pDC->ModifyWorldTransform(&x, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CKolok19View::Scale(CDC* pDC, float sx, float sy, bool rightMultiply)
{
	XFORM x;
	x.eDx = 0; x.eDy = 0;
	x.eM11 = sx; x.eM12 = 0.0f;
	x.eM21 = 0.0f; x.eM22 = sy;

	pDC->ModifyWorldTransform(&x, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CKolok19View::Rotate(CDC* pDC, float angle, bool rightMultiply)
{
	float ang = angle * 3.14159 / 180.0f;
	XFORM x;
	x.eDx = 0; x.eDy = 0;
	x.eM11 =cos(ang); x.eM12 = sin(ang);
	x.eM21 = -sin(ang); x.eM22 = cos(ang);

	pDC->ModifyWorldTransform(&x, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CKolok19View::DrawArm1(CDC* pDC)
{
	Translate(pDC, 34, 31,false);
	Rotate(pDC, -a1ang, false);
	Translate(pDC, -34, -31, false);
	DrawImgTransparent(pDC, arm1);

}

void CKolok19View::DrawArm2(CDC* pDC)
{
	XFORM x;
	pDC->GetWorldTransform(&x);

	Translate(pDC, 178, 54, false);
	Translate(pDC, 34, 31, false);
	Rotate(pDC, -a1ang, false);
	Translate(pDC, -34, -31, false);
	Translate(pDC, 187, 41, false);

	Translate(pDC, 23, 61, false);
	Rotate(pDC, 180 - a2ang, false);
	Translate(pDC, -23, -61, false);

	DrawImgTransparent(pDC, arm2);
	pDC->SetWorldTransform(&x);
}

void CKolok19View::DrawLeg1(CDC* pDC)
{
	Translate(pDC, 30, 125, false);
	Rotate(pDC, l1ang, false);
	Translate(pDC, -30, -125, false);

	DrawImgTransparent(pDC, leg1);

}

void CKolok19View::DrawLeg2(CDC* pDC)
{
	XFORM x;
	pDC->GetWorldTransform(&x);
	Translate(pDC, 35, 60, false);
	Rotate(pDC, l2ang, false);
	Translate(pDC, -35, -60, false);
	DrawImgTransparent(pDC, leg2);

	pDC->SetWorldTransform(&x);
}

void CKolok19View::DrawBody(CDC* pDC)
{
	Translate(pDC, 26, 133,false);
	Rotate(pDC, bang, false);
	Translate(pDC, -26,-133, false);
	DrawImgTransparent(pDC, body);
}

void CKolok19View::DrawTransformer(CDC* pDC)
{

	Translate(pDC, 200, 500, false);
	DrawLeg2(pDC);

	Translate(pDC, -5, -65, false);
	DrawLeg1(pDC);

	Translate(pDC, 212, -7, false);
	DrawBody(pDC);
	DrawArm2(pDC);

	Translate(pDC, 178, 54, false);
	DrawArm1(pDC);

}

BOOL CKolok19View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;
}

void CKolok19View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == 'R') {
		l2ang -= 10.0f;
		Invalidate();
	}
	else if (nChar == 'F') {
		l2ang += 10.0f;
		Invalidate();
	}
	else if (nChar == 'Q') {
		l1ang -= 10.0f;
		a1ang -= 10.0f;
		Invalidate();
	}
	else if (nChar == 'A') {
		l1ang += 10.0f;
		a1ang += 10.0f;
		Invalidate();
	}
	else if (nChar == 'W') {
		bang -= 10.0f;
		Invalidate();
	}
	else if (nChar == 'S') {
		bang += 10.0f;
		Invalidate();
	}
	else if (nChar == 'T') {
		a2ang -= 10.0f;
		Invalidate();
	}
	else if (nChar == 'G') {
		a2ang += 10.0f;
		Invalidate();
	}
	else if (nChar == VK_LEFT) {
		kretanje -= 10.0f;
		Invalidate();
	}
	else if (nChar == VK_RIGHT) {
		kretanje += 10.0f;
		Invalidate();
	}


	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
