#include "stdafx.h"
#include "ClassOptionsWindow.h"

namespace explorer {

	ButtonOptions::ButtonOptions(ListOfFiles* listOfFiles)
	{
		_listOfFiles = listOfFiles;

		m_registerHendler(METHOD(&ButtonOptions::mouseClickOptionsHandler));
		m_registerHendler(METHOD(&ButtonOptions::paintHandler));
	}

	void ButtonOptions::paintHandler(Gdiplus::Graphics& graphics)
	{
		//graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
		Gdiplus::Pen pen(Gdiplus::Color::Black, 1);
		Gdiplus::SolidBrush brush((isHover() && !isLocked()) ? (MAIN_WINDOW_COLOR_HEADER_BUTTON_SELECTED) : (MAIN_WINDOW_COLOR_HEADER));
		graphics.FillRectangle(&brush, -1, -1, getWidth() + 1, getHieght() + 1);

		graphics.DrawLine(&pen, 2, 3, getWidth() - 4, 3);
		graphics.DrawLine(&pen, 2, 7, getWidth() - 4, 7);
		graphics.DrawLine(&pen, 2, 11, getWidth() - 4, 11);
	}

	void ButtonOptions::mouseClickOptionsHandler(const MouseEventClick& mouseEventClick)
	{
	}

}