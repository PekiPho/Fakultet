
// Kolok24BView.cpp : implementation of the CKolok24BView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Kolok24B.h"
#endif

#include "Kolok24BDoc.h"
#include "Kolok24BView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKolok24BView

IMPLEMENT_DYNCREATE(CKolok24BView, CView)

BEGIN_MESSAGE_MAP(CKolok24BView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CKolok24BView construction/destruction

CKolok24BView::CKolok24BView() noexcept
{
	// TODO: add construction code here
	background = new DImage();
	basket = new DImage();
	arm = new DImage();

	background->Load(CString("Background.jpg"));
	basket->Load(CString("Basket.png"));
	arm->Load(CString("Arm.png"));

}

CKolok24BView::~CKolok24BView()
{
	delete background, basket, arm;
}

BOOL CKolok24BView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}


void CKolok24BView::DrawBackground(CDC* pDC) {
	CRect rect;
	GetClientRect(&rect);

	int bgH = background->Height();
	int bgW = background->Width();

	int topY = rect.Height() - bgH;
	int topX = (rect.Width() - bgW) / 2;

	int botX = topX + background->Width();
	int botY = topY + background->Height();

	background->Draw(pDC,  CRect(0, 0, background->Width(), background->Height()), CRect(topX, topY, botX, botY));
}


void CKolok24BView::DrawImageTransparent(CDC* pDC, DImage* pImage) {
	unsigned char* bits = pImage->GetDIBBits();

	unsigned char b = bits[0];
	unsigned char g = bits[1];
	unsigned char r = bits[2];

	CRect rect(0, 0, pImage->Width(), pImage->Height());

	pImage->DrawTransparent(pDC, rect, rect, RGB(r, g, b));
}


