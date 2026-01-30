
// 2018KolokView.cpp : implementation of the CMy2018KolokView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "2018Kolok.h"
#endif

#include "2018KolokDoc.h"
#include "2018KolokView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy2018KolokView

IMPLEMENT_DYNCREATE(CMy2018KolokView, CView)

BEGIN_MESSAGE_MAP(CMy2018KolokView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CMy2018KolokView construction/destruction

CMy2018KolokView::CMy2018KolokView() noexcept
{
	// TODO: add construction code here

	bager = new DImage();
	arm1 = new DImage();
	arm2 = new DImage();
	pozadina = new DImage();

	viljuska = GetEnhMetaFile(CString("viljuska.emf"));
	GetEnhMetaFileHeader(viljuska, sizeof(ENHMETAHEADER), &viljuskaHeader);

	bager->Load(CString("bager.png"));
	arm1->Load(CString("arm1.png"));
	arm2->Load(CString("arm2.png"));
	pozadina->Load(CString("pozadina.png"));


}

CMy2018KolokView::~CMy2018KolokView()
{
	DeleteEnhMetaFile(viljuska);
	delete bager, arm1, arm2, pozadina;
}

void CMy2018KolokView::Translate(CDC* pDC, float dx, float dy, bool rightMultiply) {
	XFORM x;

	x.eDx = dx;
	x.eDy = dy;
	x.eM11 = 1.0; x.eM12 = 0.0;
	x.eM21 = 0.0f; x.eM22 = 1.0;


	pDC->ModifyWorldTransform(&x, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CMy2018KolokView::Rotate(CDC* pDC, float angle, bool rightMultiply) {
	XFORM x;

	float ugao = angle * 3.14159f / 180.0f;

	x.eDx = 0; x.eDy = 0;
	x.eM11 = cos(ugao); x.eM12 = sin(ugao);
	x.eM21 = -sin(ugao); x.eM22 = cos(ugao);

	pDC->ModifyWorldTransform(&x, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);

}

void CMy2018KolokView::Scale(CDC* pDC, float sx, float sy, bool rightMultiply) {
	XFORM x;

	x.eDx = 0; x.eDy = 0;
	x.eM11 = sx; x.eM12 = 0;
	x.eM21 = 0; x.eM22 = sy;

	pDC->ModifyWorldTransform(&x, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);

}

void CMy2018KolokView::DrawBackground(CDC* pDC) {
	CRect rect;
	GetClientRect(&rect);

	int pozadinaH = pozadina->Height();
	int pozadinaW = pozadina->Width();

	int clientH = rect.Height();
	int clientW = rect.Width();

	int topX = (clientW - pozadinaW) / 2;
	int topY = (clientH - pozadinaH);

	int bottomX = topX + pozadinaW;
	int bottomY = topY + pozadinaH;


	pozadina->Draw(pDC, CRect(0,0,pozadina->Width(),pozadina->Height()), CRect(topX,topY,bottomX,bottomY));
}


void CMy2018KolokView::DrawImgTransparent(CDC* pDC, DImage* pImage) {

	unsigned char* bits = pImage->GetDIBBits();

	unsigned char b = bits[0];
	unsigned char g = bits[1];
	unsigned char r = bits[2];

	CRect rect(0, 0, pImage->Width(), pImage->Height());


	pImage->DrawTransparent(pDC, rect, rect, RGB(r, g, b));
}

void CMy2018KolokView::DrawBody(CDC* pDC) {

	CRect rect;
	GetClientRect(&rect);

	int x = rect.Width() - bager->Width() + kretanjeBagera;
	int y = rect.Height() - bager->Height();

	pDC->SetViewportOrg(x, y);

	DrawImgTransparent(pDC, bager);

	Translate(pDC, 5, 105, false);
}

void CMy2018KolokView::DrawArm1(CDC* pDC) {
	Translate(pDC, 58, 61, false);
	Rotate(pDC, arm1Ang, false);
	Translate(pDC, -58, -61, false);

	DrawImgTransparent(pDC, arm1);

	Translate(pDC, 309, 61, false);
}

void CMy2018KolokView::DrawArm2(CDC* pDC) {
	//Translate(pDC, 36, 40, false);
	Rotate(pDC, arm2Ang, false);
	Translate(pDC, -36, -40, false);

	DrawImgTransparent(pDC, arm2);

	Translate(pDC, 272, 40, false);
}

void CMy2018KolokView::DrawFork(CDC* pDC) {
	//Translate(pDC, 14, 20, false);
	Rotate(pDC, forkAng, false);

	Scale(pDC, 2.5, 2.5, false);
	Translate(pDC, -14, -20, false);

	int w = viljuskaHeader.rclBounds.right - viljuskaHeader.rclBounds.left;
	int h = viljuskaHeader.rclBounds.bottom - viljuskaHeader.rclBounds.top;
	pDC->PlayMetaFile(viljuska, CRect(0, 0, w, h));
}




BOOL CMy2018KolokView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMy2018KolokView drawing

void CMy2018KolokView::OnDraw(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	CBitmap* oldbmp = memDC.SelectObject(&bmp);

	int oldMode=memDC.SetGraphicsMode(GM_ADVANCED);


	CMy2018KolokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	int sdc = memDC.SaveDC();
	DrawBackground(&memDC);

	//Translate(pDC, -200, 0, false);

	DrawBody(&memDC);
	DrawArm1(&memDC);
	DrawArm2(&memDC);
	DrawFork(&memDC);

	memDC.RestoreDC(sdc);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(oldbmp);
	memDC.SetGraphicsMode(oldMode);
	memDC.DeleteDC();
	delete memDC;

}


// CMy2018KolokView printing

BOOL CMy2018KolokView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy2018KolokView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy2018KolokView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMy2018KolokView diagnostics

#ifdef _DEBUG
void CMy2018KolokView::AssertValid() const
{
	CView::AssertValid();
}

void CMy2018KolokView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy2018KolokDoc* CMy2018KolokView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy2018KolokDoc)));
	return (CMy2018KolokDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy2018KolokView message handlers

void CMy2018KolokView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == '1') {
		arm1Ang += 10.0f;
		Invalidate();
	}
	else if (nChar == '2') {
		arm1Ang -= 10.0f;
		Invalidate();
	}
	else if (nChar == '3') {
		arm2Ang += 10.0f;
		Invalidate();
	}
	else if (nChar == '4') {
		arm2Ang -= 10.0f;
		Invalidate();
	}
	else if (nChar == '5') {
		forkAng += 10.0f;
		Invalidate();
	}
	else if (nChar == '6') {
		forkAng -= 10.0f;
		Invalidate();
	}
	else if (nChar == VK_LEFT) {
		kretanjeBagera -= 10.0f;
		Invalidate();
	}
	else if (nChar == VK_RIGHT) {
		kretanjeBagera += 10.0f;
		Invalidate();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CMy2018KolokView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;
}
