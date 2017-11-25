#include "stdafx.h"
#include "ClassButtonCloseWindow.h"

namespace explorer {

	ButtonClose::ButtonClose()
	{
		registerHendler(METHOD(&ButtonClose::mouseClickCloseHandler));
		registerHendler(METHOD(&ButtonClose::paintHandler));
		registerHendler(METHOD(&ButtonClose::resizeParentHandler));

		setMoveWhenParentResizeing(true);
	}


	void ButtonClose::paintHandler(Gdiplus::Graphics& graphics)
	{		
		graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);

		Gdiplus::Pen pen(Gdiplus::Color::White, 1);
		Gdiplus::SolidBrush brush((isHover()) ? (Gdiplus::Color(254, 255, 0, 55)) : (MAIN_WINDOW_COLOR_HEADER));
		graphics.FillRectangle(&brush, -1, -1, getWidth()+1, getHieght()+1);

		int width = getWidth();
		int height = getHieght();

		int verticalOffset = 5;
		int horizontalOffset = (width - (height - (verticalOffset * 2))) / 2;

		Gdiplus::Point	pos_1(horizontalOffset, verticalOffset),
						pos_2(width - horizontalOffset - 1, height - verticalOffset - 1);
		Gdiplus::Point	pos_3(width - horizontalOffset - 1, verticalOffset),
						pos_4(horizontalOffset, height - verticalOffset - 1);

		graphics.DrawLine(&pen, pos_2, pos_1);
		graphics.DrawLine(&pen, pos_3, pos_4);
	}

	void ButtonClose::mouseClickCloseHandler(const MouseEventClick& mouseEventClick)
	{
		getParent()->destroy();
	}

	void ButtonClose::resizeParentHandler(const ParentEvent& parentEvent)
	{
	}
}