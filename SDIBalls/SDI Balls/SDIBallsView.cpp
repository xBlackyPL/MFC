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


void CALLBACK ZfxTimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime)
{
	::SendMessage(hWnd, WM_TIMER, 0, 0);
}

IMPLEMENT_DYNCREATE(SDIBallsView, CView)

BEGIN_MESSAGE_MAP(SDIBallsView, CView)
		ON_COMMAND(ID_JAMAJKA, &SDIBallsView::OnJamajka)
		ON_UPDATE_COMMAND_UI(ID_JAMAJKA, &SDIBallsView::OnUpdateJamajka)
		ON_COMMAND(ID_JAPONIA, &SDIBallsView::OnJaponia)
		ON_UPDATE_COMMAND_UI(ID_JAPONIA, &SDIBallsView::OnUpdateJaponia)
		ON_COMMAND(ID_START, &SDIBallsView::OnStart)
		ON_UPDATE_COMMAND_UI(ID_START, &SDIBallsView::OnUpdateStart)
		ON_WM_DESTROY()
		ON_WM_TIMER()
		ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

SDIBallsView::SDIBallsView() noexcept
{
	button_jamajka_ = true;
	button_japonia_ = false;
	button_start_ = false;

	client_rect_ = new CRect(0, 0, 0, 0);
	ball_ = new CRect(20, 20, 80, 80);
}

SDIBallsView::~SDIBallsView()
{
	delete client_rect_;
	delete ball_;
}

BOOL SDIBallsView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void SDIBallsView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	timer_id_ = SetTimer(WM_USER + 1, 20, nullptr); // WM_TIMER
	//timer_id_ = SetTimer(WM_USER + 1, 20, ZfxTimerProc);

	GetClientRect(client_rect_);
}

void SDIBallsView::OnDraw(CDC* dc)
{
	SDIBallsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDC memDC;

	bool b = memDC.CreateCompatibleDC(dc);
	ASSERT(b);

	CBitmap bmp;
	b = bmp.CreateCompatibleBitmap(dc, client_rect_->Width(), client_rect_->Height());
	ASSERT(b);
	CBitmap* pOldBitmap = memDC.SelectObject(&bmp);
	memDC.FillSolidRect(client_rect_, RGB(255, 255, 255));

	CPen* pPen = new CPen(PS_SOLID, 3, RGB(255, 0, 0));
	CBrush* pBrush = new CBrush(RGB(255, 0, 0));

	CPen* pOldPen = memDC.SelectObject(pPen);
	CBrush* pOldBrush = memDC.SelectObject(pBrush);

	memDC.Ellipse(ball_);

	memDC.SelectObject(pOldPen);
	memDC.SelectObject(pOldBrush);

	b = dc->BitBlt(0, 0, client_rect_->Width(), client_rect_->Height(), &memDC, 0, 0, SRCCOPY);
	ASSERT(b);

	memDC.SelectObject(pOldBitmap);
	bmp.DeleteObject();
	memDC.DeleteDC();

	//CBrush* pBrush = new CBrush(RGB(255, 0, 0));
	//CPen* pen = new CPen(PS_SOLID, 3, RGB(255, 0, 0));
	//CPen* oldPen = pDC->SelectObject(pen);
	//CBrush* pOldBrush = pDC->SelectObject(pBrush);
	//

	//pDC->Ellipse(ball_);

	//pDC->SelectObject(oldPen);
	//pDC->SelectObject(pOldBrush);
	delete pBrush;
	delete pPen;
}

#ifdef _DEBUG
void SDIBallsView::AssertValid() const
{
	CView::AssertValid();
}

void SDIBallsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

SDIBallsDoc* SDIBallsView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(SDIBallsDoc)));
	return (SDIBallsDoc*)m_pDocument;
}
#endif

void SDIBallsView::OnJamajka()
{
	button_jamajka_ = false;
	button_japonia_ = true;
}

void SDIBallsView::OnUpdateJamajka(CCmdUI* cmd_ui)
{
	cmd_ui->SetCheck(button_jamajka_);
}

void SDIBallsView::OnJaponia()
{
	button_jamajka_ = true;
	button_japonia_ = false;
}

void SDIBallsView::OnUpdateJaponia(CCmdUI* cmd_ui)
{
	cmd_ui->SetCheck(button_japonia_);
}

void SDIBallsView::OnStart()
{
	button_start_ = !button_start_;
	CMainFrame* pFrame = (CMainFrame*)GetParentFrame();
	pFrame->ResetButton(button_start_);
}

void SDIBallsView::OnUpdateStart(CCmdUI* cmd_ui)
{
}

void SDIBallsView::OnDestroy()
{
	KillTimer(timer_id_);
	CView::OnDestroy();
}

void SDIBallsView::OnTimer(UINT_PTR id_event)
{
	if (button_start_)
	{
		ball_->OffsetRect(2, 5);
		Invalidate(false);
	}

	CView::OnTimer(id_event);
}

BOOL SDIBallsView::OnEraseBackground(CDC* dc)
{
	// TODO: Dodaj tutaj swój kod procedury obs³ugi komunikatów i/lub wywo³aj domyœlny
	return 1;
	//return CView::OnEraseBackground(pDC);
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
