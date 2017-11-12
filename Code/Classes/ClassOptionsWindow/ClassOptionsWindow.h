#pragma once

#include "..\AbstractWindow\ClassAbstractWindow.h"

#ifndef _CLASS_OPTIONS_WINDOW_H_
#define _CLASS_OPTIONS_WINDOW_H_

namespace explorer {

	class OptionsWindow : public Window {
	private:
		bool _show;
		bool _animation;
		int _animationStatus;

	public:
		OptionsWindow();

		void paintHandler(Gdiplus::Graphics& graphics);

		bool isShow();
		void show(bool show);

		void timerHandler(const int timer_ID);
	};

}

#endif
