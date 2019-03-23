#pragma once
#include <string>
#include <chrono>
#include <map>

class CSortComparisonView : public CView
{
private:
    using TimeContainer = std::map<std::string, std::chrono::nanoseconds>;
    using CRecPtr = std::unique_ptr<CRect>;

    bool _sortingInProgress = false;
    bool _isSortingFinished = false;
    TimeContainer _sortingTimes;
    CRecPtr _clientRect;

    void drawChartAxis(CDC* pDC);

protected:
    CSortComparisonView() noexcept;
    DECLARE_DYNCREATE(CSortComparisonView)
    DECLARE_MESSAGE_MAP()
    BOOL OnPreparePrinting(CPrintInfo* pInfo) override;
    void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) override;
    void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) override;

public:
#ifdef _DEBUG
    void AssertValid() const override;
    void Dump(CDumpContext& dc) const override;
#endif

    CSortComparisonDoc* GetDocument() const;
    void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) override;
    void OnDraw(CDC* pDC) override;
    BOOL PreCreateWindow(CREATESTRUCT& cs) override;
    virtual ~CSortComparisonView();
    afx_msg void OnSortButtonPressed();
    afx_msg void OnSortButtonUpdate(CCmdUI* pCmdUI);
};

#ifndef _DEBUG
inline CSortComparisonDoc* CSortComparisonView::GetDocument() const {
    return reinterpret_cast<CSortComparisonDoc*>(m_pDocument);
}
#endif
