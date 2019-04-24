#pragma once

class CComplexNumberCalculatorDoc : public CDocument
{
protected:
	CComplexNumberCalculatorDoc() noexcept;
DECLARE_DYNCREATE(CComplexNumberCalculatorDoc)
DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	void SetSearchContent(const CString& value);
#endif

public:
	BOOL OnNewDocument() override;
	void Serialize(CArchive& ar) override;
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif
	virtual ~CComplexNumberCalculatorDoc();
#ifdef _DEBUG
	void AssertValid() const override;
	void Dump(CDumpContext& device_context) const override;
#endif
};
