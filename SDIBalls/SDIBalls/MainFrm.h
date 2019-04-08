#pragma once

class CMainFrame : public CFrameWnd
{
private:
	static UINT buttons_ids_[];

protected:
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)
	CToolBar          window_tool_bar;
	CStatusBar        window_status_bar;
	afx_msg int OnCreate(LPCREATESTRUCT creation_structure);
	DECLARE_MESSAGE_MAP()

public:
	void ResetButton(bool button);
	virtual BOOL PreCreateWindow(CREATESTRUCT& creation_struct);
	virtual ~CMainFrame();
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& device_context) const;
#endif
};


