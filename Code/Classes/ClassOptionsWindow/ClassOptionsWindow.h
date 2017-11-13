#pragma once

#include "..\AbstractWindow\ClassAbstractWindow.h"
#include "..\Buttons\ClassCheckButton\ClassCheckButton.h"

#ifndef _CLASS_OPTIONS_WINDOW_H_
#define _CLASS_OPTIONS_WINDOW_H_

namespace explorer {

	class OptionsWindow : public Window {
	private:
		bool _show;
		bool _animation;
		int _animationStatus;

		CheckButton _test;

	public:
		OptionsWindow();

		virtual void eventCreateWindow() override;
		void paintHandler(Gdiplus::Graphics& graphics);

		bool isShow();
		void show(bool show);

		void timerHandler(const int timer_ID);
	};

}

#endif
