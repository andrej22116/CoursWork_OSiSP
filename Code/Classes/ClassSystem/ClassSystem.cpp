#include "stdafx.h"
#include "ClassSystem.h"

namespace explorer {
	Gdiplus::Color System::_SystemColor = Gdiplus::Color();
	bool System::_haveBattary = false;


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

	bool System::deviceHaveBattay()
	{
		SYSTEM_POWER_STATUS sps;
		if (GetSystemPowerStatus(&sps)) {
			_haveBattary = true;
			if (sps.BatteryFlag == 255 || sps.BatteryFlag == 128) {
				_haveBattary = false;
			}
		}
		else {
			_haveBattary = false;
		}
		return _haveBattary;
	}
	bool System::batteryCharging()
	{
		if (_haveBattary) {
			SYSTEM_POWER_STATUS sps;
			if (GetSystemPowerStatus(&sps)) {
				return (bool)sps.ACLineStatus;
			}
		}
	}
	int System::getBatteryStatus()
	{
		if (_haveBattary) {
			SYSTEM_POWER_STATUS sps;
			if (GetSystemPowerStatus(&sps)) {
				return (int)sps.BatteryLifePercent;
			}
		}
	}

}