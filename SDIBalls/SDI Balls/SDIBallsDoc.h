#pragma once


class SDIBallsDoc : public CDocument
{
protected:
	SDIBallsDoc() noexcept;
DECLARE_DYNCREATE(SDIBallsDoc)
DECLARE_MESSAGE_MAP()
#ifdef SHARED_HANDLERS
	void SetSearchContent(const CString& value);
#endif

public:
	BOOL OnNewDocument() override;
	void Serialize(CArchive& ar) override;
	virtual ~SDIBallsDoc();

#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif

#ifdef _DEBUG
	void AssertValid() const override;
	void Dump(CDumpContext& dc) const override;
#endif
};
