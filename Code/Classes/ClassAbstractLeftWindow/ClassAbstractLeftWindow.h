#pragma once

#include "..\AbstractWindow\ClassAbstractWindow.h"

#ifndef _CLASS_ABSTRACT_LEFT_WINDOW_H_
#define _CLASS_ABSTRACT_LEFT_WINDOW_H_

namespace explorer {

	class LeftWindow : public Window {
	private:
		bool _show;
		bool _animation;
		int _animationStatus;

	public:
		LeftWindow();

		bool isShow();
		void show(bool show);

		void paintHandler(Gdiplus::Graphics& graphics);
		void timerHandler(const int timer_ID);
	};

}

#endif