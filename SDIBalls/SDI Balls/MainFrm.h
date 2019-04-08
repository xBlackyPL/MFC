#pragma once

class CMainFrame : public CFrameWnd
{
private:
	static UINT m_buttonsIDs[];

protected:
	CMainFrame() noexcept;
DECLARE_DYNCREATE(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT create_struct);
DECLARE_MESSAGE_MAP()
	CToolBar window_tool_bar;
	CStatusBar window_status_bar;

public:
	void ResetButton(bool button);
	BOOL PreCreateWindow(CREATESTRUCT& cs) override;
	virtual ~CMainFrame();

#ifdef _DEBUG
	void AssertValid() const override;
	void Dump(CDumpContext& dc) const override;
#endif
};
