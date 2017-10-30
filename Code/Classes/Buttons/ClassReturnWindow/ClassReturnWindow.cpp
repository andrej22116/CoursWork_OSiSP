#include "stdafx.h"
#include "ClassReturnWindow.h"

namespace explorer {
	std::stack<std::wstring> ButtonReturn::_forwardStack = std::stack<std::wstring>();
	std::stack<std::wstring> ButtonReturn::_backwardStack = std::stack<std::wstring>();
	std::vector<ButtonReturn*> ButtonReturn::buttons = std::vector<ButtonReturn*>(BUTTON_RETURN_TYPES_COUNT);

	ButtonReturn::ButtonReturn(ListOfFiles* listOfFiles, ButtonReturnType type)
	{
		_image = Gdiplus::Image::FromFile(L".\\Icons\\Pointer.png", true);
		_listOfFiles = listOfFiles;
		_type = type;

		buttons[type] = this;

		if (type == BUTTON_RETURN_BACKWARD) {
			m_registerHendler(METHOD(&ButtonReturn::mouseClickHandler_backward));
			m_registerHendler(METHOD(&ButtonReturn::paintHandler_backward));

		}
		else if (type == BUTTON_RETURN_FORWARD) {
			m_registerHendler(METHOD(&ButtonReturn::mouseClickHandler_forward));
			m_registerHendler(METHOD(&ButtonReturn::paintHandler_forward));
			_image->RotateFlip(Gdiplus::Rotate180FlipY);
		}
		else if (type == BUTTON_RETURN_UP) {
			m_registerHendler(METHOD(&ButtonReturn::mouseClickHandler_up));
			m_registerHendler(METHOD(&ButtonReturn::paintHandler_up));
			_image->RotateFlip(Gdiplus::Rotate90FlipX);
		}

		setDoubleBuffered(true);
	}
	ButtonReturn::~ButtonReturn()
	{
		delete _image;
	}

	void ButtonReturn::paintHandler_backward(Gdiplus::Graphics& graphics)
	{
		Gdiplus::Pen pen(Gdiplus::Color::White, 1.55);
		Gdiplus::SolidBrush brush((isHover() && !isLocked()) ? (MAIN_WINDOW_COLOR_HEADER_BUTTON_SELECTED) : (MAIN_WINDOW_COLOR_HEADER));
		graphics.FillRectangle(&brush, -1, -1, getWidth() + 1, getHieght() + 1);

		graphics.DrawImage(&(*_image), 2, 2, 12, 12);
		if (this->isLocked()) {
			Gdiplus::SolidBrush lockBrush(Gdiplus::Color(192, 56, 56, 56));
			graphics.FillRectangle(&lockBrush, -1, -1, getWidth() + 1, getHieght() + 1);
		}
	}
	void ButtonReturn::paintHandler_forward(Gdiplus::Graphics& graphics)
	{
		Gdiplus::Pen pen(Gdiplus::Color::White, 1.55);
		Gdiplus::SolidBrush brush((isHover() && !isLocked()) ? (MAIN_WINDOW_COLOR_HEADER_BUTTON_SELECTED) : (MAIN_WINDOW_COLOR_HEADER));
		graphics.FillRectangle(&brush, -1, -1, getWidth() + 1, getHieght() + 1);

		//graphics.TranslateTransform(15, 15);
		//graphics.RotateTransform(180);
		//graphics.TranslateTransform(0, 0);
		graphics.DrawImage(&(*_image), 2, 2, 12, 12);
		if (this->isLocked()) {
			Gdiplus::SolidBrush lockBrush(Gdiplus::Color(192, 56, 56, 56));
			graphics.FillRectangle(&lockBrush, -1, -1, getWidth() + 1, getHieght() + 1);
		}
	}
	void ButtonReturn::paintHandler_up(Gdiplus::Graphics& graphics)
	{
		Gdiplus::Pen pen(Gdiplus::Color::White, 1.55);
		Gdiplus::SolidBrush brush((isHover() && !isLocked()) ? (MAIN_WINDOW_COLOR_HEADER_BUTTON_SELECTED) : (MAIN_WINDOW_COLOR_HEADER));
		graphics.FillRectangle(&brush, -1, -1, getWidth() + 1, getHieght() + 1);

		//graphics.TranslateTransform(15, 0);
		//graphics.RotateTransform(90);
		//graphics.TranslateTransform(0, 0);
		graphics.DrawImage(&(*_image), 2, 2, 12, 12);
		if (this->isLocked()) {
			Gdiplus::SolidBrush lockBrush(Gdiplus::Color(192, 56, 56, 56));
			graphics.FillRectangle(&lockBrush, -1, -1, getWidth() + 1, getHieght() + 1);
		}
	}

	void ButtonReturn::mouseClickHandler_backward(const MouseEventClick& mouseEventClick)
	{

	}
	void ButtonReturn::mouseClickHandler_forward(const MouseEventClick& mouseEventClick)
	{

	}
	void ButtonReturn::mouseClickHandler_up(const MouseEventClick& mouseEventClick)
	{
		if (mouseEventClick.Click == MOUSE_CLICK_ONE
			&& mouseEventClick.Button == MOUSE_LEFT
			&& mouseEventClick.Status == KEY_PRESSED) {
			std::wstring currentDirection = _listOfFiles->getCurrentDirectory();
			if (!currentDirection.empty()) {
				File file(currentDirection);
				std::wstring backPath = file.getPrevDirection();
				_listOfFiles->setCurrentDirectory(backPath);
				_listOfFiles->updateList();

				if (backPath.empty()) {
					setLock(true);
				}
				else {
					setLock(false);
				}
			}
		}
	}

	void ButtonReturn::nextDirrectory(std::wstring& newDirrectory)
	{

	}
}