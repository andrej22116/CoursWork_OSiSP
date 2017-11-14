#include "stdafx.h"
#include "ClassReturnWindow.h"

namespace explorer {

	ButtonReturn::ButtonReturn(ButtonReturnType type)
	{
		_image = Gdiplus::Image::FromFile(L".\\Icons\\Pointer.png", true);
		_type = type;

		if (type == BUTTON_RETURN_BACKWARD) {
			registerHendler(METHOD(&ButtonReturn::paintHandler_backward));
			setLock(true);
		}
		else if (type == BUTTON_RETURN_FORWARD) {
			registerHendler(METHOD(&ButtonReturn::paintHandler_forward));
			_image->RotateFlip(Gdiplus::Rotate180FlipY);
			setLock(true);
		}
		else if (type == BUTTON_RETURN_UP) {
			registerHendler(METHOD(&ButtonReturn::paintHandler_up));
			_image->RotateFlip(Gdiplus::Rotate90FlipX);
		}
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

		graphics.DrawImage(_image, 4, 4, getWidth() - 8, getHieght() - 8);
		if (this->isLocked()) {
			Gdiplus::SolidBrush lockBrush(MAIN_WINDOW_COLOR_HEADER_BUTTON_LOCK);
			graphics.FillRectangle(&lockBrush, -1, -1, getWidth() + 1, getHieght() + 1);
		}
	}
	void ButtonReturn::paintHandler_forward(Gdiplus::Graphics& graphics)
	{
		Gdiplus::Pen pen(Gdiplus::Color::White, 1.55);
		Gdiplus::SolidBrush brush((isHover() && !isLocked()) ? (MAIN_WINDOW_COLOR_HEADER_BUTTON_SELECTED) : (MAIN_WINDOW_COLOR_HEADER));
		graphics.FillRectangle(&brush, -1, -1, getWidth() + 1, getHieght() + 1);

		graphics.DrawImage(_image, 4, 4, getWidth() - 8, getHieght() - 8);
		if (this->isLocked()) {
			Gdiplus::SolidBrush lockBrush(MAIN_WINDOW_COLOR_HEADER_BUTTON_LOCK);
			graphics.FillRectangle(&lockBrush, -1, -1, getWidth() + 1, getHieght() + 1);
		}
	}
	void ButtonReturn::paintHandler_up(Gdiplus::Graphics& graphics)
	{
		Gdiplus::Pen pen(Gdiplus::Color::White, 1.55);
		Gdiplus::SolidBrush brush((isHover() && !isLocked()) ? (MAIN_WINDOW_COLOR_HEADER_BUTTON_SELECTED) : (MAIN_WINDOW_COLOR_HEADER));
		graphics.FillRectangle(&brush, -1, -1, getWidth() + 1, getHieght() + 1);

		graphics.DrawImage(_image, 4, 4, getWidth() - 8, getHieght() - 8);
		if (this->isLocked()) {
			Gdiplus::SolidBrush lockBrush(MAIN_WINDOW_COLOR_HEADER_BUTTON_LOCK);
			graphics.FillRectangle(&lockBrush, -1, -1, getWidth() + 1, getHieght() + 1);
		}
	}
}