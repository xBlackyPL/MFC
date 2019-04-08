#include "stdafx.h"
#include "MainFrm.h"
#ifndef SHARED_HANDLERS
#include "SDIBalls.h"
#endif

#include "SDIBallsDoc.h"
#include "SDIBallsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void CALLBACK zfx_timer_proc(const HWND window_handle)
{
	::SendMessage(window_handle, WM_TIMER, 0, 0);
}

IMPLEMENT_DYNCREATE(CSDIBallsView, CView)

BEGIN_MESSAGE_MAP(CSDIBallsView, CView)
	ON_COMMAND(ID_BUTTON_PLUS, &CSDIBallsView::OnButtonPlus)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_PLUS, &CSDIBallsView::OnUpdateButtonPlus)
	ON_COMMAND(ID_BUTTON_MINUS, &CSDIBallsView::OnButtonMinus)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_MINUS, &CSDIBallsView::OnUpdateButtonMinus)
	ON_COMMAND(ID_BUTTON_START, &CSDIBallsView::OnButtonStart)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_START, &CSDIBallsView::OnUpdateButtonStart)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CSDIBallsView construction/destruction

CSDIBallsView::CSDIBallsView() noexcept
{
	m_bJamajka = true;
	m_bJaponia = false;
	m_bStart = false;

	m_pClientRect = new CRect(0, 0, 0, 0);
	m_pBall = new CRect(20, 20, 80, 80);
}

CSDIBallsView::~CSDIBallsView()
{
	delete m_pClientRect;
	delete m_pBall;
}

BOOL CSDIBallsView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CSDIBallsView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	m_nTimerID = SetTimer(WM_USER + 1, 20, NULL); // WM_TIMER
	//m_nTimerID = SetTimer(WM_USER + 1, 20, ZfxTimerProc);

	GetClientRect(m_pClientRect);
}

void CSDIBallsView::OnDraw(CDC* pDC)
{
	CSDIBallsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDC memDC;

	bool b = memDC.CreateCompatibleDC(pDC);
	ASSERT(b);

	CBitmap bmp;
	b = bmp.CreateCompatibleBitmap(pDC, m_pClientRect->Width(), m_pClientRect->Height());
	ASSERT(b);
	CBitmap* pOldBitmap = memDC.SelectObject(&bmp);
	memDC.FillSolidRect(m_pClientRect, RGB(255, 255, 255));

	CPen* pPen = new CPen(PS_SOLID, 3, RGB(255, 0, 0));
	CBrush* pBrush = new CBrush(RGB(255, 0, 0));

	CPen* pOldPen = memDC.SelectObject(pPen);
	CBrush* pOldBrush = memDC.SelectObject(pBrush);

	memDC.Ellipse(m_pBall);

	memDC.SelectObject(pOldPen);
	memDC.SelectObject(pOldBrush);

	b = pDC->BitBlt(0, 0, m_pClientRect->Width(), m_pClientRect->Height(), &memDC, 0, 0, SRCCOPY);
	ASSERT(b);

	memDC.SelectObject(pOldBitmap);
	bmp.DeleteObject();
	memDC.DeleteDC();

	//CBrush* pBrush = new CBrush(RGB(255, 0, 0));
	//CPen* pen = new CPen(PS_SOLID, 3, RGB(255, 0, 0));
	//CPen* oldPen = pDC->SelectObject(pen);
	//CBrush* pOldBrush = pDC->SelectObject(pBrush);
	//

	//pDC->Ellipse(m_pBall);

	//pDC->SelectObject(oldPen);
	//pDC->SelectObject(pOldBrush);
	delete pBrush;
	delete pPen;
}

#ifdef _DEBUG
void CSDIBallsView::AssertValid() const
{
	CView::AssertValid();
}

void CSDIBallsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDIBallsDoc* CSDIBallsView::GetDocument() const 
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIBallsDoc)));
	return (CSDIBallsDoc*)m_pDocument;
}
#endif 

void CSDIBallsView::OnButtonPlus()
{
	m_bJamajka = false;
	m_bJaponia = true;
}

void CSDIBallsView::OnUpdateButtonPlus(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bJamajka);
}

void CSDIBallsView::OnButtonMinus()
{
	m_bJamajka = true;
	m_bJaponia = false;
}

void CSDIBallsView::OnUpdateButtonMinus(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bJaponia);
}

void CSDIBallsView::OnButtonStart()
{
	m_bStart = !m_bStart;
	CMainFrame* pFrame = (CMainFrame*)GetParentFrame();
	pFrame->ResetButton(m_bStart);
}

void CSDIBallsView::OnUpdateButtonStart(CCmdUI *pCmdUI)
{
}

void CSDIBallsView::OnDestroy()
{
	KillTimer(m_nTimerID);
	CView::OnDestroy();

	// TODO: Dodaj tutaj swój kod procedury obs³ugi komunikatów
}

void CSDIBallsView::OnTimer(UINT_PTR nIDEvent)
{

	if (m_bStart)
	{
		m_pBall->OffsetRect(2, 5);
		Invalidate(false);
	}

	CView::OnTimer(nIDEvent);
}

BOOL CSDIBallsView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Dodaj tutaj swój kod procedury obs³ugi komunikatów i/lub wywo³aj domyœlny
	return 1;
	//return CView::OnEraseBkgnd(pDC);
}

/*
	- Stworzyc aplikacje SDI Balls
	- Dodaæ obs³ugê Timera
	- W³asny toolbar z przyciskami: START/STOP (zmienia siê grafika przycisku)
									- Dwa przyciski: + / -
									+ - dodaje kulke
									- - usuwa kulke
	- Poczatkowo 3 kulki (nieaktywny minus), nie wiecej niz 10 (nieaktywny plus)
	- Pilki o rozmiarach losowych (30 - 120)
	- Kolory pilek losowe
	- Rysowanie poprzez pamiêciowy kontekst urz¹dzenia
	- Wszystkie atrybuty 
	- Dodac klase CBall pochodna od CRect (kolorowej kulki)
			SetColor(COLORREF) /// DELETE + Create
			SetBallSize // Const ref to rect
			DrawBall() // CDC pointer

			CreateObjects(COLORREF BallColor ) // Kreuje pedzel i pioro, deleteobject jest wywolywany dla piora i pedzla
			InitObjects() // Przydzielenie pamieci i kreacja
			SetBall(Rect, Color, vector) // Ustawia prostokat, kolor i wektory ruchu
			SetOffset(int nOffX, int OffY) // Przesuniecie ruchu
			SetBoundRect( ref rozmiar obszaru clienta, po ktorym porusza sie kulka)

			// Zmodyfikowac klase CBall w oparciu o te skladowe - offset X oraz offset Y
*/
