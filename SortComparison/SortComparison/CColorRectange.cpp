#include "stdafx.h"
#include "CColorRectange.h"

CColorRectange::CColorRectange(CRect* pRect, int penWidth, COLORREF penColor, COLORREF bkgColor)
{
    CreateAttr(penWidth, penColor, bkgColor);
}

CColorRectange::CColorRectange(const CRect&, int penWidth, COLORREF penColor, COLORREF bkgColor)
{
    CreateAttr(penWidth, penColor, bkgColor);
}

CColorRectange::CColorRectange(const CPoint&, const CPoint&, int penWidth, COLORREF penColor, COLORREF bkgColor)
{
    CreateAttr(penWidth, penColor, bkgColor);
}

CColorRectange::CColorRectange(const CPoint&, const CSize&, int penWidth, COLORREF penColor, COLORREF bkgColor)
{
    CreateAttr(penWidth, penColor, bkgColor);
}

CColorRectange::~CColorRectange()
{
}

void CColorRectange::PaintRect(CDC* pDC)
{
}

void CColorRectange::CreateAttr(int penWidth, COLORREF penColor, COLORREF bkgColor)
{
    initAttr();
    newAttr(penWidth, penColor, bkgColor);
}

void CColorRectange::initAttr()
{
}

void CColorRectange::newAttr(int penWidth, COLORREF penColor, COLORREF bkgColor)
{
    m_pPen = std::make_unique<CPen>(PS_SOLID, penWidth, penColor);
    m_pBrush = std::make_unique<CBrush>(bkgColor);
}
