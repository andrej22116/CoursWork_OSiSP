#include "stdafx.h"
#include "ClassNewTabButton.h"

namespace explorer {

	NewTubButton::NewTubButton()
	{
		registerHendler(METHOD(&NewTubButton::paintHandler));
	}

	void NewTubButton::paintHandler(Gdiplus::Graphics& graphics)
	{
		Gdiplus::Pen pen(Gdiplus::Color(254, 200, 200, 200), 1);
		Gdiplus::SolidBrush brush((isHover() && !isLocked()) ? (MAIN_WINDOW_COLOR_HEADER_BUTTON_SELECTED) : (MAIN_WINDOW_COLOR_HEADER));
		graphics.FillRectangle(&brush, -1, -1, getWidth() + 1, getHieght() + 1);

		int width = getWidth();
		int height = getHieght();

		graphics.DrawLine(&pen,
			Gdiplus::PointF(float(width - 1) / 2.0, 5.0),
			Gdiplus::PointF(float(width - 1) / 2.0, height - 6.5)
		);
		graphics.DrawLine(&pen,
			Gdiplus::PointF(5.0, float(height - 1) / 2.0),
			Gdiplus::PointF(width - 6.5, float(height - 1) / 2.0)
		);
	}

}