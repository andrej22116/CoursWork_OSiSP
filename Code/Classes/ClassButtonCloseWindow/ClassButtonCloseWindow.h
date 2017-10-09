#pragma once

#include "..\AbstractWindow\ClassAbstractWindow.h"

#ifndef _CLASS_BUTTON_CLOSE_WINDOW_H_
#define _CLASS_BUTTON_CLOSE_WINDOW_H_

namespace explorer {

	class ButtonClose : public Window {
	public:
		ButtonClose::ButtonClose();

		LRESULT ButtonClose::closeHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
	};

}

#endif