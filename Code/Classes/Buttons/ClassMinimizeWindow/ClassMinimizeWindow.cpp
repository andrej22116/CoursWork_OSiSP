#include "stdafx.h"
#include "ClassMinimizeWindow.h"

namespace explorer {

	ButtonMinimize::ButtonMinimize()
	{
		m_registerHendler(METHOD(&ButtonMinimize::paintHandler));
		m_registerHendler(METHOD(&ButtonMinimize::resizeParentHandler));

		m_registerHendler(METHOD(&ButtonMinimize::minimizeHandler));
		setMoveWhenParentResizeing(true);

		setDoubleBuffered(true);
	}

	void ButtonMinimize::paintHandler(Gdiplus::Graphics& graphics)
	{
		Gdiplus::Pen pen(Gdiplus::Color::White, 1.6);
		Gdiplus::SolidBrush brush((isHover()) ? 
			(MAIN_WINDOW_COLOR_HEADER_BUTTON_SELECTED) :
			(MAIN_WINDOW_COLOR_HEADER));
		graphics.FillRectangle(&brush, -1, -1, getWidth() + 1, getHieght() + 1);

		graphics.DrawRectangle(&pen, 2, getHieght()-4, getWidth()-5, 1);
	}

	void ButtonMinimize::minimizeHandler(const MouseEventClick& mouseEventClick)
	{
		getParent()->minimizeWindow(true);
	}

	void ButtonMinimize::resizeParentHandler(const ParentEvent& parentEvent)
	{
	}

}