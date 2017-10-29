#pragma once

#ifndef _CLASS_BUTTON_UP_WINDOW_H_
#define _CLASS_BUTTON_UP_WINDOW_H_

#include "..\ClassAbstractButton\ClassAbstractButton.h"
#include "..\..\ClassListOfFilesWindow\ClassListOfFilesWindow.h"

namespace explorer {

	class ListOfFiles;

	class ButtonUp : public Button {
	private:
		Gdiplus::Image* _image;
		ListOfFiles* _listOfFiles;

		ButtonUp();

	public:
		ButtonUp(ListOfFiles* listOfFiles);
		~ButtonUp();

		void paintHandler(Gdiplus::Graphics& graphics);

		void mouseClickUpHandler(const MouseEventClick& mouseEventClick);
	};

}

#endif