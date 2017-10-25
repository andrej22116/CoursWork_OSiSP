#include "stdafx.h"
#include "ClassFile.h"

namespace explorer {

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
		}
		else {
			_isFile = true;
		}
	}

	std::wstring File::getPath()
	{
		return L"";
	}
	std::wstring File::getName()
	{
		return L"";
	}

	bool File::isFile()
	{
		return true;
	}
	bool File::isDirectory()
	{
		return false;
	}

	std::vector<std::wstring> File::list()
	{
		return std::vector<std::wstring>();
	}
	std::vector<std::wstring> File::list(std::wstring filter)
	{
		return std::vector<std::wstring>();
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