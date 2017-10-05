#pragma once
#include <Windows.h>
#include <string>

#ifndef _CLASS_EXCEPTION_H_
#define _CLASS_EXCEPTION_H_

namespace Explorer {
	class Exception {
	protected:
		std::wstring _msg;
	public:
		Exception();
		Exception(std::wstring msg);

		void showMsg();
	};
}

#endif