#include "stdafx.h"
#include "ClassButtonUpWindow.h"

namespace explorer {
	ButtonUp::ButtonUp()
	{

	}

	ButtonUp::ButtonUp(ListOfFiles* listOfFiles)
	{
		std::wstring filepath;
		filepath = L".\\Icons\\Up.png";
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
		//graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
		Gdiplus::Pen pen(Gdiplus::Color::White, 1.55);
		Gdiplus::SolidBrush brush((isHover()) ? (MAIN_WINDOW_COLOR_HEADER_BUTTON_SELECTED) : (MAIN_WINDOW_COLOR_HEADER));
		graphics.FillRectangle(&brush, -1, -1, getWidth() + 1, getHieght() + 1);

		graphics.DrawImage(_image,2, 2, 12, 12);
	}

	void ButtonUp::mouseClickUpHandler(const MouseEventClick& mouseEventClick)
	{
		if (mouseEventClick.Click == MOUSE_CLICK_ONE
			&& mouseEventClick.Button == MOUSE_LEFT
			&& mouseEventClick.Status == KEY_PRESSED) {
			File file(_listOfFiles->getCurrentDirectory());
			std::wstring backPath = file.getPrevDirection();
			_listOfFiles->setCurrentDirectory(backPath);
			_listOfFiles->updateList();
		}
	}

}