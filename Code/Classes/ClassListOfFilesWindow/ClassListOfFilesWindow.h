#pragma once

#include "..\AbstractWindow\ClassAbstractWindow.h"
#include "..\FileSystem\ClassFile\ClassFile.h"

#ifndef _CLASS_LIST_OF_FILES_WINDOW_H_
#define _CLASS_LIST_OF_FILES_WINDOW_H_

namespace explorer {

	class ListOfFiles : public Window {
	private:
		std::wstring _thisDirection;
		std::vector<std::wstring> _thisCatalog;

		int _activeLine;
		int _selectedLine;

	public:
		ListOfFiles();

		virtual void createWindow() override;
		void paintHandler(Gdiplus::Graphics& graphics);

		void mouseClickHandler(const MouseEventClick& mouseEventClick);

		void mouseMoveHandler(MouseEvent& mouseEvent);


		void resizeParentHandler(const ParentEvent& parentEvent);

		void updateList();
		const std::wstring& getCurrentDirectory();
		void setCurrentDirectory(std::wstring& directory);

	private:
		void calcOneLeftClick(const MouseEventClick& mouseEventClick);
		void calcDoubleLeftClick(const MouseEventClick& mouseEventClick);
	};

}

#endif