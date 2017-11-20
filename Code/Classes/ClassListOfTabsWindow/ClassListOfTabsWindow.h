#pragma once

#include "..\ClassAbstractLeftWindow\ClassAbstractLeftWindow.h"
#include "..\Buttons\ClassNewTabButton\ClassNewTabButton.h"

#ifndef _CLASS_LIST_OF_TABS_WINDOW_H_
#define _CLASS_LIST_OF_TABS_WINDOW_H_

namespace explorer {

	class TabbedWindow : public LeftWindow {
	private:
		NewTubButton newTubButton;

	public:
		TabbedWindow();

		virtual void eventCreateWindow() override;

		void paintHandler(Gdiplus::Graphics& graphics);

	};

}

#endif