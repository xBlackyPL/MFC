#pragma once

class SDIBallsView : public CView
{
protected:
	SDIBallsView() noexcept;
DECLARE_DYNCREATE(SDIBallsView)
DECLARE_MESSAGE_MAP()

	bool button_jamajka_;
	bool button_start_;
	bool button_japonia_;

	CRect* ball_;
	CRect* client_rect_;
	UINT timer_id_;

public:
	SDIBallsDoc* GetDocument() const;
	void OnDraw(CDC* dc) override;
	BOOL PreCreateWindow(CREATESTRUCT& cs) override;
	void OnInitialUpdate() override;
	virtual ~SDIBallsView();

	afx_msg void OnJamajka();
	afx_msg void OnUpdateJamajka(CCmdUI* cmd_ui);
	afx_msg void OnJaponia();
	afx_msg void OnUpdateJaponia(CCmdUI* cmd_ui);
	afx_msg void OnStart();
	afx_msg void OnUpdateStart(CCmdUI* cmd_ui);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR id_event);
	afx_msg BOOL OnEraseBackground(CDC* dc);

#ifdef _DEBUG
	void AssertValid() const override;
	void Dump(CDumpContext& dc) const override;
#endif
};

#ifndef _DEBUG
inline SDIBallsDoc* SDIBallsView::GetDocument() const
   { return reinterpret_cast<SDIBallsDoc*>(m_pDocument); }
#endif
