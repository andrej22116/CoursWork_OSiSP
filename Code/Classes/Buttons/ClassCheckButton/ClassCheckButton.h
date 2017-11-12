#pragma once

#include "..\\..\\AbstractWindow\ClassAbstractWindow.h"

#ifndef _CLASS_CHECK_BUTTON_H_
#define _CLASS_CHECK_BUTTON_H_

namespace explorer {

	class CheckButton : public Window {
	private:
		bool _isChecked;


	public:
		void init();

		CheckButton();
		CheckButton(bool checked);

		void paintHandler(Gdiplus::Graphics& graphics);
		void mouseClickHandler(const MouseEventClick& mouseEventClick);

		bool getCheckStatus();
		void setCheckStatus(bool status);
	};

}

#endif