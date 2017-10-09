#include "stdafx.h"
#include "ClassWindowException.h"

namespace explorer {
	WindowException::WindowException()
	{
		_msg = L"Window exception!";
	}
	WindowException::WindowException(std::wstring msg)
	{
		_msg = msg;
	}
}