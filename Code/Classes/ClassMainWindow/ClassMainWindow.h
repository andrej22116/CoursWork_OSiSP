#pragma once

#include "..\AbstractWindow\ClassAbstractWindow.h"
#include "..\ClassButtonCloseWindow\ClassButtonCloseWindow.h"
#include "..\ClassMaximizeWindow\ClassMaximizeWindow.h"
#include "..\ClassMinimizeWindow\ClassMinimizeWindow.h"

#ifndef _CLASS_MAIN_WINDOW_H_
#define _CLASS_MAIN_WINDOW_H_

namespace explorer {

	class MainWindow : public Window {
	private:
		ButtonClose buttonClose;
		ButtonMaximize buttonMaximize;
		ButtonMinimize buttonMinimize;

		int _oldCursorPosX, _oldCursorPosY;
		bool _moving;

	public:
		MainWindow();

		void createHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
		void paintHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
		
		void leftButtonDownHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
		void leftButtonUpHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
		
		void moveHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
	};
}

#endif