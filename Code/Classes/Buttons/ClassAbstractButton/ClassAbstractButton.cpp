#include "stdafx.h"
#include "ClassAbstractButton.h"

namespace explorer {

	Button::Button()
	{
		registerHendler(METHOD(&Button::hoverHandler));
		setLock(false);
	}

	void Button::eventCreateWindow()
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