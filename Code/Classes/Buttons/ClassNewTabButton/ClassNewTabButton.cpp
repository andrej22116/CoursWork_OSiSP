#include "stdafx.h"
#include "ClassNewTabButton.h"

namespace explorer {

	NewTubButton::NewTubButton()
	{
		registerHendler(METHOD(&NewTubButton::paintHandler));
	}

	void NewTubButton::paintHandler(Gdiplus::Graphics& graphics)
	{
		Gdiplus::SolidBrush brushHeadBackground(Gdiplus::Color(20, 0, 0, 0));
		Gdiplus::Pen pen(Gdiplus::Color(254, 0, 0, 0), 1);

		graphics.Clear(Gdiplus::Color(200, 255, 255, 255));
		
		int width = getWidth();
		int height = getHieght();

		graphics.FillRectangle(&brushHeadBackground, 0, 0, width, height);
		if (!isLocked() && isHover()) {
			graphics.FillRectangle(&brushHeadBackground, 0, 0, width, height);
		}

		graphics.DrawLine(&pen,
			Gdiplus::PointF(float(width - 1) / 2.0, 5.0),
			Gdiplus::PointF(float(width - 1) / 2.0, height - 6.5)
		);
		graphics.DrawLine(&pen,
			Gdiplus::PointF(5.0, float(height - 1) / 2.0),
			Gdiplus::PointF(width - 6.0, float(height - 1) / 2.0)
		);
	}

}