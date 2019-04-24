#pragma once

class CComplexNumberCalculatorView : public CView
{
protected:
	CComplexNumberCalculatorView() noexcept;
DECLARE_DYNCREATE(CComplexNumberCalculatorView)
DECLARE_MESSAGE_MAP()

public:
	CComplexNumberCalculatorDoc* GetDocument() const;

	void OnDraw(CDC* device_context) override;
	BOOL PreCreateWindow(CREATESTRUCT& creation_structure) override;
	virtual ~CComplexNumberCalculatorView();
#ifdef _DEBUG
	void AssertValid() const override;
	void Dump(CDumpContext& device_context) const override;
#endif
};

#ifndef _DEBUG
inline CComplexNumberCalculatorDoc* CComplexNumberCalculatorView::GetDocument() const
   { return reinterpret_cast<CComplexNumberCalculatorDoc*>(m_pDocument); }
#endif
