#include "stdafx.h"
#include "ClassOptionsWindow.h"

namespace explorer {
	OptionsWindow::OptionsWindow()
	{
		m_registerHendler(METHOD(&OptionsWindow::paintHandler));

		setResizeWhenParentResizeing(false, true);
	}

	void OptionsWindow::eventCreateWindow()
	{
		_test.create(
			std::wstring(L"_test"),
			*this,
			20,
			20,
			17,
			17,
			true
		);
	}

	void OptionsWindow::paintHandler(Gdiplus::Graphics& graphics)
	{
		graphics.SetCompositingMode(Gdiplus::CompositingMode::CompositingModeSourceCopy);
		graphics.Clear(Gdiplus::Color(200, 255, 255, 255));
	}

	bool OptionsWindow::isShow()
	{
		return _show;
	}
	void OptionsWindow::show(bool show)
	{
		_show = show;
		if (_show) {
			moveWindowPos(0, MAIN_WINDOW_HEADER_HEIGHT + 1, false);
			showWindow(true);
			redrawWindow(false);
		}
		else {
			showWindow(false);
			moveWindowPos(-getWidth(), MAIN_WINDOW_HEADER_HEIGHT + 1, false);
		}
	}

	void OptionsWindow::timerHandler(const int timer_ID)
	{
	}

}