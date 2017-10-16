#include "stdafx.h"
#include "ClassButtonCloseWindow.h"

namespace explorer {

	ButtonClose::ButtonClose()
	{
		m_registerHendler(METHOD(&ButtonClose::mouseClickCloseHandler));
		m_registerHendler(METHOD(&ButtonClose::paintHandler));
		m_registerHendler(METHOD(&ButtonClose::resizeParentHandler));
	}


	void ButtonClose::paintHandler(Gdiplus::Graphics& graphics)
	{		
		graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);

		Gdiplus::Pen pen(Gdiplus::Color::White, 1.55);
		Gdiplus::SolidBrush brush((isHover()) ? (Gdiplus::Color::Red) : (Gdiplus::Color(64,64,64)));
		graphics.FillRectangle(&brush, -1, -1, getWidth()+1, getHieght()+1);

		graphics.SetClip(&_region);
		Gdiplus::Point pos_1(0, 0), pos_2(getWidth(), getHieght());
		Gdiplus::Point pos_3(getWidth()-1, 0), pos_4(-1, getHieght());

		graphics.DrawLine(&pen, pos_2, pos_1);
		graphics.DrawLine(&pen, pos_3, pos_4);

		graphics.ExcludeClip(&_region);
	}

	void ButtonClose::mouseClickCloseHandler(const MouseEventClick& mouseEventClick)
	{
		m_sendMessageForParent(WM_CLOSE, 0, 0);
	}

	void ButtonClose::resizeParentHandler(const ParentEvent& parentEvent)
	{
		if (parentEvent.Code == PARENT_RESIZE) {
			resizeWindow(parentEvent.Width - 16, 1, 15, 15, true);
		}
	}
}