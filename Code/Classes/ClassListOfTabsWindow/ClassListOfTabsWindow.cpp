#include "stdafx.h"
#include "ClassListOfTabsWindow.h"

namespace explorer {

	TabbedWindow::TabbedWindow()
	{
		registerHendler(METHOD(&TabbedWindow::paintHandler));
	}

	void TabbedWindow::paintHandler(Gdiplus::Graphics& graphics)
	{

	}

}