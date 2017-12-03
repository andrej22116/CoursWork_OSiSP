#include "stdafx.h"
#include "ClassTabLineButton.h"

namespace explorer {

	TabLineButton::TabLineButton()
	{
		registerHendler(METHOD(&TabLineButton::paintHandler));

		_selected = false;
	}

	void TabLineButton::eventCreateWindow()
	{
		getHoverMessages(true);

		_closeButton.create(
			*this,
			getWidth() - 33,
			int(getHieght() / 2) - 10,
			20,
			20,
			true
		);
	}

	void TabLineButton::paintHandler(Gdiplus::Graphics& graphics)
	{
		graphics.Clear(Gdiplus::Color(200, 255, 255, 255));

		Gdiplus::SolidBrush brushSelectedBackground(Gdiplus::Color(32, 0, 0, 0));
		Gdiplus::Pen pen(Gdiplus::Color(254, 0, 0, 0), 1);

		int width = getWidth();
		int height = getHieght();

		//graphics.FillRectangle(&brushHeadBackground, 0, 0, width, height);
		if (!isLocked() && _selected)
		if (!isLocked() && isHover()) {
			graphics.FillRectangle(&brushSelectedBackground, 0, 0, width, height);
		}
	}
}