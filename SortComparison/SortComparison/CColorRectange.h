#pragma once

#include <atltypes.h>
#include <memory>

#define BLACK RGB(0, 0, 0)
#define WHITE RGB(255, 255, 255)


class CColorRectange : public CRect
{
public:
    using CPenPtr = std::unique_ptr<CPen>;
    using CBrushPtr = std::unique_ptr<CBrush>;

    explicit CColorRectange(CRect* pRect = nullptr, int penWidth = 0, COLORREF penColor = BLACK, COLORREF bkgColor = BLACK);
    explicit CColorRectange(const CRect &, int penWidth = 0, COLORREF penColor = BLACK, COLORREF bkgColor = BLACK);
    CColorRectange(const CPoint &, const CPoint &, int penWidth = 0, COLORREF penColor = BLACK, COLORREF bkgColor = BLACK);
    CColorRectange(const CPoint &, const CSize &, int penWidth = 0, COLORREF penColor = BLACK, COLORREF bkgColor = BLACK);

    ~CColorRectange();

    void PaintRect(CDC* pDC);
    void CreateAttr(int penWidth = 0, COLORREF penColor = BLACK, COLORREF bkgColor = BLACK);

private:
    void initAttr();
    void newAttr(int penWidth, COLORREF penColor, COLORREF bkgColor);

    CPenPtr m_pPen;
    CBrushPtr m_pBrush;
};
