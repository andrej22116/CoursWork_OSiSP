#include "stdafx.h"
#include "ClassButtonCloseTab.h"

namespace explorer {

	CloseTabButton::CloseTabButton()
	{
		registerHendler(METHOD(&CloseTabButton::paintHandler));
	}

	void CloseTabButton::paintHandler(Gdiplus::Graphics& graphics)
	{
		Gdiplus::SolidBrush brushBackground(Gdiplus::Color(20, 0, 0, 0));
		Gdiplus::Pen pen(Gdiplus::Color(254, 0, 0, 0), 1);

		graphics.Clear(Gdiplus::Color(200, 255, 255, 255));


		int width = getWidth();
		int height = getHieght();

		int verticalOffset = 5;
		int horizontalOffset = (width - (height - (verticalOffset * 2))) / 2;

		Gdiplus::Point	pos_1(horizontalOffset, verticalOffset),
			pos_2(width - horizontalOffset - 1, height - verticalOffset - 1);
		Gdiplus::Point	pos_3(width - horizontalOffset - 1, verticalOffset),
			pos_4(horizontalOffset, height - verticalOffset - 1);

		if (!isLocked() && isHover()) {
			graphics.FillRectangle(&brushBackground, 0, 0, width, height);
		}

		graphics.DrawLine(&pen, pos_2, pos_1);
		graphics.DrawLine(&pen, pos_3, pos_4);
	}

}