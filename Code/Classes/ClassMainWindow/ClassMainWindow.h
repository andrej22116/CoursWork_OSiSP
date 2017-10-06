#pragma once

#include "..\AbstractWindow\ClassAbstractWindow.h"

#ifndef _CLASS_MAIN_WINDOW_H_
#define _CLASS_MAIN_WINDOW_H_

namespace Explorer {

	class MainWindow : public Window {
	public:
		MainWindow::MainWindow(int pos_x, int pos_y);
		MainWindow::MainWindow(int pos_x, int pos_y, int width, int hieght, bool show);
		MainWindow::MainWindow(std::wstring name, int pos_x, int pos_y, int width, int hieght, bool show);

		void registerWindowHandlers();

		LRESULT createHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
	};
}

#endif