
// MonapuzzleView.cpp : implementation of the CMonapuzzleView class
//

#include "pch.h"
#include "framework.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "lab3.h"
#include "DImage.h"
#endif

#include "lab3Doc.h"
#include "lab3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TO_RAD(x) {x * PI/180}
const float PI = 3.141592653f;
const int GUNIT = 25; // Grid Unit
const int N = 9;

using namespace std;

// CMonapuzzleView

IMPLEMENT_DYNCREATE(CMonapuzzleView, CView)

BEGIN_MESSAGE_MAP(CMonapuzzleView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CMonapuzzleView construction/destruction

CMonapuzzleView::CMonapuzzleView() noexcept
{

	tranX[0] = -48;  tranY[0] = -48;  rot[0] = 25;   mirX[0] = false; mirY[0] = true;
	tranX[1] = -58;  tranY[1] = 236;  rot[1] = 19;   mirX[1] = true;  mirY[1] = false;
	tranX[2] = 256;  tranY[2] = -64;  rot[2] = -76;  mirX[2] = true;  mirY[2] = false;
	tranX[3] = 248;  tranY[3] = 250;  rot[3] = 161;  mirX[3] = true;  mirY[3] = false;
	tranX[4] = 240;  tranY[4] = 92;   rot[4] = 252;  mirX[4] = false; mirY[4] = true;
	tranX[5] = 92;   tranY[5] = 248;  rot[5] = 114;  mirX[5] = true;  mirY[5] = false;
	tranX[6] = 106;  tranY[6] = -54;  rot[6] = -125; mirX[6] = true;  mirY[6] = false;
	tranX[7] = -60;  tranY[7] = 100;  rot[7] = -72;  mirX[7] = false; mirY[7] = true;
	tranX[8] = 90;   tranY[8] = 90;   rot[8] = -121; mirX[8] = false; mirY[8] = true;
}

CMonapuzzleView::~CMonapuzzleView()
{

}

BOOL CMonapuzzleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

#pragma region Funkcije Transformacija
void CMonapuzzleView::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
{
	XFORM xform{};
	xform.eM11 = 1.0;
	xform.eM12 = 0.0;
	xform.eM21 = 0.0;
	xform.eM22 = 1.0;
	xform.eDx = dX;
	xform.eDy = dY;

	pDC->ModifyWorldTransform(&xform, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CMonapuzzleView::Scale(CDC* pDC, float sX, float sY, bool rightMultiply)
{
	XFORM xform{};
	xform.eM11 = sX;
	xform.eM12 = 0.0;
	xform.eM21 = 0.0;
	xform.eM22 = sY;
	xform.eDx = 0.0;
	xform.eDy = 0.0;

	pDC->ModifyWorldTransform(&xform, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CMonapuzzleView::Rotate(CDC* pDC, float angle, bool rightMultiply)
{
	angle = TO_RAD(angle);
	XFORM xform{};

	xform.eM11 = cos(angle);
	xform.eM12 = sin(angle);
	xform.eM21 = -sin(angle);
	xform.eM22 = cos(angle);
	xform.eDx = 0.0;
	xform.eDy = 0.0;

	pDC->ModifyWorldTransform(&xform, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CMonapuzzleView::Mirror(CDC* pDC, bool mx, bool my, bool rightMultiply)
{
	XFORM xform{};

	xform.eM11 = mx ? -1.0 : 1.0;
	xform.eM12 = 0.0;
	xform.eM21 = 0.0;
	xform.eM22 = my ? -1.0 : 1.0;
	xform.eDx = 0.0;
	xform.eDy = 0.0;

	pDC->ModifyWorldTransform(&xform, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
#pragma endregion




void CMonapuzzleView::Postavi(CDC* pDC, CString imeSlike, int x, int y, int angle, bool mirrorX, bool mirrorY, bool samoPlava)
{
	XFORM oldTransform;
	pDC->GetWorldTransform(&oldTransform);

	Translate(pDC, -128, -128);
	Rotate(pDC, angle);
	Mirror(pDC, mirrorX, mirrorY);
	Translate(pDC, 128, 128);

	Translate(pDC, x, y);

	DImage img;
	img.Load(imeSlike);
	int w = img.Width();
	int h = img.Height();
	
	CBitmap bmpImage, bmpMask;

	bmpImage.CreateCompatibleBitmap(pDC, w, h);
	bmpMask.CreateBitmap(w, h, 1, 1, NULL);

	CDC* pSrcDC = new CDC();
	pSrcDC->CreateCompatibleDC(pDC);
	pSrcDC->SelectObject(&bmpImage);
	CDC* pMaskDC = new CDC();
	pMaskDC->CreateCompatibleDC(pDC);
	pMaskDC->SelectObject(&bmpMask);

	img.Draw(pSrcDC, CRect(0, 0, w, h), CRect(0, 0, w, h));

	COLORREF pozadina = pSrcDC->GetPixel(0, 0);
	pSrcDC->SetBkColor(pozadina);
	pMaskDC->BitBlt(0, 0, w, h, pSrcDC, 0, 0, SRCCOPY);

	pSrcDC->SetTextColor(RGB(255, 255, 255));
	pSrcDC->SetBkColor(RGB(0, 0, 0));

	
	Filtriraj(&bmpImage, samoPlava);
	pSrcDC->BitBlt(0, 0, w, h, pMaskDC, 0, 0, SRCAND);


	pDC->BitBlt(0, 0, w, h, pMaskDC, 0, 0, SRCAND);
	pDC->BitBlt(0, 0, w, h, pSrcDC, 0, 0, SRCPAINT);

	delete pSrcDC;
	delete pMaskDC;

	pDC->SetWorldTransform(&oldTransform);
}

void CMonapuzzleView::Filtriraj(CBitmap* bmpImage, bool boja)
{
	BITMAP bitmapStruct;
	bmpImage->GetBitmap(&bitmapStruct);

	DWORD dwCount = bitmapStruct.bmWidthBytes * bitmapStruct.bmHeight;
	vector<BYTE> imageBits(dwCount);

	if (bmpImage->GetBitmapBits(dwCount, imageBits.data()) == 0) return;

	BITMAPINFO* bmpInfo = reinterpret_cast<BITMAPINFO*>(&bitmapStruct);
	WORD bpp = bmpInfo->bmiHeader.biBitCount;

	for (size_t i = 0; i < imageBits.size() - 3; i += 4)
	{
		BYTE b = imageBits[i];
		BYTE g = imageBits[i + 1];
		BYTE r = imageBits[i + 2];
		
		int grayedBit = 64 + (r + g + b) / 3;
		if (grayedBit > 255) grayedBit = 255;

		r = g = boja ? 0 : grayedBit;
		b = grayedBit;

		imageBits[i] = b;
		imageBits[i + 1] = g;
		imageBits[i + 2] = r;
	}
	if (bmpImage->SetBitmapBits(dwCount, imageBits.data()));
}

void CMonapuzzleView::Cela(CDC* pDC)
{
	Postavi(pDC, CString("1.bmp"), tranX[0], tranY[0], rot[0], mirX[0], mirY[0]);
	Postavi(pDC, CString("2.bmp"), tranX[1], tranY[1], rot[1], mirX[1], mirY[1]);
	Postavi(pDC, CString("3.bmp"), tranX[2], tranY[2], rot[2], mirX[2], mirY[2]);
	Postavi(pDC, CString("4.bmp"), tranX[3], tranY[3], rot[3], mirX[3], mirY[3]);
	Postavi(pDC, CString("5.bmp"), tranX[4], tranY[4], rot[4], mirX[4], mirY[4]);
	Postavi(pDC, CString("6.bmp"), tranX[5], tranY[5], rot[5], mirX[5], mirY[5], true);
	Postavi(pDC, CString("7.bmp"), tranX[6], tranY[6], rot[6], mirX[6], mirY[6]);
	Postavi(pDC, CString("8.bmp"), tranX[7], tranY[7], rot[7], mirX[7], mirY[7]);
	Postavi(pDC, CString("9.bmp"), tranX[8], tranY[8], rot[8], mirX[8], mirY[8]);
}



void CMonapuzzleView::OnDraw(CDC* pDC)
{
	CMonapuzzleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	CRect clientRect;
	GetClientRect(&clientRect);
	CDC* pMemDC = new CDC();
	pMemDC->CreateCompatibleDC(pDC);

	CBitmap memBitmap;
	memBitmap.CreateCompatibleBitmap(pDC, clientRect.Width(), clientRect.Height());
	pMemDC->SelectObject(&memBitmap);

	pMemDC->FillSolidRect(clientRect, pDC->GetBkColor());

	int oldMode = pMemDC->SetGraphicsMode(GM_ADVANCED);

	Cela(pMemDC);

	
	pMemDC->SetGraphicsMode(oldMode);

	pDC->BitBlt(0, 0, clientRect.Width(), clientRect.Height(), pMemDC, 0, 0, SRCCOPY);
	
	delete pMemDC;
}


// CMonapuzzleView printing

BOOL CMonapuzzleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMonapuzzleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMonapuzzleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}



#ifdef _DEBUG
void CMonapuzzleView::AssertValid() const
{
	CView::AssertValid();
}

void CMonapuzzleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMonapuzzleDoc* CMonapuzzleView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMonapuzzleDoc)));
	return (CMonapuzzleDoc*)m_pDocument;
}
#endif //_DEBUG



void CMonapuzzleView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}