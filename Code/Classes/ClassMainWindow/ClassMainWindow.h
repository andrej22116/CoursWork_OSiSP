#pragma once

#include "..\AbstractWindow\ClassAbstractWindow.h"
#include "..\ClassButtonCloseWindow\ClassButtonCloseWindow.h"

#ifndef _CLASS_MAIN_WINDOW_H_
#define _CLASS_MAIN_WINDOW_H_

namespace explorer {

	class MainWindow : public Window {
	private:
		ButtonClose buttonClose;
	public:
		MainWindow();

		void registerWindowHandlers();

		void createHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
		void paintHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
		void paintHandler_2(HWND hWnd, WPARAM wParam, LPARAM lParam);
	};
}

#endif