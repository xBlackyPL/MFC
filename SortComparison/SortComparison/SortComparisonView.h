#pragma once
#include <string>
#include <chrono>
#include <map>

class CSortComparisonView : public CView
{
private:
    using TimeContainer = std::map<std::string, std::chrono::nanoseconds>;
    using TimeMeasurement = std::pair<std::string, std::chrono::nanoseconds>;
    using Time = std::chrono::steady_clock;
    using CRecPtr = std::unique_ptr<CRect>;
    using CFontPtr = std::unique_ptr<CFont>;

    bool sorting_in_progress_ = false;
    bool is_sorting_finished_ = false;
    CFont* old_font_;
    CFontPtr new_font_;
    TimeContainer sorting_times_;
    CRecPtr client_rect_;

    void drawChartAxis(CDC* p_dc);

protected:
    CSortComparisonView() noexcept;
    DECLARE_DYNCREATE(CSortComparisonView)
    DECLARE_MESSAGE_MAP()
    BOOL OnPreparePrinting(CPrintInfo* p_info) override;
    void OnBeginPrinting(CDC* p_dc, CPrintInfo* p_info) override;
    void OnEndPrinting(CDC* p_dc, CPrintInfo* p_info) override;

public:
#ifdef _DEBUG
    void AssertValid() const override;
    void Dump(CDumpContext& dc) const override;
#endif

    CSortComparisonDoc* GetDocument() const;
    void OnPrepareDC(CDC* p_dc, CPrintInfo* p_info) override;
    void OnDraw(CDC* p_dc) override;
    BOOL PreCreateWindow(CREATESTRUCT& cs) override;
    virtual ~CSortComparisonView();
    afx_msg void OnSortButtonPressed();
    afx_msg void OnSortButtonUpdate(CCmdUI* p_cmd_ui);
};

#ifndef _DEBUG
inline CSortComparisonDoc* CSortComparisonView::GetDocument() const {
    return reinterpret_cast<CSortComparisonDoc*>(m_pDocument);
}
#endif
