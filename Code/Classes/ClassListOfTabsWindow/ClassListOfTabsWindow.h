#pragma once

#include "..\ClassAbstractLeftWindow\ClassAbstractLeftWindow.h"
#include "..\Buttons\ClassNewTabButton\ClassNewTabButton.h"

#ifndef _CLASS_LIST_OF_TABS_WINDOW_H_
#define _CLASS_LIST_OF_TABS_WINDOW_H_

namespace explorer {

	class MainWindow;

	class TabbedWindow : public LeftWindow {
	private:
		NewTubButton newTubButton;
		std::list<std::wstring> _listOfDirs;

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
		
		void updateList(std::list <std::wstring> list);

	};

}

#endif