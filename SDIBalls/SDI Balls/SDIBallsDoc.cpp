#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "SDIBalls.h"
#endif

#include <propkey.h>
#include "SDIBallsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(SDIBallsDoc, CDocument)

BEGIN_MESSAGE_MAP(SDIBallsDoc, CDocument)
END_MESSAGE_MAP()


SDIBallsDoc::SDIBallsDoc() noexcept
{
}

SDIBallsDoc::~SDIBallsDoc()
= default;

BOOL SDIBallsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
	{
		return FALSE;
	}
	return TRUE;
}

void SDIBallsDoc::Serialize(CArchive& ar)
{
}

#ifdef SHARED_HANDLERS

void SDIBallsDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

void SDIBallsDoc::InitializeSearchContent()
{
	CString strSearchContent;
	SetSearchContent(strSearchContent);
}

void SDIBallsDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif

#ifdef _DEBUG
void SDIBallsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void SDIBallsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
