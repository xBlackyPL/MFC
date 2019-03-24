#pragma once

#include <atltypes.h>
#include <memory>

#define BLACK RGB(0, 0, 0)
#define WHITE RGB(255, 255, 255)
#define RED RGB(255, 0, 0)
#define GREEN RGB(0, 255, 0)
#define BLUE RGB(0, 0, 255)
#define ORANGE RGB(255, 165, 0)
#define CYAN RGB(0, 255, 255)
#define GREENYELLOW RGB(173, 255, 47)

class CColorRectange : public CRect
{
public:
    using CPenPtr = std::unique_ptr<CPen>;
    using CBrushPtr = std::unique_ptr<CBrush>;

    CColorRectange(CRect* p_rect = nullptr, int pen_width = 0, COLORREF pen_color = BLACK, COLORREF bkg_color = BLACK);
    CColorRectange(const CRect&, int pen_width = 0, COLORREF pen_color = BLACK, COLORREF bkg_color = BLACK);
    CColorRectange(const CPoint&, const CPoint&, int pen_width = 0, COLORREF pen_color = BLACK,
        COLORREF bkg_color = BLACK);
    CColorRectange(const CPoint&, const CSize&, int pen_width = 0, COLORREF pen_color = BLACK, COLORREF bkg_color = BLACK);

    CColorRectange::~CColorRectange() = default;

    void paintRect(CDC* p_dc);
    void create_attr(int pen_width = 0, COLORREF pen_color = BLACK, COLORREF bkg_color = BLACK);

private:
    CPenPtr old_pen_;
    CBrushPtr old_brush_;

    void initAttr()
    {
        old_pen_ = std::unique_ptr<CPen>();
        old_brush_ = std::unique_ptr<CBrush>();
    }

    void newAttr(int pen_width, COLORREF pen_color, COLORREF bkg_color);
};
