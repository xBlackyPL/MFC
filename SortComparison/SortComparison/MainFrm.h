#pragma once

class CMainFrame : public CFrameWnd
{
protected:
    CMainFrame() noexcept;
    DECLARE_DYNCREATE(CMainFrame)
    CStatusBar        m_wndStatusBar;
    CToolBar          m_wndToolBar;
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    DECLARE_MESSAGE_MAP()

public:
#ifdef _DEBUG
    void AssertValid() const override;
    void Dump(CDumpContext& dc) const override;
#endif

    BOOL PreCreateWindow(CREATESTRUCT& cs) override;
    virtual ~CMainFrame();
};
