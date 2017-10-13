#pragma once

#include "..\..\AbstractWindow\ClassAbstractWindow.h"

#ifndef _CLASS_BUTTON_CLOSE_WINDOW_H_
#define _CLASS_BUTTON_CLOSE_WINDOW_H_

namespace explorer {

	class ButtonClose : public Window {
	private:
		Gdiplus::Region _region;
		bool _hover;

	public:
		ButtonClose();

		void createHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
		void closeHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
		void paintHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);

		void hoverHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
		void resizeParentHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
	};

}

#endif