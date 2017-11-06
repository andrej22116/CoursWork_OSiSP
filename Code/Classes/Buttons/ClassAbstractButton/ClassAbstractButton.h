#pragma once

#include "..\..\AbstractWindow\ClassAbstractWindow.h"

#ifndef _CLASS_ABSTRACT_BUTTON_H_
#define _CLASS_ABSTRACT_BUTTON_H_

namespace explorer {

	class Button : public Window {
	private:
		bool _hover;
	public:
		Button();

		virtual void eventCreateWindow() override final;
		void hoverHandler(bool status);

		bool isHover();
	};

}

#endif