#pragma once

#include "..\..\AbstractWindow\ClassAbstractWindow.h"

#ifndef _CLASS_BUTTON_CLOSE_WINDOW_H_
#define _CLASS_BUTTON_CLOSE_WINDOW_H_

namespace explorer {

	class ButtonClose : public Window {
	private:
		Gdiplus::Region _region;
		bool _hover;

	public:
		ButtonClose();

		virtual void createWindow() override;
		
		void paintHandler(Gdiplus::Graphics& graphics);
		void hoverHandler(HoverStatus status);
		void resizeParentHandler(const ParentEvent& parentEvent);

		void mouseClickCloseHandler(const MouseEventClick& mouseEventClick);
	};

}

#endif