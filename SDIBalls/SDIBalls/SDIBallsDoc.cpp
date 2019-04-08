#include "stdafx.h"
#include "SDIBallsDoc.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CSDIBallsDoc, CDocument)
BEGIN_MESSAGE_MAP(CSDIBallsDoc, CDocument)
END_MESSAGE_MAP()

CSDIBallsDoc::CSDIBallsDoc() noexcept
{
}

CSDIBallsDoc::~CSDIBallsDoc() = default;

BOOL CSDIBallsDoc::OnNewDocument()
{
	return CDocument::OnNewDocument();
}

void CSDIBallsDoc::Serialize(CArchive& archive)
{
}

#ifdef _DEBUG
void CSDIBallsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSDIBallsDoc::Dump(CDumpContext& device_context) const
{
	CDocument::Dump(device_context);
}
#endif
