#pragma once

#include "..\ClassAbstractLeftWindow\ClassAbstractLeftWindow.h"

#ifndef _CLASS_LIST_OF_TABS_WINDOW_H_
#define _CLASS_LIST_OF_TABS_WINDOW_H_

namespace explorer {

	class TabbedWindow : public LeftWindow {
	private:

	public:
		TabbedWindow();

		void paintHandler(Gdiplus::Graphics& graphics);

	};

}

#endif