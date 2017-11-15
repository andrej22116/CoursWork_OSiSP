#include "stdafx.h"
#include "ClassAbstractLeftWindow.h"

namespace explorer {
	LeftWindow::LeftWindow()
	{
		registerHendler(METHOD(&LeftWindow::paintHandler));
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
		graphics.Clear(Gdiplus::Color(200, 255, 255, 255));
		Gdiplus::Font fontHead(&Gdiplus::FontFamily(L"Arial"), 16);
		Gdiplus::SolidBrush brush(Gdiplus::Color(254, 0, 0, 0));
		Gdiplus::SolidBrush brushBackground(Gdiplus::Color(20, 0, 0, 0));

		graphics.FillRectangle(&brushBackground, 0, 0, getWidth(), 40);
		graphics.DrawString(getWindowName().c_str(), -1, &fontHead, Gdiplus::PointF(10, 10), &brush);
	}
	void LeftWindow::timerHandler(const int timer_ID)
	{
	}

}