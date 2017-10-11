#pragma once

#include "..\AbstractWindow\ClassAbstractWindow.h"
#include "..\ClassButtonCloseWindow\ClassButtonCloseWindow.h"
#include "..\ClassMaximizeWindow\ClassMaximizeWindow.h"

#ifndef _CLASS_MAIN_WINDOW_H_
#define _CLASS_MAIN_WINDOW_H_

namespace explorer {

	class MainWindow : public Window {
	private:
		ButtonClose buttonClose;
		ButtonMaximizeWindow buttonMaximize;

	public:
		MainWindow();

		void createHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
		void paintHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
	};
}

#endif