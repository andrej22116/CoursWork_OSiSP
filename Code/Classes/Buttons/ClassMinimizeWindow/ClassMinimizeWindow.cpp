#include "stdafx.h"
#include "ClassMinimizeWindow.h"

namespace explorer {

	ButtonMinimize::ButtonMinimize()
	{
		m_registerHendler(METHOD(&ButtonMinimize::paintHandler));
		m_registerHendler(METHOD(&ButtonMinimize::resizeParentHandler));

		m_registerHendler(METHOD(&ButtonMinimize::minimizeHandler));
		setMoveWhenParentResizeing(true);
	}

	void ButtonMinimize::paintHandler(Gdiplus::Graphics& graphics)
	{
		Gdiplus::Pen pen(Gdiplus::Color(254, 200, 200, 200), 1);
		Gdiplus::SolidBrush brush((isHover()) ? 
			(MAIN_WINDOW_COLOR_HEADER_BUTTON_SELECTED) :
			(MAIN_WINDOW_COLOR_HEADER));
		graphics.FillRectangle(&brush, -1, -1, getWidth() + 1, getHieght() + 1);


		int width = getWidth();
		int height = getHieght();

		int verticalOffset = 5;
		int horizontalOffset = (width - (height - (verticalOffset * 2))) / 2;
		graphics.DrawLine(&pen, horizontalOffset, height / 2, width - horizontalOffset - 1, height / 2);
	}

	void ButtonMinimize::minimizeHandler(const MouseEventClick& mouseEventClick)
	{
		getParent()->minimizeWindow(true);
	}

	void ButtonMinimize::resizeParentHandler(const ParentEvent& parentEvent)
	{
	}

}