#pragma once

#include "..\AbstractWindow\ClassAbstractWindow.h"

#ifndef _CLASS_MAIN_WINDOW_H_
#define _CLASS_MAIN_WINDOW_H_

namespace Explorer {

	class MainWindow : public Window {
	private:
		int _width, _hieght;

	public:
		MainWindow();
		MainWindow(int width, int hieght);

		static LRESULT WndProc(HWND hWnd, int msg, WPARAM wParam, LPARAM lParam);
	};
}

#endif