#pragma once

#include "..\..\AbstractWindow\ClassAbstractWindow.h"

#ifndef _CLASS_ABSTRACT_BUTTON_H_
#define _CLASS_ABSTRACT_BUTTON_H_

namespace explorer {

	class Button : public Window {
	public:
		Button();

		void hoverHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
		void resizeParentHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
	};

}

#endif