
// lab2View.cpp : implementation of the Clab2View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "lab2.h"
#endif

#include "lab2Doc.h"
#include "lab2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Clab2View

IMPLEMENT_DYNCREATE(Clab2View, CView)

BEGIN_MESSAGE_MAP(Clab2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// Clab2View construction/destruction

Clab2View::Clab2View() noexcept
{
	m_hCactusLight = GetEnhMetaFile(_T("cactus_part_light.emf"));
	m_hCactusDark = GetEnhMetaFile(_T("cactus_part.emf"));

	if (!m_hCactusLight || !m_hCactusDark)
		AfxMessageBox(_T("Failed to load cactus images!"));

}

Clab2View::~Clab2View()
{
}

BOOL Clab2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Clab2View drawing

void Clab2View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
{
	XFORM xf;
	xf.eM11 = 1.0f;
	xf.eM12 = 0.0f;
	xf.eM21 = 0.0f;
	xf.eM22 = 1.0f;
	xf.eDx = dX;
	xf.eDy = dY;


	DWORD mode;

	if (rightMultiply)
		mode = MWT_RIGHTMULTIPLY;
	else mode = MWT_LEFTMULTIPLY;

	pDC->ModifyWorldTransform(&xf, mode);

}

void Clab2View::Scale(CDC* pDC, float sX, float sY, bool rightMultiply)
{
	XFORM xf;
	xf.eM11 = sX;
	xf.eM12 = 0.0f;
	xf.eM21 = 0.0f;
	xf.eM22 = sY;
	xf.eDx = 0.0f;
	xf.eDy = 0.0f;

	DWORD mode;

	if (rightMultiply)
		mode = MWT_RIGHTMULTIPLY;
	else mode = MWT_LEFTMULTIPLY;

	pDC->ModifyWorldTransform(&xf, mode);

}

void Clab2View::Rotate(CDC* pDC, float angle, bool rightMultiply)
{
	double a = angle;

	XFORM xf;
	xf.eM11 = cos(a);
	xf.eM12 = sin(a);
	xf.eM21 = -sin(a);
	xf.eM22 = cos(a);
	xf.eDx = 0.0f;
	xf.eDy = 0.0f;

	DWORD mode;

	if (rightMultiply)
		mode = MWT_RIGHTMULTIPLY;
	else mode = MWT_LEFTMULTIPLY;

	pDC->ModifyWorldTransform(&xf, mode);
}

void Clab2View::DrawFigure(CDC* pDC)
{
	pDC->SetGraphicsMode(GM_ADVANCED);

	XFORM old;
	pDC->GetWorldTransform(&old);

	Clab2View::Translate(pDC, 250.0f, 500.0f, false);

	DrawCactus(pDC);

	pDC->SetWorldTransform(&old);
}

void Clab2View::DrawCactus(CDC* pDC)
{

	XFORM saved;
	pDC->GetWorldTransform(&saved);
	const float G = 25.0f;
	
	//prvi ovaj u centar
	Translate(pDC, 0, -4.5 * G, false);
	DrawPart(pDC, 2.2f, 3.0f, 0, true);

	//drugi ovaj odma iznad
	Translate(pDC, 0, -3.0 * G, false);
	DrawPart(pDC, 0.8f, 3.0f, 0, false);

	//treci ova leva grana
	Translate(pDC, -1.0*G, 0.5 * G, false);
	DrawPart(pDC, 0.8f, 3.0f, -45.0f, false);


	//cetvrti ovaj levo sto je horizontalan
	Translate(pDC, -2.5f * G, -1.0*G, false);
	DrawPart(pDC, 1.6f,3.0f, 90.0f, false);

	//peti ovaj duguljast ispravan
	Translate(pDC, 1.5*G, -1.5 * G, false);
	DrawPart(pDC, 1.4f, 3.0f, 0, false);


	//sesti ovaj velik na vrh najvisi
	Translate(pDC, 0, -3 * G, false);
	DrawPart(pDC, 2.5f, 3.0f, 0, false);


	//sedmi desno grananje
	Translate(pDC, 3 * G, 5.5f*G, false);
	DrawPart(pDC, 0.8f, 3.0f, 45.0f, false);


	//osmi ovaj horizontalan desno grananje
	Translate(pDC, 2.5*G, -1 * G, false);
	DrawPart(pDC, 1.6f, 3.0f, 90.0f, false);


	//deveti ovaj light uspravan na desnu granu
	Translate(pDC, -1.5*G, -1.5 * G, false);
	DrawPart(pDC, 1.4f, 3.0f, 0, true);

	//deseti ovaj sto ide gore skroz desno
	Translate(pDC, 4*G, 0.5 * G, false);
	DrawPart(pDC, 1.5f, 3.0f, 45.0f, false);

	//jedanaest ovaj nanize skroz desno
	Translate(pDC, 0, 2 * G, false);
	DrawPart(pDC, 1.5f, 3.0f, -45.0f, false);


	XFORM identity = { 1,0,0,1,0,0 };
	pDC->SetWorldTransform(&identity);


	CPen blackPen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(&blackPen);
	CBrush greenBrush(RGB(50, 180, 50));
	CBrush* oldBrush = pDC->SelectObject(&greenBrush);
	int cx = 250;
	int cy = 350;
	int r = 10;
	pDC->Ellipse(cx - r, cy - r, cx + r, cy + r);

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(&blackPen);


	pDC->SetWorldTransform(&saved);
}


void Clab2View::DrawPart(CDC* pDC, float sx, float sy, float angle, bool light)
{
	XFORM saved;
	pDC->GetWorldTransform(&saved);

	angle = angle * 3.14159f / 180.0f;
	if (light)
		angle += lightRotation;

	Rotate(pDC, angle, false);
	Scale(pDC, sx, sy, false);

	HENHMETAFILE hEmf = light ? m_hCactusLight : m_hCactusDark;

	RECT r;
	r.left = -12.5;
	r.right = 12.5;
	r.top = -12.5;
	r.bottom =12.5;

	PlayEnhMetaFile(pDC->GetSafeHdc(), hEmf, &r);

	pDC->SetWorldTransform(&saved);
}



void Clab2View::OnDraw(CDC* pDC)
{
	Clab2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	DrawFigure(pDC);


	CPen* oldPen;

	if (showGrid) {
		CPen gridPen(PS_SOLID, 1, RGB(255, 255, 255));
		oldPen = pDC->SelectObject(&gridPen);

		CRect rr;
		GetClientRect(&rr);

		for (int x = 0; x < rr.Width(); x += 25) {
			pDC->MoveTo(x, 0);
			pDC->LineTo(x, rr.Height());
		}

		for (int y = 0; y < rr.Width(); y += 25) {
			pDC->MoveTo(0, y);
			pDC->LineTo(rr.Width(), y);
		}
	}

	CPen blackBox(PS_SOLID, 2, RGB(0, 0, 0));

	if (showGrid)
		pDC->SelectObject(&blackBox);
	else oldPen = pDC->SelectObject(&blackBox);

	CBrush* oldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
	pDC->Rectangle(0, 0, 500, 500);

	pDC->SelectObject(&oldPen);
	pDC->SelectObject(&oldBrush);
}


// Clab2View printing

BOOL Clab2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Clab2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Clab2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// Clab2View diagnostics

#ifdef _DEBUG
void Clab2View::AssertValid() const
{
	CView::AssertValid();
}

void Clab2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Clab2Doc* Clab2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Clab2Doc)));
	return (Clab2Doc*)m_pDocument;
}
#endif //_DEBUG


// Clab2View message handlers


BOOL Clab2View::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);

	pDC->FillSolidRect(&rect, RGB(200, 230, 255));

	return TRUE;
}


void Clab2View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 'g' || nChar == 'G') {
		showGrid = !showGrid;
		Invalidate();
	}

	const float step = 3.14159f / 4.0f;

	if (nChar == 'a' || nChar == 'A') {
		lightRotation -= step;
		Invalidate();
	}

	if (nChar == 'd' || nChar == 'D') {
		lightRotation += step;
		Invalidate();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
