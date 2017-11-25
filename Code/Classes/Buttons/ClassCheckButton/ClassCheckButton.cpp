#include "stdafx.h"
#include "ClassCheckButton.h"

namespace explorer {

	void CheckButton::init()
	{
		registerHendler(METHOD(&CheckButton::paintHandler));
		registerHendler(METHOD(&CheckButton::mouseClickHandler));

		setLock(false);
	}

	CheckButton::CheckButton() : _isChecked(false)
	{
		init();
	}
	CheckButton::CheckButton(bool checked) : _isChecked(checked)
	{
		init();
	}
	CheckButton::CheckButton(const CheckButton& rabotaiSuka)
	{

	}

	void CheckButton::paintHandler(Gdiplus::Graphics& graphics)
	{
		graphics.Clear(Gdiplus::Color(200, 255, 255, 255));
		graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

		int width = getWidth();
		int height = getHieght();
		
		if (!isLocked()) {
			if (_isChecked) {
				Gdiplus::Pen pen(Gdiplus::Color(254, 39, 215, 4), 1);
				Gdiplus::Pen pen_ok(Gdiplus::Color(254, 0, 128, 4), 1);
				graphics.DrawEllipse(&pen, 0, 0, width - 1, height - 1);

				graphics.DrawLine(&pen_ok, Gdiplus::Point(width / 2, 5), Gdiplus::Point(width / 2, height - 6));
				graphics.DrawLine(&pen_ok, Gdiplus::Point(5, height / 2), Gdiplus::Point(width - 6, height / 2));
			}
			else {
				Gdiplus::Pen pen(Gdiplus::Color(254, 255, 39, 0), 1);
				graphics.DrawEllipse(&pen, 0, 0, width - 1, height - 1);

				graphics.DrawLine(&pen, Gdiplus::Point(5, height / 2), Gdiplus::Point(width - 6, height / 2));
			}
		}
		else {
			Gdiplus::Pen pen(Gdiplus::Color(254, 196, 196, 196), 1);
			graphics.DrawEllipse(&pen, 0, 0, width - 1, height - 1);

			if (_isChecked) {
				graphics.DrawLine(&pen, Gdiplus::Point(width / 2, 5), Gdiplus::Point(width / 2, height - 6));
				graphics.DrawLine(&pen, Gdiplus::Point(5, height / 2), Gdiplus::Point(width - 6, height / 2));
			}
			else {
				graphics.DrawLine(&pen, Gdiplus::Point(5, height / 2), Gdiplus::Point(width - 6, height / 2));
			}
		}
	}
	void CheckButton::mouseClickHandler(const MouseEventClick& mouseEventClick)
	{
		if (mouseEventClick.Button == MOUSE_LEFT && mouseEventClick.Status == KEY_PRESSED && !isLocked()) {
			setCheckStatus(!_isChecked);
		}
	}

	bool CheckButton::getCheckStatus()
	{
		return _isChecked;
	}
	void CheckButton::setCheckStatus(bool status)
	{
		_isChecked = status;
		redrawWindow(false);
	}

}