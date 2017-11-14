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
		static bool _displayExtension;
		static bool _displayHiddenFiles;
		static bool _displayFileSize;
		static bool _openDirectoriesInNewTab;
		static bool _restoreLastTabs;
		static bool _displayIcons;

		std::wstring _thisDirection;
		std::vector<File::FileInfo> _thisCatalog;
		std::vector<std::pair<std::wstring, int>> _logicalDrives;

		std::stack<std::wstring> _forwardStack;
		std::stack<std::wstring> _backwardStack;

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
		void nextDirrectory(std::wstring& oldDirrectory);

		std::wstring getCurrentDirectory();
		void setCurrentDirectory(std::wstring& directory);

	private:
		void calcOneLeftClick(const MouseEventClick& mouseEventClick);
		void calcDoubleLeftClick(const MouseEventClick& mouseEventClick);

	/// External elements
	private:
		ButtonReturn* _buttonBackward;
		ButtonReturn* _buttonForward;
		ButtonReturn* _buttonUp;
	public:
		void setButtonBackward(ButtonReturn* button);
		void setButtonForward(ButtonReturn* button);
		void setButtonUp(ButtonReturn* button);

		void mouseClickButtonBackwardHandler(const MouseEventClick& mouseEventClick);
		void mouseClickButtonForwardHandler(const MouseEventClick& mouseEventClick);
		void mouseClickButtonUpHandler(const MouseEventClick& mouseEventClick);
	};

}

#endif