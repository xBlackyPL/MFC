#include "stdafx.h"
#include "ComplexNumberCalculator.h"

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

CMainFrame::CMainFrame() noexcept
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(const LPCREATESTRUCT creation_structure)
{
	if (CFrameWnd::OnCreate(creation_structure) == -1)
	{
		return -1;
	}

	if (!window_tool_bar.CreateEx(this, TBSTYLE_FLAT,
	                              WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY |
	                              CBRS_SIZE_DYNAMIC) ||
		!window_tool_bar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

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

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& creation_structure)
{
	creation_structure.cx = 350;
	creation_structure.cy = 300;	
	creation_structure.x = 0;
	creation_structure.y = 0;
	return CFrameWnd::PreCreateWindow(creation_structure);	
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
#endif
