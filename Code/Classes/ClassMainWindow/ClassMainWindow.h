#pragma once

#include "..\AbstractWindow\ClassAbstractWindow.h"
#include "..\Buttons\ClassButtonCloseWindow\ClassButtonCloseWindow.h"
#include "..\Buttons\ClassMaximizeWindow\ClassMaximizeWindow.h"
#include "..\Buttons\ClassMinimizeWindow\ClassMinimizeWindow.h"
#include "..\ClassListOfFilesWindow\ClassListOfFilesWindow.h"
#include "..\ClassOptionsWindow\ClassOptionsWindow.h"
#include "..\Buttons\ClassOptionsButton\ClassOptionsButton.h"
#include "..\Buttons\ClassReturnWindow\ClassReturnWindow.h"
#include "..\Buttons\ClassNewTabButton\ClassNewTabButton.h"
#include "..\ClassListOfTabsWindow\ClassListOfTabsWindow.h"
#include "..\Buttons\ClassTabsButton\ClassTabsButton.h"

#ifndef _CLASS_MAIN_WINDOW_H_
#define _CLASS_MAIN_WINDOW_H_

namespace explorer {
	class MainWindow : public Window {
	private:
		ButtonClose buttonClose;
		ButtonMaximize buttonMaximize;
		ButtonMinimize buttonMinimize;
		ListOfFiles listOfFiles;
		std::vector<ListOfFiles> _vectorOfListsOfFiles;
		ButtonReturn buttonBackward;
		ButtonReturn buttonForward;
		ButtonReturn buttonUp;
		ButtonOptions buttonOptions;
		OptionsWindow windowOptions;
		TabbedWindow tabbedWindow;
		TabsButton tabsButton;

		bool _batteryFound;
		bool _isCharging;
		int  _batteryStatus;

	public:
		MainWindow();

		virtual void eventCreateWindow() override;
		void paintHandler(Gdiplus::Graphics& graphics);
		
		void mouseClickHandler(const MouseEventClick& mouseEventClick);
		void mouseMoveHandler(MouseEvent& mouseEvent);
		void keyboardHandler(const KeyEvent& keyEvent);

		void updateBatteryStatusTimerHandler(int timerID);

		void mouseClickButtonOptionsHandler(const MouseEventClick& mouseEventClick);
		void mouseClickButtonAllTabsHandler(const MouseEventClick& mouseEventClick);
		void mouseClickButtonNewTabHandler(const MouseEventClick& mouseEventClick);

	private:
		void m_moveListOfFilesIfShowLeftWindow(int leftWindowWidth, bool leftWindowIsShow);
	};
}

#endif