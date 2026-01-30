
// Kolok22View.cpp : implementation of the CKolok22View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Kolok22.h"
#endif

#include "Kolok22Doc.h"
#include "Kolok22View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKolok22View

IMPLEMENT_DYNCREATE(CKolok22View, CView)

BEGIN_MESSAGE_MAP(CKolok22View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CKolok22View construction/destruction

CKolok22View::CKolok22View() noexcept
{
	// TODO: add construction code here
	base = new DImage();
	arm1 = new DImage();
	arm2 = new DImage();
	head = new DImage();
	pozadina = new DImage();
	bShadow = new DImage();
	a1Shadow = new DImage();
	a2Shadow = new DImage();
	hShadow = new DImage();

	base->Load(CString("base.png"));
	arm1->Load(CString("arm1.png"));
	arm2->Load(CString("arm2.png"));
	head->Load(CString("head.png"));
	pozadina->Load(CString("pozadina.jpg"));
	bShadow->Load(CString("base_shadow.png"));
	a1Shadow->Load(CString("arm1_shadow.png"));
	a2Shadow->Load(CString("arm2_shadow.png"));
	hShadow->Load(CString("head_shadow.png"));

}

CKolok22View::~CKolok22View()
{
	delete base, arm1, arm2, head, pozadina, bShadow, a1Shadow, hShadow,a2Shadow;
}

BOOL CKolok22View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CKolok22View drawing

void CKolok22View::OnDraw(CDC* pDC)
{
	CKolok22Doc* pDoc = GetDocument();
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

	int oldMode = memDC.SetGraphicsMode(GM_ADVANCED);
	int sdc = memDC.SaveDC();

	//crtanje
	DrawBackground(&memDC);
	XFORM xo;
	memDC.GetWorldTransform(&xo);
	DrawLampShadow(&memDC);
	memDC.SetWorldTransform(&xo);
	memDC.GetWorldTransform(&xo);
	DrawLamp(&memDC,false);
	memDC.GetWorldTransform(&xo);

	memDC.RestoreDC(sdc);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.SetGraphicsMode(oldMode);
	memDC.SelectObject(&obmp);
	memDC.DeleteDC();
	delete memDC;



	// TODO: add draw code for native data here
}


// CKolok22View printing

BOOL CKolok22View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKolok22View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKolok22View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CKolok22View diagnostics

#ifdef _DEBUG
void CKolok22View::AssertValid() const
{
	CView::AssertValid();
}

void CKolok22View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKolok22Doc* CKolok22View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKolok22Doc)));
	return (CKolok22Doc*)m_pDocument;
}
#endif //_DEBUG


// CKolok22View message handlers

