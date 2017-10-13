#include "stdafx.h"
#include "ClassMinimizeWindow.h"

namespace explorer {

	ButtonMinimize::ButtonMinimize()
	{
		m_registerHendler(METHOD(&ButtonMinimize::paintHandler));
		m_registerHendler(METHOD(&ButtonMinimize::hoverHandler));
		m_registerHendler(METHOD(&ButtonMinimize::resizeParentHandler));

		m_registerHendler(METHOD(&ButtonMinimize::minimizeHandler));

		_hover = false;
	}

	void ButtonMinimize::createWindow()
	{
		getHoverMessages(true);
	}
	void ButtonMinimize::paintHandler(Gdiplus::Graphics& graphics)
	{
		Gdiplus::Pen pen(Gdiplus::Color::White, 1.6);
		Gdiplus::SolidBrush brush((_hover) ? (Gdiplus::Color(96, 96, 96)) : (Gdiplus::Color(64, 64, 64)));
		graphics.FillRectangle(&brush, -1, -1, getWidth() + 1, getHieght() + 1);

		graphics.DrawRectangle(&pen, 2, getHieght()-3, getWidth()-5, 1);
	}
	void ButtonMinimize::hoverHandler(HoverStatus status)
	{
		_hover = status;
		redrawWindow(false);
	}

	void ButtonMinimize::minimizeHandler(const MouseEventClick& mouseEventClick)
	{
		getParent()->minimizeWindow(true);
	}

	void ButtonMinimize::resizeParentHandler(const ParentEvent& parentEvent)
	{
		if (parentEvent.Code == PARENT_RESIZE) {
			resizeWindow(parentEvent.Width - 48, 1, 15, 15, true);
		}
	}

}