void CKolok24BView::Translate(CDC* pDC, float dx, float dy, bool rightMultiply) {

	XFORM x;
	x.eDx = dx; x.eDy = dy;
	x.eM11 = 1.0f; x.eM12 = 0.0f;
	x.eM21 = 0.0f; x.eM22 = 1.0f;

	pDC->ModifyWorldTransform(&x, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CKolok24BView::Scale(CDC* pDC, float sx, float sy, bool rightMultiply) {
	XFORM x;
	x.eDx = 0; x.eDy = 0;
	x.eM11 = sx; x.eM12 = 0.0f;
	x.eM21 = 0.0f; x.eM22 = sy;

	pDC->ModifyWorldTransform(&x, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CKolok24BView::Rotate(CDC* pDC, float angle, bool rightMultiply) {
	float rot = angle * 3.14159 / 180.0f;

	XFORM x;
	x.eDx = 0; x.eDy = 0;
	x.eM11 = cos(rot); x.eM12 = sin(rot);
	x.eM21 = -sin(rot); x.eM22 = cos(rot);

	pDC->ModifyWorldTransform(&x, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CKolok24BView::DrawArm(CDC* pDC) {

	Translate(pDC,-10, -10,false);
	DrawImageTransparent(pDC, arm);
	Translate(pDC, 10, 10, false);
}

void CKolok24BView::DrawBasket(CDC* pDC, int r) {

	XFORM oldXf;
	pDC->GetWorldTransform(&oldXf);


	Scale(pDC, 0.675, 0.675, false);
	int w = basket->Width();
	int h = basket->Height();

	Translate(pDC, -w / 2.0, -h / 2.0, false);
	DrawImageTransparent(pDC, basket);
	//Translate(pDC, w / 2.0, h / 2.0, false);

	pDC->SetWorldTransform(&oldXf);

	CFont font;
	font.CreateFont(0.9 * r, 0, -600, -600, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, _T("Verdana"));

	CFont* oldFont = pDC->SelectObject(&font);
	pDC->SetTextColor(RGB(0, 0, 128));
	pDC->SetBkMode(TRANSPARENT);

	pDC->SetTextAlign(TA_CENTER | TA_BASELINE);
	pDC->TextOut(0, 0, _T("R_G"));

	pDC->SelectObject(oldFont);
	font.DeleteObject();

	
}

void CKolok24BView::DrawBasketCouple(CDC* pDC, int l, int r, float angle) {

	
	XFORM old;
	pDC->GetWorldTransform(&old);
	Rotate(pDC, angle, false);
	DrawBasket(pDC, r);
	pDC->SetWorldTransform(&old);


	pDC->GetWorldTransform(&old);
	Rotate(pDC, -90.0f, false);
	DrawArm(pDC);
	pDC->SetWorldTransform(&old);

	Translate(pDC, l, 0, false);
	Rotate(pDC, angle, false);
	DrawBasket(pDC, r);
}

void CKolok24BView::DrawPlatform(CDC* pDC, int l, int r, double angle)
{
	XFORM xo;
	pDC->GetWorldTransform(&xo);
	Rotate(pDC, angle, false);
	DrawBasket(pDC, r);
	pDC->SetWorldTransform(&xo);

	for (int i = 0; i < 4; i++) {
		
		pDC->GetWorldTransform(&xo);
		Rotate(pDC, 45.0f + i * 90 + angle, false);
		Translate(pDC, 2*r, 0, false);
		DrawBasketCouple(pDC, l, r, - angle);
		pDC->SetWorldTransform(&xo);
	}
}

void CKolok24BView::DrawCarousel(CDC* pDC, int h, int r, double offset, double alpha, double beta, double angle)
{
	CRect rect;
	GetClientRect(&rect);
	pDC->SetViewportOrg(rect.Width() / 2 + offset, rect.Height() - 100);


	XFORM temp;
	pDC->GetWorldTransform(&temp);
	Rotate(pDC, (offset / 50.0) * 180.0 / 3.14, false);
	DrawBasket(pDC, r);
	pDC->SetWorldTransform(&temp);

	Translate(pDC, 0, -10, false);
	Rotate(pDC, alpha, false);


	Rotate(pDC, 180.0f, false);
	DrawArm(pDC);
	Rotate(pDC, 180.0f, false);

	Translate(pDC, 0, -182, false);
	Rotate(pDC, beta, false);

	Rotate(pDC, 180.0f, false);
	DrawArm(pDC);
	Rotate(pDC, 180.0f, false);

	Translate(pDC, 0, -182, false);

	DrawPlatform(pDC, h, 50, angle);
}




// CKolok24BView drawing

void CKolok24BView::OnDraw(CDC* pDC)
{
	CKolok24BDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	CBitmap* oldbmp = memDC.SelectObject(&bmp);

	int oldMode = memDC.SetGraphicsMode(GM_ADVANCED);

	int sdc = memDC.SaveDC();

	//crtanje
	DrawBackground(&memDC);
	DrawCarousel(&memDC, 185, 50, o, a, b, ang);

	memDC.RestoreDC(sdc);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(oldbmp);
	memDC.SetGraphicsMode(oldMode);
	memDC.DeleteDC();
	delete memDC;
}


// CKolok24BView printing

BOOL CKolok24BView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKolok24BView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKolok24BView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CKolok24BView diagnostics

#ifdef _DEBUG
void CKolok24BView::AssertValid() const
{
	CView::AssertValid();
}

void CKolok24BView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKolok24BDoc* CKolok24BView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKolok24BDoc)));
	return (CKolok24BDoc*)m_pDocument;
}
#endif //_DEBUG


// CKolok24BView message handlers

BOOL CKolok24BView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;
}

void CKolok24BView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == 'Q') {
		o -= 10.0f;
		Invalidate();
	}
	else if (nChar == 'W') {
		o += 10.0f;
		Invalidate();
	}
	else if (nChar == 'A') {
		a -= 10.0f;
		Invalidate();
	}
	else if (nChar == 'S') {
		a += 10.0f;
		Invalidate();
	}
	else if (nChar == 'D') {
		b -= 10.0f;
		Invalidate();
	}
	else if (nChar == 'F') {
		b += 10.0f;
		Invalidate();
	}
	else if (nChar == 'E') {
		ang -= 10.0f;
		Invalidate();
	}
	else if (nChar == 'R') {
		ang += 10.0f;
		Invalidate();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
