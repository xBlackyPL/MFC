#pragma once

class CSDIBallsDoc : public CDocument
{
protected:
	CSDIBallsDoc() noexcept;
DECLARE_DYNCREATE(CSDIBallsDoc)
DECLARE_MESSAGE_MAP()

public:
	BOOL OnNewDocument() override;
	void Serialize(CArchive& archive) override;
	virtual ~CSDIBallsDoc();
#ifdef _DEBUG
	void AssertValid() const override;
	void Dump(CDumpContext& device_context) const override;
#endif
};
