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

	std::vector<std::wstring> File::list()
	{
		return list(std::wstring(L"*"));
	}
	std::vector<std::wstring> File::list(std::wstring filter)
	{
		HANDLE hFind;
		WIN32_FIND_DATA findData;

		std::wstring find = _path;
		find += filter;

		hFind = FindFirstFile(find.c_str(), &findData);
		if (INVALID_HANDLE_VALUE == hFind) {
			throw FileException(L"File exception: Find error!");
		}


		std::vector<std::wstring> result;
		do {
			result.push_back(findData.cFileName);
		} while (FindNextFile(hFind, &findData));

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