#pragma once
#include "..\ClassException\ClassException.h"

#ifndef _CLASS_WINDOW_EXCEPTION_H_
#define _CLASS_WINDOW_EXCEPTION_H_

namespace Explorer {
	class WindowException : public Exception {
	private:
		std::wstring _msg;
	public:
		WindowException();
		WindowException(std::wstring msg);
	};
}

#endif