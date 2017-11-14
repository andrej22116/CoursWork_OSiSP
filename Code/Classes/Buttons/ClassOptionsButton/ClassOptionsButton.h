#pragma once

#include "..\ClassAbstractButton\ClassAbstractButton.h"

#ifndef _CLASS_OPTIONS_BUTTON_H_
#define _CLASS_OPTIONS_BUTTON_H_

namespace explorer {

	class ListOfFiles;

	class ButtonOptions : public Button {
	private:
		ListOfFiles* _listOfFiles;

		Gdiplus::Image* _image;

	public:
		ButtonOptions();
		~ButtonOptions();

		void paintHandler(Gdiplus::Graphics& graphics);

		void mouseClickOptionsHandler(const MouseEventClick& mouseEventClick);
	};

}

#endif