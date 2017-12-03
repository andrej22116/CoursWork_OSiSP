#pragma once

#include "..\ClassAbstractButton\ClassAbstractButton.h"
#include "..\ClassButtonCloseTab\ClassButtonCloseTab.h"

#ifndef _CLASS_TAB_LINE_BUTTON_H_
#define _CLASS_TAB_LINE_BUTTON_H_

namespace explorer {

	class TabLineButton : public Button {
	private:
		CloseTabButton _closeButton;

		bool _selected;

	public:
		TabLineButton();

		virtual void eventCreateWindow() override;

		void paintHandler(Gdiplus::Graphics& graphics);
	};

}

#endif