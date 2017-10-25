#pragma once

#include <Windows.h>
#include "..\ClassException\ClassException.h"

#ifndef _CLASS_FILE_EXCEPTION_H_
#define _CLASS_FILE_EXCEPTION_H_

namespace explorer {

	class FileException : public Exception {
	private:
		std::wstring _msg;
	public:
		FileException();
		FileException(std::wstring msg);

	};

}

#endif