#pragma once

#include <Windows.h>
#include "..\..\Exceptions\ClassFileException\ClassFileException.h"

#ifndef _CLASS_FILE_H_
#define _CLASS_FILE_H_

namespace explorer {

	class File {
	public:
		struct FileInfo {
			std::wstring Name;
			bool IsFile;
			bool IsDirectory;

			bool haveIcon;
			std::shared_ptr<Gdiplus::Bitmap> Icon;

			FileInfo(std::wstring name, bool isFile, bool isDir, HICON* icon);
		};

	private:
		std::wstring _path;
		std::wstring _fileName;

		bool _isFile;
		bool _isDir;

	public:
		File() = delete;
		File(std::wstring path);

		std::wstring getPrevDirection();
		std::wstring getDirection();
		std::wstring getName();

		bool isFile();
		bool isDirectory();

		std::vector<FileInfo> list();
		std::vector<FileInfo> list(std::wstring filter);

		static std::vector<std::pair<std::wstring, int>> getAllLogicalDrives();
	};

}

#endif