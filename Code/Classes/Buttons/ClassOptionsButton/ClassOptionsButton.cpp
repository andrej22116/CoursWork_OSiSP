#include "stdafx.h"
#include "ClassOptionsButton.h"
#include "..\..\ClassMainWindow\ClassMainWindow.h"

namespace explorer {

	ButtonOptions::ButtonOptions(ListOfFiles* listOfFiles)
	{
		_listOfFiles = listOfFiles;
		_image = Gdiplus::Image::FromFile(L".\\Icons\\Pinion.png", true);

		m_registerHendler(METHOD(&ButtonOptions::mouseClickOptionsHandler));
		m_registerHendler(METHOD(&ButtonOptions::paintHandler));
	}

	ButtonOptions::~ButtonOptions()
	{
		delete _image;
	}

	void ButtonOptions::paintHandler(Gdiplus::Graphics& graphics)
	{
		//graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
		Gdiplus::Pen pen(Gdiplus::Color::White, 1);
		Gdiplus::SolidBrush brush((isHover() && !isLocked()) ? (MAIN_WINDOW_COLOR_HEADER_BUTTON_SELECTED) : (MAIN_WINDOW_COLOR_HEADER));
		graphics.FillRectangle(&brush, -1, -1, getWidth() + 1, getHieght() + 1);

		graphics.SetInterpolationMode(Gdiplus::InterpolationModeBilinear);
		graphics.DrawImage(_image, 3, 3, getWidth() - 8, getHieght() - 8);

	}

	void ButtonOptions::mouseClickOptionsHandler(const MouseEventClick& mouseEventClick)
	{
		if (mouseEventClick.Click == MOUSE_CLICK_ONE
			&& mouseEventClick.Button == MOUSE_LEFT
			&& mouseEventClick.Status == KEY_PRESSED) {
			((MainWindow*)getParent())->showWindowOptions(true);
		}
	}

}