#pragma once


class CSDIBallsView : public CView
{
protected: // create from serialization only
	CSDIBallsView() noexcept;
	DECLARE_DYNCREATE(CSDIBallsView)


	bool m_bJamajka;
	bool m_bStart;
	bool m_bJaponia;

	CRect* m_pBall;
	CRect* m_pClientRect; 

	UINT m_nTimerID;
	DECLARE_MESSAGE_MAP()

public:
	CSDIBallsDoc* GetDocument() const;

	void OnDraw(CDC* pDC) override;
	BOOL PreCreateWindow(CREATESTRUCT& cs) override;
	void OnInitialUpdate() override; 
	virtual ~CSDIBallsView();

#ifdef _DEBUG
	void AssertValid() const override;
	void Dump(CDumpContext& dc) const override;
#endif

	afx_msg void OnButtonPlus();
	afx_msg void OnUpdateButtonPlus(CCmdUI *pCmdUI);
	afx_msg void OnButtonMinus();
	afx_msg void OnUpdateButtonMinus(CCmdUI *pCmdUI);
	afx_msg void OnButtonStart();
	afx_msg void OnUpdateButtonStart(CCmdUI *pCmdUI);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in Zaj4View.cpp
inline CSDIBallsDoc* CSDIBallsView::GetDocument() const
   { return reinterpret_cast<CSDIBallsDoc*>(m_pDocument); }
#endif

