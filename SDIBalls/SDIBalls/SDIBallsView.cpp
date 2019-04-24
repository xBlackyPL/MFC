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
		ON_WM_SIZE()
END_MESSAGE_MAP()

CSDIBallsView::CSDIBallsView() noexcept
{
	is_start_button_clicked_ = false;

	client_view_ = std::make_unique<CRect>(CRect(0, 0, 0, 0));
	ball_handler_ = BallsCore::BallsHandler(client_view_.get());
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
	ball_handler_.spawnRandomBall();
	ball_handler_.spawnRandomBall();
	ball_handler_.spawnRandomBall();
}

void CSDIBallsView::OnDraw(CDC* device_context)
{
	const auto doc = GetDocument();
	ASSERT_VALID(doc);

	CDC device_context_memory;
	ASSERT(device_context_memory.CreateCompatibleDC(device_context));

	CBitmap bitmap;
	ASSERT(bitmap.CreateCompatibleBitmap(device_context, client_view_->Width(), client_view_->Height()));

	const auto old_bitmap = device_context_memory.SelectObject(&bitmap);
	device_context_memory.FillSolidRect(client_view_.get(), RGB(255, 255, 255));

	ball_handler_.drawBalls(&device_context_memory);

	ASSERT(device_context->BitBlt(0, 0, client_view_->Width(), client_view_->Height(), &device_context_memory, 0, 0,
 SRCCOPY));

	device_context_memory.SelectObject(old_bitmap);
	bitmap.DeleteObject();
	device_context_memory.DeleteDC();
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
	return dynamic_cast<CSDIBallsDoc*>(m_pDocument);
}
#endif

void CSDIBallsView::OnButtonPlus()
{
	ball_handler_.spawnRandomBall();
	if (ball_handler_.numberOfBalls() > BallsConfiguration::minimal_number_of_balls)
	{
		minus_enable_ = true;
	}
	else
	{
		minus_enable_ = false;
	}

	if (ball_handler_.numberOfBalls() >= BallsConfiguration::maximal_number_of_balls)
	{
		plus_enable_ = false;
	}
	else
	{
		plus_enable_ = true;
	}
}

void CSDIBallsView::OnUpdateButtonPlus(CCmdUI* cmd_ui)
{
	cmd_ui->Enable(plus_enable_);
}

void CSDIBallsView::OnButtonMinus()
{
	ball_handler_.killLast();
	if (ball_handler_.numberOfBalls() > BallsConfiguration::minimal_number_of_balls)
	{
		minus_enable_ = true;
	}
	else
	{
		minus_enable_ = false;
	}

	if (ball_handler_.numberOfBalls() >= BallsConfiguration::maximal_number_of_balls)
	{
		plus_enable_ = false;
	}
	else
	{
		plus_enable_ = true;
	}
}

void CSDIBallsView::OnUpdateButtonMinus(CCmdUI* cmd_ui)
{
	cmd_ui->Enable(minus_enable_);
}

void CSDIBallsView::OnButtonStart()
{
	is_start_button_clicked_ = !is_start_button_clicked_;
	auto frame = dynamic_cast<CMainFrame*>(GetParentFrame());
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
		ball_handler_.moveBalls(client_view_.get());
		Invalidate(false);
	}

	CView::OnTimer(event_id);
}

BOOL CSDIBallsView::OnEraseBackground(CDC* device_context)
{
	return 1;
}


void CSDIBallsView::OnSize(const UINT type, const int new_x, const int new_y)
{
	CView::OnSize(type, new_x, new_y);
	GetClientRect(client_view_.get());
}
