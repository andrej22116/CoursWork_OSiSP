#pragma once

#include "..\AbstractWindow\ClassAbstractWindow.h"
#include "..\Buttons\ClassButtonCloseWindow\ClassButtonCloseWindow.h"
#include "..\Buttons\ClassMaximizeWindow\ClassMaximizeWindow.h"
#include "..\Buttons\ClassMinimizeWindow\ClassMinimizeWindow.h"
#include "..\ClassListOfFilesWindow\ClassListOfFilesWindow.h"
#include "..\Buttons\ClassOptionsWindow\ClassOptionsWindow.h"
#include "..\Buttons\ClassReturnWindow\ClassReturnWindow.h"

#ifndef _CLASS_MAIN_WINDOW_H_
#define _CLASS_MAIN_WINDOW_H_

namespace explorer {

	class MainWindow : public Window {
	private:
		ButtonClose buttonClose;
		ButtonMaximize buttonMaximize;
		ButtonMinimize buttonMinimize;
		ListOfFiles listOfFiles;
		ButtonReturn buttonBackward;
		ButtonReturn buttonForward;
		ButtonReturn buttonUp;
		ButtonOptions buttonOptions;

	public:
		MainWindow();

		virtual void eventCreateWindow() override;
		virtual void eventSizeWindow(int oldWidth, int oldHeight) override;
		void paintHandler(Gdiplus::Graphics& graphics);
		
		void mouseClickHandler(const MouseEventClick& mouseEventClick);
		void keyboardHandler(const KeyEvent& keyEvent);
		
		void mouseMoveHandler(MouseEvent& mouseEvent);

	private:
	};
}

#endif