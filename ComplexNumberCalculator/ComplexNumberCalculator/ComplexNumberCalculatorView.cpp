#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "ComplexNumberCalculator.h"
#endif

#include "ComplexNumberCalculatorDoc.h"
#include "ComplexNumberCalculatorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CComplexNumberCalculatorView, CView)

BEGIN_MESSAGE_MAP(CComplexNumberCalculatorView, CView)
END_MESSAGE_MAP()

CComplexNumberCalculatorView::CComplexNumberCalculatorView() noexcept
{
}

CComplexNumberCalculatorView::~CComplexNumberCalculatorView() = default;

BOOL CComplexNumberCalculatorView::PreCreateWindow(CREATESTRUCT& creation_structure)
{
	return CView::PreCreateWindow(creation_structure);
}

void CComplexNumberCalculatorView::OnDraw(CDC* device_context)
{
	const auto doc = GetDocument();
	ASSERT_VALID(doc);
	if (!doc)
	{
	}
}

#ifdef _DEBUG
void CComplexNumberCalculatorView::AssertValid() const
{
	CView::AssertValid();
}

void CComplexNumberCalculatorView::Dump(CDumpContext& device_context) const
{
	CView::Dump(device_context);
}

CComplexNumberCalculatorDoc* CComplexNumberCalculatorView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CComplexNumberCalculatorDoc)));
	return static_cast<CComplexNumberCalculatorDoc*>(m_pDocument);
}
#endif
