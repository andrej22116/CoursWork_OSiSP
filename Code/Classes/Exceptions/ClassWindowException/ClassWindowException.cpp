#include "ClassWindowException.h"

namespace Explorer {
	WindowException::WindowException()
	{
		_msg = L"Window exception!";
	}
	WindowException::WindowException(std::wstring msg)
	{
		_msg = msg;
	}
}