#pragma once

#include "..\ClassAbstractButton\ClassAbstractButton.h"

#ifndef _CLASS_NEW_TAB_BUTTON_H_
#define _CLASS_NEW_TAB_BUTTON_H_

namespace explorer {

	class NewTubButton : public Button {
	private:

	public:
		NewTubButton();

		void paintHandler(Gdiplus::Graphics& graphics);

	};

}

#endif