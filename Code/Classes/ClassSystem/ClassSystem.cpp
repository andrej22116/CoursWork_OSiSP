#include "stdafx.h"
#include "ClassSystem.h"

namespace explorer {
	Gdiplus::Color System::_SystemColor = Gdiplus::Color();


	int System::GetScreenWidth()
	{
		return GetSystemMetrics(SM_CXSCREEN);
	}
	int System::GetScreenHeight()
	{
		return GetSystemMetrics(SM_CYSCREEN);
	}

	const Gdiplus::Color& System::GetSystemColor()
	{
		return _SystemColor;
	}

	std::pair<int, int> System::GetSystemVersion()
	{
		OSVERSIONINFOEX version;
		ZeroMemory(&version, sizeof(OSVERSIONINFOEX));
		version.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

		GetVersionEx((OSVERSIONINFO*)(&version));

		return std::pair<int, int>(version.dwMajorVersion, version.dwMinorVersion);
	}


	void System::s_updateSystemColor()
	{
		DWORD color = 0;
		BOOL opaque = FALSE;

		HRESULT hr = DwmGetColorizationColor(&color, &opaque);
		if (SUCCEEDED(hr)) {
			_SystemColor.SetValue(Gdiplus::ARGB(color));
			//_systemColor = Gdiplus::Color(254, _systemColor.GetRed(), _systemColor.GetGreen(), _systemColor.GetBlue());

		}
	}

}