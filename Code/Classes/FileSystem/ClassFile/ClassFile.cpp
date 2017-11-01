#include "stdafx.h"
#include "ClassFile.h"

namespace explorer {

	File::FileInfo::FileInfo(std::wstring name, bool isFile, bool isDir, HICON* icon)
	{
		Name = name;
		IsFile = isFile;
		IsDirectory = isDir;

		if (icon) {
			haveIcon = true;
			Icon = std::make_shared<Gdiplus::Bitmap>(*icon);
		}
	}

	File::File(std::wstring path)
	{
		_isDir = false;
		_isFile = false;

		_path = path;
		DWORD Attributes = GetFileAttributes(_path.c_str());

		if (ERROR_FILE_NOT_FOUND == GetLastError()) {
			throw FileException(L"File exception: file \"" + _path + L"\" not found!");
		}
		else if (Attributes & FILE_ATTRIBUTE_DIRECTORY) {
			_isDir = true;
			if (_path[_path.size() - 1] != '\\') {
				_path += '\\';
			}
		}
		else {
			_isFile = true;
		}
	}

	std::wstring File::getPrevDirection()
	{
		std::wstring prevDir;

		auto pos = _path.find_last_of('\\');
		pos = _path.find_last_of('\\', pos - 1);

		prevDir = _path.substr(0, pos + 1);
		return prevDir;
	}
	std::wstring File::getDirection()
	{
		if (_isDir) {
			return _path;
		}
		else {
			std::wstring path;
			auto position = _path.find_last_of('\\');

			path = _path.substr(0, position + 1);
			return path;
		}
	}
	std::wstring File::getName()
	{
		std::wstring path;
		auto position = _path.find_last_of('\\');
		path = _path.substr(position + 1, _path.size());
		return path;
	}

	bool File::isFile()
	{
		return _isFile;
	}
	bool File::isDirectory()
	{
		return _isDir;
	}

	std::vector<File::FileInfo> File::list()
	{
		return list(std::wstring(L"*"));
	}
	std::vector<File::FileInfo> File::list(std::wstring filter)
	{
		HANDLE hFind;
		WIN32_FIND_DATA findData;

		std::wstring find = _path;
		find += filter;

		hFind = FindFirstFile(find.c_str(), &findData);
		if (INVALID_HANDLE_VALUE == hFind) {
			throw FileException(L"File exception: Find error!");
		}


		std::vector<std::wstring> filelist;
		do {
			filelist.push_back(findData.cFileName);
		} while (FindNextFile(hFind, &findData));

		FindClose(hFind);

		std::vector<FileInfo> result;
		for (auto file : filelist) {
			bool isDir = false;

			std::wstring full_path = _path + file;
			std::unique_ptr<FileInfo> fInfo;

			DWORD atributes = GetFileAttributes(full_path.c_str());
			if (atributes & FILE_ATTRIBUTE_DIRECTORY) {
				isDir = true;
				fInfo = std::make_unique<FileInfo>(file, !isDir, isDir, nullptr);
			}
			else {
				SHFILEINFO info;
				SHGetFileInfo(full_path.c_str(),
					FILE_ATTRIBUTE_NORMAL,
					&info,
					sizeof(SHFILEINFO),
					SHGFI_USEFILEATTRIBUTES | SHGFI_ICON | SHGFI_SMALLICON | SHGFI_SHELLICONSIZE
				);
				fInfo = std::make_unique<FileInfo>(file, !isDir, isDir, &info.hIcon);
				DestroyIcon(info.hIcon);
			}

			result.push_back(*fInfo);
		}

		return result;
	}



	std::vector<std::pair<std::wstring, int>> File::getAllLogicalDrives()
	{
		std::vector<std::pair<std::wstring, int>> vector;

		WCHAR drivers[128];
		GetLogicalDriveStringsW(128, drivers);

		WCHAR* iter = drivers;
		while (*iter) {
			vector.push_back(std::pair<std::wstring, int>(iter, 0));
			iter = iter + wcslen(iter) + 1;
		}

		for (auto& driver : vector) {
			driver.second = GetDriveTypeW(driver.first.c_str());
		}

		return vector;
	}
}