void CKolok22View::Translate(CDC* pDC, float dx, float dy, bool rightMultiply)
{
	XFORM x;
	x.eDx = dx; x.eDy = dy;
	x.eM11 = 1.0f; x.eM12 = 0.0f;
	x.eM21 = 0.0f; x.eM22 = 1.0f;

	pDC->ModifyWorldTransform(&x, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CKolok22View::Scale(CDC* pDC, float sx, float sy, bool rightMultiply)
{
	XFORM x;
	x.eDx = 0; x.eDy = 0;
	x.eM11 = sx; x.eM12 = 0.0f;
	x.eM21 = 0.0f; x.eM22 = sy;

	pDC->ModifyWorldTransform(&x, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);

}

void CKolok22View::Rotate(CDC* pDC, float angle, bool rightMultiply)
{
	float ang = angle * 3.14159 / 180.0f;
	XFORM x;
	x.eDx = 0; x.eDy = 0;
	x.eM11 = cos(ang); x.eM12 = sin(ang);
	x.eM21 = -sin(ang); x.eM22 = cos(ang);

	pDC->ModifyWorldTransform(&x, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CKolok22View::DrawBackground(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);

	int rectH = rect.Height();
	int rectW = rect.Width();

	int pozadinaH = pozadina->Height();
	int pozadinaW = pozadina->Width();

	int topX = (rectW - pozadinaW) / 2;
	int topY = rectH - pozadinaH;

	int botX = topX + pozadina->Width();
	int botY = topY + pozadina->Height();

	pozadina->Draw(pDC, CRect(0, 0, pozadina->Width(), pozadina->Height()), CRect(topX, topY, botX, botY));
}

void CKolok22View::DrawImgTransparent(CDC* pDC, DImage* pImage)
{
	unsigned char* bits = pImage->GetDIBBits();

	unsigned char b = bits[0];
	unsigned char g = bits[1];
	unsigned char r = bits[2];

	CRect rect(0, 0, pImage->Width(), pImage->Height());

	pImage->DrawTransparent(pDC, rect, rect, RGB(r, g, b));
}

void CKolok22View::DrawLampBase(CDC* pDC, bool bIsShadow)
{
	CRect rect;
	GetClientRect(&rect);

	int x = rect.Width() / 2;
	int y = rect.Height() - 250;

	pDC->SetViewportOrg(x, y);

	if (bIsShadow) {
		DrawImgTransparent(pDC, bShadow);
	}
	else {
		DrawImgTransparent(pDC, base);
	}

	Translate(pDC, 105, -30, false);
}

void CKolok22View::DrawLampArm1(CDC* pDC, bool bIsShadow)
{
	Translate(pDC, 58, 61, false);
	Rotate(pDC, ang1, false);
	Translate(pDC, -58, -61, false);

	
	if(!bIsShadow)
		DrawImgTransparent(pDC, arm1);
	else {
		Rotate(pDC, -90.0f, false);
		Scale(pDC, 1, 0.25, false);
		DrawImgTransparent(pDC, a1Shadow);
	}

	Translate(pDC, 309, 61, false);
}

void CKolok22View::DrawLampArm2(CDC* pDC, bool bIsShadow)
{
	//Translate(pDC, 36, 40, false);
	Rotate(pDC, ang2, false);
	Translate(pDC, -36, -40, false);

	if (!bIsShadow)
		DrawImgTransparent(pDC, arm2);
	else {
		//Scale(pDC, 1, 0.25, false);
		DrawImgTransparent(pDC, a2Shadow);
	}


	Translate(pDC, 272, 40, false);
}

void CKolok22View::DrawLampHead(CDC* pDC, bool bIsShadow)
{
	Rotate(pDC, hAng, false);
	Translate(pDC, -178, -100,false);

	if (!bIsShadow)
		DrawImgTransparent(pDC, head);
	else {
		//Scale(pDC, 1, 0.25, false);
		DrawImgTransparent(pDC, hShadow);
	}

}

void CKolok22View::DrawLamp(CDC* pDC, bool bIsShadow)
{
	if (!bIsShadow) {
		DrawLampBase(pDC, false);
		DrawLampArm1(pDC, false);
		DrawLampArm2(pDC, false);
		DrawLampHead(pDC, false);
	}
	else {
		DrawLampBase(pDC, true);
		DrawLampArm1(pDC, true);
		DrawLampArm2(pDC, true);
		DrawLampHead(pDC, true);
	}
	
}

void CKolok22View::DrawLampShadow(CDC* pDC)
{
	DrawLamp(pDC, true);
}

BOOL CKolok22View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;
}

void CKolok22View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == '1') {
		ang1 -= 10.0f;
		Invalidate();
	}
	else if (nChar == '2') {
		ang1 += 10.0f;
		Invalidate();
	}
	else if (nChar == '3') {
		ang2 -= 10.0f;
		Invalidate();
	}
	else if (nChar == '4') {
		ang2 += 10.0f;
		Invalidate();
	}
	else if (nChar == '5') {
		hAng -= 10.0f;
		Invalidate();
	}
	else if (nChar == '6') {
		hAng += 10.0f;
		Invalidate();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
