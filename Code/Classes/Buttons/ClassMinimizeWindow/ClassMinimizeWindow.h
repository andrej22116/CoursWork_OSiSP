#pragma once

#include "..\..\Buttons\ClassAbstractButton\ClassAbstractButton.h"

#ifndef _CLASS_MINIMIZE_WINDOW_H_
#define _CLASS_MINIMIZE_WINDOW_H_

namespace explorer {
	class ButtonMinimize : public Button {
	private:
	public:
		ButtonMinimize();

		void paintHandler(Gdiplus::Graphics& graphics);
		void resizeParentHandler(const ParentEvent& parentEvent);

		void minimizeHandler(const MouseEventClick& mouseEventClick);
	};
}

#endif