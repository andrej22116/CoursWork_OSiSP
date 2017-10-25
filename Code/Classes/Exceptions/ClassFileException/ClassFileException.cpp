#include "stdafx.h"
#include "ClassFileException.h"

namespace explorer {

	FileException::FileException()
	{
		_msg = L"File exception";
	}
	FileException::FileException(std::wstring msg)
	{
		_msg = msg;
	}

}