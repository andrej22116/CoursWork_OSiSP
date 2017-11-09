#pragma once

#include "..\..\Buttons\ClassAbstractButton\ClassAbstractButton.h"

#ifndef _CLASS_BUTTON_CLOSE_WINDOW_H_
#define _CLASS_BUTTON_CLOSE_WINDOW_H_

namespace explorer {

	class ButtonClose : public Button {
	private:

	public:
		ButtonClose();
		
		void paintHandler(Gdiplus::Graphics& graphics);
		void resizeParentHandler(const ParentEvent& parentEvent);

		void mouseClickCloseHandler(const MouseEventClick& mouseEventClick);
	};

}

#endif