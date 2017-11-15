#pragma once
#
#include "..\ClassAbstractButton\ClassAbstractButton.h"

#ifndef _CLASS_TABS_BUTTON_H_
#define _CLASS_TABS_BUTTON_H_

namespace explorer {

	class TabsButton : public Button {
	private:

	public:
		TabsButton();

		void paintHandler(Gdiplus::Graphics& graphics);
	};

}

#endif