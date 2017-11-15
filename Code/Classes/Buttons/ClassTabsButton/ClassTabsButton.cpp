#include "stdafx.h"
#include "ClassTabsButton.h"

namespace explorer {

	TabsButton::TabsButton()
	{
		registerHendler(METHOD(&TabsButton::paintHandler));
	}

	void TabsButton::paintHandler(Gdiplus::Graphics& graphics)
	{
		Gdiplus::SolidBrush brush((isHover() && !isLocked()) ? (MAIN_WINDOW_COLOR_HEADER_BUTTON_SELECTED) : (MAIN_WINDOW_COLOR_HEADER));
		Gdiplus::SolidBrush textBrush(Gdiplus::Color(254, 200, 200, 200));
		graphics.FillRectangle(&brush, -1, -1, getWidth() + 1, getHieght() + 1);

		Gdiplus::StringFormat stringFormat(Gdiplus::StringFormatFlags::StringFormatFlagsNoClip);
		stringFormat.SetLineAlignment(Gdiplus::StringAlignmentCenter);
		stringFormat.SetAlignment(Gdiplus::StringAlignmentCenter);

		Gdiplus::Font font(&Gdiplus::FontFamily(L"Arial"), 8);
		Gdiplus::RectF rect(0,0,50, getHieght());

		graphics.DrawString(L"¬кладки", -1, &font, rect, &stringFormat, &textBrush);

	}

}