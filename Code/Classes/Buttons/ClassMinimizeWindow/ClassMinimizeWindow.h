#pragma once

#include "..\AbstractWindow\ClassAbstractWindow.h"

#ifndef _CLASS_MINIMIZE_WINDOW_H_
#define _CLASS_MINIMIZE_WINDOW_H_

namespace explorer {
	class ButtonMinimize : public Window {
	private:
		bool _hover;

	public:
		ButtonMinimize();

		void createHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
		void paintHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
		void hoverHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
		void minimizeHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
		void resizeParentHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
	};
}

#endif