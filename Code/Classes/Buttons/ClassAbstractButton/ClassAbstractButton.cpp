#include "stdafx.h"
#include "ClassAbstractButton.h"

namespace explorer {

	Button::Button()
	{
		m_registerHendler(METHOD(&Button::hoverHandler));
	}

	void Button::createWindow()
	{
		getHoverMessages(true);
	}

	void Button::hoverHandler(bool status)
	{
		_hover = status;
		redrawWindow(false);
	}

	bool Button::isHover()
	{
		return _hover;
	}
}