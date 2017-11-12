#include "stdafx.h"
#include "ClassCheckButton.h"

namespace explorer {

	void CheckButton::init()
	{
		m_registerHendler(METHOD(&CheckButton::paintHandler));
		m_registerHendler(METHOD(&CheckButton::mouseClickHandler));
	}

	CheckButton::CheckButton() : _isChecked(false)
	{
		init();
	}
	CheckButton::CheckButton(bool checked) : _isChecked(false)
	{
		init();
	}

	void CheckButton::paintHandler(Gdiplus::Graphics& graphics)
	{
		graphics.Clear(Gdiplus::Color(128, 0, 0, 0));
	}
	void CheckButton::mouseClickHandler(const MouseEventClick& mouseEventClick)
	{
		if (mouseEventClick.Button == MOUSE_LEFT && mouseEventClick.Status == KEY_PRESSED) {
		}
	}

}