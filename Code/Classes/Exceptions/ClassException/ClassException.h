#pragma once

#ifndef _CLASS_EXCEPTION_H_
#define _CLASS_EXCEPTION_H_

namespace explorer {
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