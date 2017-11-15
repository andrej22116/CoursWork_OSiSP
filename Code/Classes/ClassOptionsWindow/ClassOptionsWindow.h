#pragma once

#include "..\AbstractWindow\ClassAbstractWindow.h"
#include "..\Buttons\ClassCheckButton\ClassCheckButton.h"
#include "..\ClassAbstractLeftWindow\ClassAbstractLeftWindow.h"

#ifndef _CLASS_OPTIONS_WINDOW_H_
#define _CLASS_OPTIONS_WINDOW_H_

namespace explorer {

	class OptionsWindow : public LeftWindow {
	private:
		std::list<std::wstring> _listOfParams;

		std::vector<CheckButton> _listOfcheckBoxes;

	public:
		OptionsWindow();

		virtual void eventCreateWindow() override;
		void paintHandler(Gdiplus::Graphics& graphics);
	};

}

#endif
