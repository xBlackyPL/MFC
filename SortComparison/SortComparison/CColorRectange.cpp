#include "stdafx.h"
#include "CColorRectange.h"

CColorRectange::CColorRectange(CRect* p_rect, const int pen_width, const COLORREF pen_color, const COLORREF bkg_color) :
    CRect(p_rect)
{
    create_attr(pen_width, pen_color, bkg_color);
}

CColorRectange::CColorRectange(const CRect& p_rect, const int pen_width, const COLORREF pen_color, const COLORREF bkg_color) :
    CRect(p_rect)
{
    create_attr(pen_width, pen_color, bkg_color);
}

CColorRectange::CColorRectange(const CPoint& left_top, const CPoint& right_bottom, const int pen_width,
    const COLORREF pen_color, const COLORREF bkg_color)
{
    create_attr(pen_width, pen_color, bkg_color);
}

CColorRectange::CColorRectange(const CPoint& left_top, const CSize& size, const int pen_width, const COLORREF pen_color, const COLORREF bkg_color) :
    CRect(left_top, size)
{
    create_attr(pen_width, pen_color, bkg_color);
}

void CColorRectange::paintRect(CDC* p_dc)
{
    const auto p_old_pen = p_dc->SelectObject(old_pen_.get());
    const auto p_old_brush = p_dc->SelectObject(old_brush_.get());

    p_dc->Rectangle(static_cast<CRect*>(this));

    p_dc->SelectObject(p_old_pen);
    p_dc->SelectObject(p_old_brush);
}

void CColorRectange::create_attr(const int pen_width, const COLORREF pen_color, const COLORREF bkg_color)
{
    initAttr();
    newAttr(pen_width, pen_color, bkg_color);
}

void CColorRectange::newAttr(int pen_width, COLORREF pen_color, COLORREF bkg_color)
{
    old_pen_ = std::make_unique<CPen>(PS_SOLID, pen_width, pen_color);
    old_brush_ = std::make_unique<CBrush>(bkg_color);
}
