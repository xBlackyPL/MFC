#pragma once

class CMainFrame : public CFrameWnd
{
private:
	static UINT m_buttonsIDs[];

protected:
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	void ResetButton(bool btn);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual ~CMainFrame();
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};


