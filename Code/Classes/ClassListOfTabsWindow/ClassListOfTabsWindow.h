#pragma once

#include "..\ClassAbstractLeftWindow\ClassAbstractLeftWindow.h"
#include "..\Buttons\ClassNewTabButton\ClassNewTabButton.h"
#include "..\Buttons\ClassButtonCloseTab\ClassButtonCloseTab.h"

#ifndef _CLASS_LIST_OF_TABS_WINDOW_H_
#define _CLASS_LIST_OF_TABS_WINDOW_H_

namespace explorer {

	class MainWindow;

	enum TabEvent {
		TAB_EVENT_SELECT,
		TAB_EVENT_CLOSE
	};
	typedef std::function<void(int, TabEvent)> UpdateTabsListHandler;

	class TabbedWindow : public LeftWindow {
	private:
		NewTubButton newTubButton;
		std::list<std::wstring> _listOfDirs;
		std::list<Button> _listOfCloseButtons;

		std::map<int, std::pair<std::wstring, std::shared_ptr<CloseTabButton>>> _listOfTabs;

		int _lineHeight;
		int _hoveredLine;
		int _selectedLine;

	public:
		friend MainWindow;

		TabbedWindow();

		virtual void eventCreateWindow() override;

		void paintHandler(Gdiplus::Graphics& graphics);

		void mouseMoveHandler(MouseEvent& mouseEvent);
		void mouseClickHandler(const MouseEventClick& mouseEventClick);
		
		void updateTabsMap(std::map<int, std::wstring> mapOfTabs);
		void updateOneTab(int tabKey, std::wstring newString);
		void deleteOneTab(int tabKey);

		void moveButtons();

		void update();

	};

}

#endif