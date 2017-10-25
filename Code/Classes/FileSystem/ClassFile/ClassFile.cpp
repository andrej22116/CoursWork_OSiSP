#include "stdafx.h"
#include "ClassFile.h"

namespace explorer {

	File::File(std::wstring path)
	{
		_path = path;
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

}