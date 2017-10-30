#include "stdafx.h"
#include "ClassOptionsWindow.h"

namespace explorer {

	ButtonOptions::ButtonOptions(ListOfFiles* listOfFiles)
	{
		_listOfFiles = listOfFiles;

		m_registerHendler(METHOD(&ButtonUp::mouseClickOptionsHandler));
		m_registerHendler(METHOD(&ButtonUp::paintHandler));

		setDoubleBuffered(true);
	}

	void ButtonOptions::paintHandler(Gdiplus::Graphics& graphics)
	{
		//graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
		Gdiplus::Pen pen(Gdiplus::Color::White, 1.55);
		Gdiplus::SolidBrush brush((isHover() && !isLocked()) ? (MAIN_WINDOW_COLOR_HEADER_BUTTON_SELECTED) : (MAIN_WINDOW_COLOR_HEADER));
		graphics.FillRectangle(&brush, -1, -1, getWidth() + 1, getHieght() + 1);
	}

	void ButtonOptions::mouseClickOptionsHandler(const MouseEventClick& mouseEventClick)
	{
	}

}