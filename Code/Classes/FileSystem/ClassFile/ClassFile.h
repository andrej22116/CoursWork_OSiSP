#pragma once

#include <Windows.h>

#ifndef _CLASS_FILE_H_
#define _CLASS_FILE_H_

namespace explorer {

	class File {
		std::wstring _path;
		std::wstring _fileName;

		bool _isFile;
		bool _isDir;

	public:
		File(std::wstring path);

		std::wstring getPath();
		std::wstring getName();

		bool isFile();
		bool isDirectory();

		std::vector<std::wstring> list();
		std::vector<std::wstring> list(std::wstring filter);
	};

}

#endif