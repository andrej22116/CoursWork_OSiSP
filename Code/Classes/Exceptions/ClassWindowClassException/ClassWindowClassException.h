#pragma once
#include "..\ClassException\ClassException.h"

#ifndef _CLASS_WINDOW_CLASS_EXCEPTION_H_
#define _CLASS_WINDOW_CLASS_EXCEPTION_H_

namespace Explorer {
	class WindowClassException : public Exception {
	private:
		std::wstring _msg;
	public:
		WindowClassException();
		WindowClassException(std::wstring msg);
	};
}

#endif