#include "stdafx.h"
#include "ClassButtonCloseWindow.h"

namespace explorer {

	ButtonClose::ButtonClose()
	{
		m_registerHendler(METHOD(&ButtonClose::mouseClickCloseHandler));
		m_registerHendler(METHOD(&ButtonClose::paintHandler));
		m_registerHendler(METHOD(&ButtonClose::resizeParentHandler));

		setMoveWhenParentResizeing(true);
	}


	void ButtonClose::paintHandler(Gdiplus::Graphics& graphics)
	{		
		graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);

		Gdiplus::Pen pen(Gdiplus::Color::White, 1.55);
		Gdiplus::SolidBrush brush((isHover()) ? (Gdiplus::Color::Red) : (MAIN_WINDOW_COLOR_HEADER));
		graphics.FillRectangle(&brush, -1, -1, getWidth()+1, getHieght()+1);

		graphics.SetClip(&_region);
		Gdiplus::Point pos_1(2, 2), pos_2(getWidth()-3, getHieght()-3);
		Gdiplus::Point pos_3(getWidth() - 3, 2), pos_4(2, getHieght()-3);

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
	}
}