#pragma once

#include "..\..\AbstractWindow\ClassAbstractWindow.h"

#ifndef _CLASS_MINIMIZE_WINDOW_H_
#define _CLASS_MINIMIZE_WINDOW_H_

namespace explorer {
	class ButtonMinimize : public Window {
	private:
		bool _hover;

	public:
		ButtonMinimize();

		virtual void createWindow() override;

		void paintHandler(Gdiplus::Graphics& graphics);
		void hoverHandler(bool status);
		void resizeParentHandler(const ParentEvent& parentEvent);

		void minimizeHandler(const MouseEventClick& mouseEventClick);
	};
}

#endif