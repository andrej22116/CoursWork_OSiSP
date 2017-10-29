#pragma once

#include "..\AbstractWindow\ClassAbstractWindow.h"
#include "..\Buttons\ClassButtonCloseWindow\ClassButtonCloseWindow.h"
#include "..\Buttons\ClassMaximizeWindow\ClassMaximizeWindow.h"
#include "..\Buttons\ClassMinimizeWindow\ClassMinimizeWindow.h"
#include "..\ClassListOfFilesWindow\ClassListOfFilesWindow.h"
#include "..\Buttons\ClassButtonUpWindow\ClassButtonUpWindow.h"

#ifndef _CLASS_MAIN_WINDOW_H_
#define _CLASS_MAIN_WINDOW_H_

namespace explorer {

	class MainWindow : public Window {
	private:
		ButtonClose buttonClose;
		ButtonMaximize buttonMaximize;
		ButtonMinimize buttonMinimize;
		ListOfFiles listOfFiles;
		ButtonUp buttonUp;

	public:
		MainWindow();

		virtual void createWindow() override;
		void paintHandler(Gdiplus::Graphics& graphics);
		
		void mouseClickHandler(const MouseEventClick& mouseEventClick);
		void keyboardHandler(const KeyEvent& keyEvent);
		
		void mouseMoveHandler(MouseEvent& mouseEvent);

	private:
	};
}

#endif