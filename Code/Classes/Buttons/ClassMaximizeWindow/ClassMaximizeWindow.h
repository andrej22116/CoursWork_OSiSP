#pragma once

#include "..\..\AbstractWindow\ClassAbstractWindow.h"

#ifndef _CLASS_MAXIMIZE_WINDOW_H_
#define _CLASS_MAXIMIZE_WINDOW_H_

namespace explorer {

	class ButtonMaximize : public Window {
	private:
		bool _maximized;
		bool _hover;

		int _oldWidth, _oldHieght;
		int _oldPosX, _oldPosY;

	public:
		ButtonMaximize();

		virtual void createWindow() override;

		void paintHandler(Gdiplus::Graphics& graphics);
		void hoverHandler(bool status);
		void resizeParentHandler(const ParentEvent& parentEvent);

		void maximizeHandler(const MouseEventClick& mouseEventClick);

#ifdef _DEBUG
		void testHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
#endif
	};

}

#endif