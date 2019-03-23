#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "SortComparison.h"
#endif

#include "SortComparisonDoc.h"
#include "SortComparisonView.h"
#include "Sorters.h"
#include <sstream>
#include <random>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CSortComparisonView, CView)

BEGIN_MESSAGE_MAP(CSortComparisonView, CView)
    ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
    ON_COMMAND(SORT_BUTTON, &CSortComparisonView::OnSortButtonPressed)
    ON_UPDATE_COMMAND_UI(SORT_BUTTON, &CSortComparisonView::OnSortButtonUpdate)
END_MESSAGE_MAP()


CSortComparisonView::CSortComparisonView() noexcept
{
    // TODO: add construction code here

}

CSortComparisonView::~CSortComparisonView()
{
}

void CSortComparisonView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
    GetClientRect(_clientRect.get());
}

BOOL CSortComparisonView::PreCreateWindow(CREATESTRUCT& cs)
{
    _clientRect = std::make_unique<CRect>(0, 0, 0, 0);

    return CView::PreCreateWindow(cs);
}

void CSortComparisonView::OnDraw(CDC* pDC)
{
    CSortComparisonDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (nullptr == pDoc)
    {
        return;
    }

    if (_isSortingFinished)
    {
        drawChartAxis(pDC);
    }
}


BOOL CSortComparisonView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // default preparation
    return DoPreparePrinting(pInfo);
}

void CSortComparisonView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add extra initialization before printing
}

void CSortComparisonView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add cleanup after printing
}


#ifdef _DEBUG
void CSortComparisonView::AssertValid() const
{
    CView::AssertValid();
}

void CSortComparisonView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CSortComparisonDoc* CSortComparisonView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSortComparisonDoc)));
    return (CSortComparisonDoc*)m_pDocument;
}

#endif //_DEBUG

void CSortComparisonView::OnSortButtonUpdate(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(!_sortingInProgress);
}

void CSortComparisonView::OnSortButtonPressed()
{
    _sortingInProgress = true;
    _sortingTimes.clear();
    std::vector<int> randomVector;
    std::random_device deviceSeed;

    std::mt19937 generator(deviceSeed());
    const std::uniform_int_distribution<> distribution(0, 1000);
    for (auto i = 0; i < 10000; ++i)
    {
        randomVector.push_back(distribution(generator));
    }

    auto start = std::chrono::steady_clock::now();
    Sorters::bubbleSort(randomVector);
    _sortingTimes.insert(std::pair<std::string, std::chrono::nanoseconds>(
        Sorters::bubbleSortId, std::chrono::steady_clock::now() - start));

    start = std::chrono::steady_clock::now();
    Sorters::insertionSort(randomVector);
    _sortingTimes.insert(std::pair<std::string, std::chrono::nanoseconds>(
        Sorters::insertionSortId, std::chrono::steady_clock::now() - start));

    start = std::chrono::steady_clock::now();
    Sorters::halfSort(randomVector);
    _sortingTimes.insert(std::pair<std::string, std::chrono::nanoseconds>(
        Sorters::halfSortId, std::chrono::steady_clock::now() - start));

    start = std::chrono::steady_clock::now();
    Sorters::selectionSort(randomVector);
    _sortingTimes.insert(std::pair<std::string, std::chrono::nanoseconds>(
        Sorters::selectionSortId, std::chrono::steady_clock::now() - start));


    _isSortingFinished = true;
    _sortingInProgress = false;
    GetDocument()->UpdateAllViews(NULL);
}

void CSortComparisonView::drawChartAxis(CDC* pDC)
{
    const auto topMargin = _clientRect->Height() / 20;
    const auto leftMargin = _clientRect->Width() / 20;
    const CPoint yAxisTip(leftMargin, topMargin);
    const CPoint chartTip(leftMargin, topMargin * 18);
    const CPoint xAxisTip(leftMargin * 18, topMargin * 18);
    pDC->MoveTo(yAxisTip); pDC->LineTo(leftMargin - 5, topMargin + 5);
    pDC->MoveTo(yAxisTip); pDC->LineTo(leftMargin + 5, topMargin + 5);
    pDC->MoveTo(yAxisTip); pDC->LineTo(chartTip);
    pDC->MoveTo(chartTip); pDC->LineTo(xAxisTip);

    const auto bubbleTime = _sortingTimes[Sorters::bubbleSortId].count() / 10e7;
    const auto insertionTime = _sortingTimes[Sorters::insertionSortId].count() / 10e7;
    const auto selectioTime = _sortingTimes[Sorters::selectionSortId].count() / 10e7;
    const auto halfTime = _sortingTimes[Sorters::halfSortId].count() / 10e7;

    auto bubbleChart = CRect(leftMargin + _clientRect->Width() / 20,
        topMargin * 18 - bubbleTime,
        leftMargin + 3 * (_clientRect->Width() / 20),
        topMargin * 18);

    auto insertionChart = CRect(leftMargin + 4 * _clientRect->Width() / 20,
        topMargin * 18 - insertionTime,
        leftMargin + 6 * (_clientRect->Width() / 20),
        topMargin * 18);

    auto selectionChart = CRect(leftMargin + 7 * _clientRect->Width() / 20,
        topMargin * 18 - selectioTime,
        leftMargin + 9 * (_clientRect->Width() / 20),
        topMargin * 18);

    auto haltChart = CRect(leftMargin + 10 * _clientRect->Width() / 20,
        topMargin * 18 - halfTime,
        leftMargin + 12 * (_clientRect->Width() / 20),
        topMargin * 18);

    pDC->FillSolidRect(bubbleChart, RGB(100, 100, 0));
    pDC->FillSolidRect(insertionChart, RGB(100, 200, 0));
    pDC->FillSolidRect(selectionChart, RGB(100, 100, 200));
    pDC->FillSolidRect(haltChart, RGB(100, 0, 0));
}