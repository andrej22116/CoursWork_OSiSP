#pragma once

#include "..\ClassAbstractButton\ClassAbstractButton.h"

#ifndef _CLASS_RETURN_WINDOW_H_
#define _CLASS_RETURN_WINDOW_H_

namespace explorer {
	class ButtonReturn : public Button {
	public:
		enum ButtonReturnType {
			BUTTON_RETURN_BACKWARD = 0,
			BUTTON_RETURN_FORWARD,
			BUTTON_RETURN_UP,
			BUTTON_RETURN_TYPES_COUNT
		};

	private:
		Gdiplus::Image* _image;
		ButtonReturnType _type;

		static std::stack<std::wstring> _forwardStack;
		static std::stack<std::wstring> _backwardStack;

	public:
		static std::vector<ButtonReturn*> buttons;

		ButtonReturn(ButtonReturnType type);
		~ButtonReturn();

		void paintHandler_backward(Gdiplus::Graphics& graphics);
		void paintHandler_forward(Gdiplus::Graphics& graphics);
		void paintHandler_up(Gdiplus::Graphics& graphics);

		void mouseClickHandler_backward(const MouseEventClick& mouseEventClick);
		void mouseClickHandler_forward(const MouseEventClick& mouseEventClick);
		void mouseClickHandler_up(const MouseEventClick& mouseEventClick);

		static void nextDirrectory(std::wstring& oldDirrectory);
	};

}

#endif