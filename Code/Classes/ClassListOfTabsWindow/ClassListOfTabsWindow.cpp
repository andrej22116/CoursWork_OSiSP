#include "stdafx.h"
#include "ClassListOfTabsWindow.h"

namespace explorer {

	TabbedWindow::TabbedWindow()
	{
		registerHendler(METHOD(&TabbedWindow::paintHandler));
	}

	void TabbedWindow::eventCreateWindow()
	{
		int width = getWidth();
		newTubButton.create(
			*this,
			width - 38,
			5,
			30,
			30,
			true
		);


	}

	void TabbedWindow::paintHandler(Gdiplus::Graphics& graphics)
	{

	}

}