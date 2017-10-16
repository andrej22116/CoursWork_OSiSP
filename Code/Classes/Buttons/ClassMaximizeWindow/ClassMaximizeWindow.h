#pragma once

#include "..\..\Buttons\ClassAbstractButton\ClassAbstractButton.h"

#ifndef _CLASS_MAXIMIZE_WINDOW_H_
#define _CLASS_MAXIMIZE_WINDOW_H_

namespace explorer {

	class ButtonMaximize : public Button {
	private:
		bool _maximized;

		int _oldWidth, _oldHieght;
		int _oldPosX, _oldPosY;

	public:
		ButtonMaximize();

		bool isMaximized();

		void paintHandler(Gdiplus::Graphics& graphics);
		void resizeParentHandler(const ParentEvent& parentEvent);

		void maximizeHandler(const MouseEventClick& mouseEventClick);

#ifdef _DEBUG
		void testHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
#endif
	};

}

#endif