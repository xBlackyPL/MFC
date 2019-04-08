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

CSDIBallsView::CSDIBallsView() noexcept
{
	bool_1_ = true;
	bool_2_ = false;

	is_start_button_clicked_ = false;

	client_view_ = std::make_unique<CRect>(CRect(0, 0, 0, 0));
	demo_ball_ = std::make_unique<CRect>(CRect(20, 20, 80, 80));
}

CSDIBallsView::~CSDIBallsView() = default;

BOOL CSDIBallsView::PreCreateWindow(CREATESTRUCT& creation_structure)
{
	return CView::PreCreateWindow(creation_structure);
}

void CSDIBallsView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	timer_id_ = SetTimer(WM_USER + 1, 20, nullptr);
	GetClientRect(client_view_.get());
}

void CSDIBallsView::OnDraw(CDC* device_context)
{
	CSDIBallsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDC memDC;

	bool b = memDC.CreateCompatibleDC(device_context);
	ASSERT(b);

	CBitmap bmp;
	b = bmp.CreateCompatibleBitmap(device_context, client_view_->Width(), client_view_->Height());
	ASSERT(b);
	CBitmap* pOldBitmap = memDC.SelectObject(&bmp);
	memDC.FillSolidRect(client_view_.get(), RGB(255, 255, 255));

	CPen* pPen = new CPen(PS_SOLID, 3, RGB(255, 0, 0));
	CBrush* pBrush = new CBrush(RGB(255, 0, 0));

	CPen* pOldPen = memDC.SelectObject(pPen);
	CBrush* pOldBrush = memDC.SelectObject(pBrush);

	memDC.Ellipse(demo_ball_.get());

	memDC.SelectObject(pOldPen);
	memDC.SelectObject(pOldBrush);

	b = device_context->BitBlt(0, 0, client_view_->Width(), client_view_->Height(), &memDC, 0, 0, SRCCOPY);
	ASSERT(b);

	memDC.SelectObject(pOldBitmap);
	bmp.DeleteObject();
	memDC.DeleteDC();

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
	return static_cast<CSDIBallsDoc*>(m_pDocument);
}
#endif

void CSDIBallsView::OnButtonPlus()
{
	bool_1_ = false;
	bool_2_ = true;
}

void CSDIBallsView::OnUpdateButtonPlus(CCmdUI* cmd_ui)
{
	cmd_ui->SetCheck(bool_1_);
}

void CSDIBallsView::OnButtonMinus()
{
	bool_1_ = true;
	bool_2_ = false;
}

void CSDIBallsView::OnUpdateButtonMinus(CCmdUI* cmd_ui)
{
	cmd_ui->SetCheck(bool_2_);
}

void CSDIBallsView::OnButtonStart()
{
	is_start_button_clicked_ = !is_start_button_clicked_;
	auto* frame = static_cast<CMainFrame*>(GetParentFrame());
	frame->ResetButton(is_start_button_clicked_);
}

void CSDIBallsView::OnUpdateButtonStart(CCmdUI* cmd_ui)
{
}

void CSDIBallsView::OnDestroy()
{
	KillTimer(timer_id_);
	CView::OnDestroy();
}

void CSDIBallsView::OnTimer(const UINT_PTR event_id)
{
	if (is_start_button_clicked_)
	{
		demo_ball_->OffsetRect(2, 5);
		Invalidate(false);
	}

	CView::OnTimer(event_id);
}

BOOL CSDIBallsView::OnEraseBackground(CDC* device_context)
{
	return 1;
}
