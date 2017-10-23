#pragma once

#include "..\AbstractWindow\ClassAbstractWindow.h"
#include "..\Buttons\ClassButtonCloseWindow\ClassButtonCloseWindow.h"
#include "..\Buttons\ClassMaximizeWindow\ClassMaximizeWindow.h"
#include "..\Buttons\ClassMinimizeWindow\ClassMinimizeWindow.h"

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
		bool _resize_x, _resize_y;

		bool _inBorder_x_left, _inBorder_x_right;
		bool _inBorder_y_top, _inBorder_y_bot;
		bool _inHeader;

	public:
		MainWindow();

		virtual void createWindow() override;
		void paintHandler(Gdiplus::Graphics& graphics);
		
		void mouseClickHandler(const MouseEventClick& mouseEventClick);
		void keyboardHandler(const KeyEvent& keyEvent);
		
		void mouseMoveHandler(MouseEvent& mouseEvent);

	private:
		void checkCursorPosInBorder(MouseEvent& mouseEvent);
		void checkCursorPosInHeader(MouseEvent& mouseEvent);

		void move(MouseEvent& mouseEvent);
		void resize(MouseEvent& mouseEvent);
	};
}

#endif