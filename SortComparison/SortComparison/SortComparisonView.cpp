#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "SortComparison.h"
#endif

#include "SortComparisonDoc.h"
#include "SortComparisonView.h"
#include "Sorters.h"
#include <sstream>
#include <random>
#include "CColorRectange.h"

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


using namespace Sorters;

CSortComparisonView::CSortComparisonView() noexcept
{
    // TODO: add construction code here
}

CSortComparisonView::~CSortComparisonView()
{
}

void CSortComparisonView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
    GetClientRect(client_rect_.get());
}

BOOL CSortComparisonView::PreCreateWindow(CREATESTRUCT& cs)
{
    client_rect_ = std::make_unique<CRect>(0, 0, 0, 0);
    const auto log_font = new LOGFONT;

    memset(log_font, 0, sizeof(LOGFONT));
    log_font->lfCharSet = DEFAULT_CHARSET;
    log_font->lfHeight = 100;
    log_font->lfWidth = 6;
    log_font->lfWeight = FW_NORMAL;

    CString font_face_name("Arial");
    lstrcpyn(log_font->lfFaceName, font_face_name, font_face_name.GetLength() + 1);
    new_font_ = std::make_unique<CFont>();

    if (!(new_font_->CreatePointFontIndirect(log_font)))
    {
        TRACE0("Could Not create font... \n");
    }

    return CView::PreCreateWindow(cs);
}

