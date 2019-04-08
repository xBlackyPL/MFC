#pragma once


class CSDIBallsDoc : public CDocument
{
protected:
	CSDIBallsDoc() noexcept;
	DECLARE_DYNCREATE(CSDIBallsDoc)
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	void SetSearchContent(const CString& value);
#endif 

public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& archive);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	virtual ~CSDIBallsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& device_context) const;
#endif
};