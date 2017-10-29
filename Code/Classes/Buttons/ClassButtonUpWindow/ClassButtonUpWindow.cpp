#include "stdafx.h"
#include "ClassButtonUpWindow.h"

namespace explorer {
	ButtonUp::ButtonUp()
	{

	}

	ButtonUp::ButtonUp(ListOfFiles* listOfFiles)
	{
		std::wstring filepath;
#ifdef _DEBUG
		filepath = L".\\CoursWork_OSiSP\\Icons\\Up.png";
#else
		filepath = L".\\Icons\\Up.png";
#endif
		_image = Gdiplus::Image::FromFile(filepath.c_str(), true);
		_listOfFiles = listOfFiles;

		m_registerHendler(METHOD(&ButtonUp::mouseClickUpHandler));
		m_registerHendler(METHOD(&ButtonUp::paintHandler));

		setDoubleBuffered(true);
	}
	ButtonUp::~ButtonUp()
	{
		delete _image;
	}

	void ButtonUp::paintHandler(Gdiplus::Graphics& graphics)
	{
		graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);

		Gdiplus::Pen pen(Gdiplus::Color::White, 1.55);
		Gdiplus::SolidBrush brush((isHover()) ? (MAIN_WINDOW_COLOR_HEADER_BUTTON_SELECTED) : (MAIN_WINDOW_COLOR_HEADER));
		graphics.FillRectangle(&brush, -1, -1, getWidth() + 1, getHieght() + 1);

		graphics.DrawImage(_image, 0, 0);
	}

	void ButtonUp::mouseClickUpHandler(const MouseEventClick& mouseEventClick)
	{

	}

}