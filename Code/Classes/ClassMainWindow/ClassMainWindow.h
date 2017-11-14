#pragma once

#include "..\AbstractWindow\ClassAbstractWindow.h"
#include "..\Buttons\ClassButtonCloseWindow\ClassButtonCloseWindow.h"
#include "..\Buttons\ClassMaximizeWindow\ClassMaximizeWindow.h"
#include "..\Buttons\ClassMinimizeWindow\ClassMinimizeWindow.h"
#include "..\ClassListOfFilesWindow\ClassListOfFilesWindow.h"
#include "..\ClassOptionsWindow\ClassOptionsWindow.h"
#include "..\Buttons\ClassOptionsButton\ClassOptionsButton.h"
#include "..\Buttons\ClassReturnWindow\ClassReturnWindow.h"

#ifndef _CLASS_MAIN_WINDOW_H_
#define _CLASS_MAIN_WINDOW_H_

namespace explorer {

	class ButtonClose;
	class ButtonMaximize;
	class ButtonMinimize;
	class ListOfFiles;
	class ButtonReturn;
	class ButtonReturn;
	class ButtonReturn;
	class ButtonOptions;
	class OptionsWindow;

	class MainWindow : public Window {
	private:
		ButtonClose buttonClose;
		ButtonMaximize buttonMaximize;
		ButtonMinimize buttonMinimize;
		std::vector<ListOfFiles> _vectorOfListsOfFiles;
		ButtonReturn buttonBackward;
		ButtonReturn buttonForward;
		ButtonReturn buttonUp;
		ButtonOptions buttonOptions;
		OptionsWindow windowOptions;

		bool _batteryFound;
		bool _isCharging;
		int  _batteryStatus;

	public:
		MainWindow();

		virtual void eventCreateWindow() override;
		void paintHandler(Gdiplus::Graphics& graphics);
		
		void mouseClickHandler(const MouseEventClick& mouseEventClick);
		void keyboardHandler(const KeyEvent& keyEvent);
		
		void mouseMoveHandler(MouseEvent& mouseEvent);

		bool windowOptionsIsShow();
		void showWindowOptions(bool show);

		void updateBatteryStatusTimerHandler(int timerID);

	private:
	};
}

#endif