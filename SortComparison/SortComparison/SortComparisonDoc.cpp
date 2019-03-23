#include "stdafx.h"

#ifndef SHARED_HANDLERS
#include "SortComparison.h"
#endif

#include "SortComparisonDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CSortComparisonDoc, CDocument)

BEGIN_MESSAGE_MAP(CSortComparisonDoc, CDocument)
END_MESSAGE_MAP()


// CSortComparisonDoc construction/destruction

CSortComparisonDoc::CSortComparisonDoc() noexcept
{
    // TODO: add one-time construction code here

}

CSortComparisonDoc::~CSortComparisonDoc()
{
}

BOOL CSortComparisonDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: add reinitialization code here
    // (SDI documents will reuse this document)

    return TRUE;
}




// CSortComparisonDoc serialization

void CSortComparisonDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // TODO: add storing code here
    }
    else
    {
        // TODO: add loading code here
    }
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CSortComparisonDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
    // Modify this code to draw the document's data
    dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

    CString strText = _T("TODO: implement thumbnail drawing here");
    LOGFONT lf;

    CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
    pDefaultGUIFont->GetLogFont(&lf);
    lf.lfHeight = 36;

    CFont fontDraw;
    fontDraw.CreateFontIndirect(&lf);

    CFont* pOldFont = dc.SelectObject(&fontDraw);
    dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
    dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CSortComparisonDoc::InitializeSearchContent()
{
    CString strSearchContent;
    // Set search contents from document's data.
    // The content parts should be separated by ";"

    // For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
    SetSearchContent(strSearchContent);
}

void CSortComparisonDoc::SetSearchContent(const CString& value)
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

#endif // SHARED_HANDLERS

// CSortComparisonDoc diagnostics

#ifdef _DEBUG
void CSortComparisonDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CSortComparisonDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG


// CSortComparisonDoc commands
