#include "stdafx.h"
#include "ClassAbstractLeftWindow.h"

namespace explorer {
	LeftWindow::LeftWindow()
	{
		registerHendler(METHOD(&LeftWindow::paintHandler));

		setResizeWhenParentResizeing(false, true);
		_show = false;
	}

	bool LeftWindow::isShow()
	{
		return _show;
	}
	void LeftWindow::show(bool show)
	{
		_show = show;
		if (_show) {
			moveWindowPos(1, MAIN_WINDOW_HEADER_HEIGHT + 1, false);
			showWindow(true);
			redrawWindow(false);
		}
		else {
			showWindow(false);
			moveWindowPos(-getWidth(), MAIN_WINDOW_HEADER_HEIGHT + 1, false);
		}
	}

	void LeftWindow::paintHandler(Gdiplus::Graphics& graphics)
	{
		//graphics.Clear(Gdiplus::Color(200, 255, 255, 255));
		graphics.Clear(Gdiplus::Color(0, 0, 0, 0));
		Gdiplus::Font fontHead(&Gdiplus::FontFamily(L"Arial"), 16);
		Gdiplus::SolidBrush stringBrush(Gdiplus::Color(254, 0, 0, 0));
		Gdiplus::SolidBrush brushBackground(Gdiplus::Color(200, 255, 255, 255));
		Gdiplus::SolidBrush brushHeadBackground(Gdiplus::Color(20, 0, 0, 0));

		int width = getWidth();
		int gradientWidth = 3;

		Gdiplus::LinearGradientBrush gradientBorderBrush(
			Gdiplus::Point(width - gradientWidth - 1, 0),
			Gdiplus::Point(width, 0),
			Gdiplus::Color(200, 255, 255, 255),
			LISTBOX_COLOR_BACKGROUND
		);

		graphics.FillRectangle(&brushBackground, 0, 0, width - gradientWidth, getHieght());
		graphics.FillRectangle(&gradientBorderBrush, width - gradientWidth, 0, gradientWidth, getHieght());

		graphics.FillRectangle(&brushHeadBackground, 0, 0, getWidth(), headHeight);
		graphics.DrawString(getWindowName().c_str(), -1, &fontHead, Gdiplus::PointF(10, 10), &stringBrush);
	}
	void LeftWindow::timerHandler(const int timer_ID)
	{
	}

}