#pragma once

#include "..\ClassAbstractButton\ClassAbstractButton.h"

#ifndef _CLASS_BUTTON_CLOSE_TAB_H_
#define _CLASS_BUTTON_CLOSE_TAB_H_

namespace explorer {

	class CloseTabButton : public Button {
	public:
		CloseTabButton();

		void paintHandler(Gdiplus::Graphics& graphics);
	};

}

#endif