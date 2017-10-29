#pragma once

#ifndef _CLASS_LIST_OF_FILES_WINDOW_H_
#define _CLASS_LIST_OF_FILES_WINDOW_H_

#include "..\AbstractWindow\ClassAbstractWindow.h"
#include "..\FileSystem\ClassFile\ClassFile.h"
#include "..\Buttons\ClassButtonUpWindow\ClassButtonUpWindow.h"

namespace explorer {

	class ButtonUp;

	class ListOfFiles : public Window {
	private:
		ButtonUp* _buttonUp;

		std::wstring _thisDirection;
		std::vector<std::wstring> _thisCatalog;
		std::vector<std::pair<std::wstring, int>> _logicalDrives;

		int _activeLine;
		int _selectedLine;

		bool _inDrive;

	public:
		ListOfFiles(ButtonUp* buttonUp);

		virtual void createWindow() override;
		void paintHandler(Gdiplus::Graphics& graphics);

		void mouseClickHandler(const MouseEventClick& mouseEventClick);

		void mouseMoveHandler(MouseEvent& mouseEvent);


		void resizeParentHandler(const ParentEvent& parentEvent);

		void updateList();
		const std::wstring& getCurrentDirectory();
		void setCurrentDirectory(std::wstring& directory);

		void updateButtonUP(bool lock);

	private:
		void calcOneLeftClick(const MouseEventClick& mouseEventClick);
		void calcDoubleLeftClick(const MouseEventClick& mouseEventClick);
	};

}

#endif