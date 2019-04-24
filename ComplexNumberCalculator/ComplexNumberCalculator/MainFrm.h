#pragma once

class CMainFrame : public CFrameWnd
{
protected:
	CMainFrame() noexcept;
DECLARE_DYNCREATE(CMainFrame)
	CToolBar window_tool_bar;
	CStatusBar window_status_bar;
	afx_msg int OnCreate(LPCREATESTRUCT creation_structure);
DECLARE_MESSAGE_MAP()

public:
	BOOL PreCreateWindow(CREATESTRUCT& creation_structure) override;
	virtual ~CMainFrame();
#ifdef _DEBUG
	void AssertValid() const override;
	void Dump(CDumpContext& device_context) const override;
#endif
};
