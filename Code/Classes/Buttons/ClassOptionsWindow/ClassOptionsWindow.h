#pragma once

#include "..\ClassAbstractButton\ClassAbstractButton.h"
#include "..\..\ClassListOfFilesWindow\ClassListOfFilesWindow.h"

#ifndef _CLASS_OPTIONS_WINDOW_H_
#define _CLASS_OPTIONS_WINDOW_H_

namespace explorer {

	class ListOfFiles;

	class ButtonOptions : public Button {
	private:
		ListOfFiles* _listOfFiles;

	public:
		ButtonOptions(ListOfFiles* listOfFiles);

		void paintHandler(Gdiplus::Graphics& graphics);

		void mouseClickOptionsHandler(const MouseEventClick& mouseEventClick);
	};

}

#endif