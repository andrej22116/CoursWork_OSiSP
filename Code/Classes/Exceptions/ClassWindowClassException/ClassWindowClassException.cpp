#include "stdafx.h"
#include "ClassWindowClassException.h"

namespace explorer {
	WindowClassException::WindowClassException()
	{
		_msg = L"Window class exception!";
	}
	WindowClassException::WindowClassException(std::wstring msg)
	{
		_msg = msg;
	}
}