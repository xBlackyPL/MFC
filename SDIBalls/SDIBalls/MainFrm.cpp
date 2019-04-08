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

UINT CMainFrame::buttons_ids_[] =
{
	ID_BUTTON_PLUS,
	ID_BUTTON_MINUS,
	ID_BUTTON_START,
	ID_APP_ABOUT,
};

CMainFrame::CMainFrame() noexcept { }
CMainFrame::~CMainFrame() = default;

int CMainFrame::OnCreate(const LPCREATESTRUCT creation_structure)
{
	if (CFrameWnd::OnCreate(creation_structure) == -1)
	{
		return -1;
	}
	if (!window_tool_bar.Create(this) ||
		!window_tool_bar.LoadBitmap(IDR_SDIBALLSBAR) ||
		!window_tool_bar.SetButtons(buttons_ids_, sizeof(buttons_ids_) / sizeof(UINT)))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	auto& bar_ctrl = window_tool_bar.GetToolBarCtrl();
	bar_ctrl.SetBitmapSize(CSize(59, 31));
	bar_ctrl.SetButtonSize(CSize(59,31));

	if (!window_status_bar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1; 
	}
	window_status_bar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	window_tool_bar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&window_tool_bar);
	return 0;
}

void CMainFrame::ResetButton(const bool button)
{
	const int button_id = sizeof(buttons_ids_) / sizeof(UINT);
	if (button)
	{
		window_tool_bar.SetButtonInfo(2, ID_BUTTON_START, TBBS_BUTTON, button_id);
	}
	else
	{
		window_tool_bar.SetButtonInfo(2, ID_BUTTON_START, TBBS_BUTTON, 2);
	}
	window_tool_bar.Invalidate();
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& creation_struct)
{
	return CFrameWnd::PreCreateWindow(creation_struct);
}

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& device_context) const
{
	CFrameWnd::Dump(device_context);
}
#endif //_DEBUG
