#pragma once

#ifndef _CLASS_LIST_OF_FILES_WINDOW_H_
#define _CLASS_LIST_OF_FILES_WINDOW_H_

#include "..\AbstractWindow\ClassAbstractWindow.h"
#include "..\FileSystem\ClassFile\ClassFile.h"
#include "..\Buttons\ClassReturnWindow\ClassReturnWindow.h"

namespace explorer {

	class ButtonReturn;

	class ListOfFiles : public Window {
	private:
		std::wstring _thisDirection;
		std::vector<File::FileInfo> _thisCatalog;
		std::vector<std::pair<std::wstring, int>> _logicalDrives;

		int _activeLine;
		int _selectedLine;

		bool _inDrive;

	public:
		ListOfFiles();

		virtual void eventCreateWindow() override;
		virtual void eventSizeWindow(int oldWidth, int oldHeight) override;

		void paintHandler(Gdiplus::Graphics& graphics);

		void mouseClickHandler(const MouseEventClick& mouseEventClick);

		void mouseMoveHandler(MouseEvent& mouseEvent);


		void resizeParentHandler(const ParentEvent& parentEvent);

		void updateList();
		std::wstring getCurrentDirectory();
		void setCurrentDirectory(std::wstring& directory);

		void updateButtonUP(bool lock);

	private:
		void calcOneLeftClick(const MouseEventClick& mouseEventClick);
		void calcDoubleLeftClick(const MouseEventClick& mouseEventClick);
	};

}

#endif