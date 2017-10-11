#pragma once

#include "..\AbstractWindow\ClassAbstractWindow.h"

#ifndef _CLASS_MAXIMIZE_WINDOW_H_
#define _CLASS_MAXIMIZE_WINDOW_H_

namespace explorer {

	class ButtonMaximizeWindow : public Window {
	private:
		bool _maximized;
		bool _hover;

		int _oldWidth, _oldHieght;
		int _oldPosX, _oldPosY;

	public:
		ButtonMaximizeWindow();

		void createHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
		void paintHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
		void hoverHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
		void maximizeHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
		void resizeParentHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);

#ifdef _DEBUG
		void testHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
#endif
	};

}

#endif