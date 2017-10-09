#include "stdafx.h"
#include "ClassException.h"

namespace explorer {
	Exception::Exception()
	{
		_msg = L"Exception!";
	}
	Exception::Exception(std::wstring msg)
	{
		_msg = msg;
	}

	void Exception::showMsg()
	{
		MessageBoxW(nullptr, _msg.c_str(), L"Exception", MB_OK | MB_ICONERROR);
	}
}