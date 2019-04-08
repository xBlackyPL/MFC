#pragma once
#include <memory>

class CSDIBallsView : public CView
{
private:
	std::unique_ptr<CRect> client_view_;
	std::unique_ptr<CRect> demo_ball_;
	UINT timer_id_;
	bool bool_1_;
	bool is_start_button_clicked_;
	bool bool_2_;

protected:
	CSDIBallsView() noexcept;

DECLARE_DYNCREATE(CSDIBallsView)
DECLARE_MESSAGE_MAP()

public:
	CSDIBallsDoc* GetDocument() const;

	void OnDraw(CDC* device_context) override;
	BOOL PreCreateWindow(CREATESTRUCT& creation_structure) override;
	void OnInitialUpdate() override;
	virtual ~CSDIBallsView();

#ifdef _DEBUG
	void AssertValid() const override;
	void Dump(CDumpContext& dc) const override;
#endif

	afx_msg void OnButtonPlus();
	afx_msg void OnUpdateButtonPlus(CCmdUI* cmd_ui);
	afx_msg void OnButtonMinus();
	afx_msg void OnUpdateButtonMinus(CCmdUI* cmd_ui);
	afx_msg void OnButtonStart();
	afx_msg void OnUpdateButtonStart(CCmdUI* cmd_ui);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR event_id);
	afx_msg BOOL OnEraseBackground(CDC* device_context);
};

#ifndef _DEBUG
inline CSDIBallsDoc* CSDIBallsView::GetDocument() const
   { return reinterpret_cast<CSDIBallsDoc*>(m_pDocument); }
#endif
