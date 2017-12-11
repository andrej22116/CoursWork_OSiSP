#pragma once

#ifndef _CLASS_SYSTEM_H_
#define _CLASS_SYSTEM_H_

namespace explorer {
	class Window;

	class System {
	private:
		System() {};
		static Gdiplus::Color _SystemColor;

		friend Window;

	public:
		static int GetScreenWidth();
		static int GetScreenHeight();

		static const Gdiplus::Color& GetSystemColor();
		// return system MAJOR and system MINOR versions 
		static std::pair<int, int> GetSystemVersion();

	private:
		static void s_updateSystemColor();
	};

}

#endif