void CSortComparisonView::OnDraw(CDC* p_dc)
{
    CSortComparisonDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (nullptr == pDoc)
    {
        return;
    }

    if (is_sorting_finished_)
    {
        drawChartAxis(p_dc);
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
    return static_cast<CSortComparisonDoc*>(m_pDocument);
}

#endif //_DEBUG

void CSortComparisonView::OnSortButtonUpdate(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(!sorting_in_progress_);
}

void CSortComparisonView::OnSortButtonPressed()
{
    sorting_in_progress_ = true;
    sorting_times_.clear();
    std::vector<int> random_vector;
    std::random_device device_seed;

    std::mt19937 generator(device_seed());
    const std::uniform_int_distribution<> distribution(0, 1000);
    for (auto i = 0; i < 10000; ++i)
    {
        random_vector.push_back(distribution(generator));
    }

    auto start = Time::now();
    bubbleSort(random_vector);
    sorting_times_.insert(TimeMeasurement(bubbleSortId, Time::now() - start));

    start = Time::now();
    insertionSort(random_vector);
    sorting_times_.insert(TimeMeasurement(insertionSortId, Time::now() - start));

    start = Time::now();
    halfSort(random_vector);
    sorting_times_.insert(TimeMeasurement(halfSortId, Time::now() - start));

    start = Time::now();
    selectionSort(random_vector);
    sorting_times_.insert(TimeMeasurement(selectionSortId, Time::now() - start));

    is_sorting_finished_ = true;
    sorting_in_progress_ = false;
    GetDocument()->UpdateAllViews(nullptr);
}

void CSortComparisonView::drawChartAxis(CDC* p_dc)
{
    const auto top_margin = client_rect_->Height() / 20;
    const auto left_margin = client_rect_->Width() / 20;

    const CPoint y_axis_tip(left_margin, top_margin);
    const CPoint chart_tip(left_margin, top_margin * 18);
    const CPoint x_axis_tip(left_margin * 18, top_margin * 18);

    p_dc->MoveTo(y_axis_tip);
    p_dc->LineTo(left_margin - 5, top_margin + 5);
    p_dc->MoveTo(y_axis_tip);
    p_dc->LineTo(left_margin + 5, top_margin + 5);
    p_dc->MoveTo(y_axis_tip);

    p_dc->TextOut(left_margin - 25, top_margin * 2.5f, CString("3.5"));
    p_dc->MoveTo(left_margin, top_margin * 2.5f);
    p_dc->LineTo(left_margin * 18, top_margin * 2.5f);

    p_dc->TextOut(left_margin - 25, top_margin * 4.5f, CString("3.5"));
    p_dc->MoveTo(left_margin, top_margin * 4.5f);
    p_dc->LineTo(left_margin * 18, top_margin * 4.5f);

    p_dc->TextOut(left_margin - 25, top_margin * 6.5f, CString("3.0"));
    p_dc->MoveTo(left_margin, top_margin * 6.5f);
    p_dc->LineTo(left_margin * 18, top_margin * 6.5f);

    p_dc->TextOut(left_margin - 25, top_margin * 8.5f, CString("2.5"));
    p_dc->MoveTo(left_margin, top_margin * 8.5f);
    p_dc->LineTo(left_margin * 18, top_margin * 8.5f);

    p_dc->TextOut(left_margin - 25, top_margin * 10.5f, CString("2.0"));
    p_dc->MoveTo(left_margin, top_margin * 10.5f);
    p_dc->LineTo(left_margin * 18, top_margin * 10.5f);

    p_dc->TextOut(left_margin - 25, top_margin * 12.5f, CString("1.5"));
    p_dc->MoveTo(left_margin, top_margin * 12.5f);
    p_dc->LineTo(left_margin * 18, top_margin * 12.5f);

    p_dc->TextOut(left_margin - 25, top_margin * 14.5f, CString("1.0"));
    p_dc->MoveTo(left_margin, top_margin * 14.5f);
    p_dc->LineTo(left_margin * 18, top_margin * 14.5f);

    p_dc->TextOut(left_margin - 25, top_margin * 16.5f, CString("0.5"));
    p_dc->MoveTo(left_margin, top_margin * 16.5f);
    p_dc->LineTo(left_margin * 18, top_margin * 16.5f);

    p_dc->TextOut(left_margin - 25, top_margin * 18, CString("0.0"));
    p_dc->MoveTo(y_axis_tip);
    p_dc->LineTo(chart_tip);
    p_dc->MoveTo(chart_tip);
    p_dc->LineTo(x_axis_tip);


    p_dc->TextOut(left_margin * 7, top_margin, CString("Sort Comparision"));

    old_font_ = p_dc->SelectObject(new_font_.get());
    p_dc->TextOut(left_margin - 25, top_margin, CString("y(t)"));

    const auto bubble_time = sorting_times_[bubbleSortId].count() / 10e7;
    const auto insertion_time = sorting_times_[insertionSortId].count() / 10e7;
    const auto selection_time = sorting_times_[selectionSortId].count() / 10e7;
    const auto half_time = sorting_times_[halfSortId].count() / 10e7;

    auto bubble_chart = CRect(left_margin + client_rect_->Width() / 20,
        top_margin * 18 - bubble_time,
        left_margin + 3 * (client_rect_->Width() / 20),
        top_margin * 18);

    auto insertion_chart = CRect(left_margin + 4 * client_rect_->Width() / 20,
        top_margin * 18 - insertion_time,
        left_margin + 6 * (client_rect_->Width() / 20),
        top_margin * 18);

    auto selection_chart = CRect(left_margin + 7 * client_rect_->Width() / 20,
        top_margin * 18 - selection_time,
        left_margin + 9 * (client_rect_->Width() / 20),
        top_margin * 18);

    auto half_chart = CRect(left_margin + 10 * client_rect_->Width() / 20,
        top_margin * 18 - half_time,
        left_margin + 12 * (client_rect_->Width() / 20),
        top_margin * 18);

    auto bubble_chart_ccrec = std::make_unique<CColorRectange>(bubble_chart, 1, BLACK, RED);
    auto insertion_chart_ccrec = std::make_unique<CColorRectange>(insertion_chart, 1, BLACK, GREEN);
    auto selection_chart_ccrec = std::make_unique<CColorRectange>(selection_chart, 1, BLACK, BLUE);
    auto half_chart_ccrec = std::make_unique<CColorRectange>(half_chart, 1, BLACK, ORANGE);

    bubble_chart_ccrec->paintRect(p_dc);
    insertion_chart_ccrec->paintRect(p_dc);
    selection_chart_ccrec->paintRect(p_dc);
    half_chart_ccrec->paintRect(p_dc);

    old_font_ = p_dc->SelectObject(old_font_);

    p_dc->TextOut(left_margin + client_rect_->Width() / 20,
        top_margin * 16 - bubble_time,
        CString("Bubble Sort"));
    p_dc->TextOut(left_margin + 4 * client_rect_->Width() / 20,
        top_margin * 16 - insertion_time,
        CString("Insert. Sort"));
    p_dc->TextOut(left_margin + 7 * client_rect_->Width() / 20,
        top_margin * 16 - selection_time,
        CString("Select. Sort"));
    p_dc->TextOut(left_margin + 10 * client_rect_->Width() / 20,
        top_margin * 16 - half_time,
        CString("Half Sort"));

    old_font_ = p_dc->SelectObject(new_font_.get());

    p_dc->TextOut(left_margin + client_rect_->Width() / 20,
        top_margin * 17 - bubble_time,
        CString(std::to_string(bubble_time / 100.f).c_str()));
    p_dc->TextOut(left_margin + 4 * client_rect_->Width() / 20,
        top_margin * 17 - insertion_time,
        CString(std::to_string(insertion_time / 100.f).c_str()));
    p_dc->TextOut(left_margin + 7 * client_rect_->Width() / 20,
        top_margin * 17 - selection_time,
        CString(std::to_string(selection_time / 100.f).c_str()));
    p_dc->TextOut(left_margin + 10 * client_rect_->Width() / 20,
        top_margin * 17 - half_time,
        CString(std::to_string(half_time / 100.f).c_str()));
}