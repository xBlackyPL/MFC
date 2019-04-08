#include "stdafx.h"
#include "SDIBalls.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
		ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

UINT CMainFrame::m_buttonsIDs[] =
{
	ID_JAMAJKA,
	ID_JAPONIA,
	ID_START,
	ID_APP_ABOUT,
};

CMainFrame::CMainFrame() noexcept
{
}

CMainFrame::~CMainFrame() = default;

int CMainFrame::OnCreate(const LPCREATESTRUCT create_struct)
{
	if (CFrameWnd::OnCreate(create_struct) == -1)
	{
		return -1;
	}

	if (!window_tool_bar.Create(this) ||
		!window_tool_bar.LoadBitmap(IDR_MYTOOLBAR) ||
		!window_tool_bar.SetButtons(m_buttonsIDs, sizeof(m_buttonsIDs) / sizeof(UINT)))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	auto& bar_ctrl = window_tool_bar.GetToolBarCtrl();
	bar_ctrl.SetBitmapSize(CSize(31, 29));
	bar_ctrl.SetButtonSize(CSize(39, 36));

	if (!window_status_bar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;
	}
	window_status_bar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));
	window_tool_bar.EnableDocking(CBRS_ALIGN_ANY);

	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&window_tool_bar);

	return 0;
}

void CMainFrame::ResetButton(const bool button)
{
	const int button_ix = sizeof(m_buttonsIDs) / sizeof(UINT);
	if (button)
	{
		window_tool_bar.SetButtonInfo(2, ID_START, TBBS_BUTTON, button_ix);
	}
	else
	{
		window_tool_bar.SetButtonInfo(2, ID_START, TBBS_BUTTON, 2);
	}
	window_tool_bar.Invalidate();
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
	{
		return FALSE;
	}
	return TRUE;
}

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG
