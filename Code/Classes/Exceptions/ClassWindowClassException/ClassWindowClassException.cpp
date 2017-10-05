#include "ClassWindowClassException.h"

namespace Explorer {
	WindowClassException::WindowClassException()
	{
		_msg = L"Window class exception!";
	}
	WindowClassException::WindowClassException(std::wstring msg)
	{
		_msg = msg;
	}
}