#pragma once

#include <Windows.h>
#include <string>

#ifndef _CLASS_MAIN_WINDOW_H_
#define _CLASS_MAIN_WINDOW_H_

namespace Explorer {
	class Window {
	private:
		static WNDCLASSEX WndClass;

		int _width, _hieght;
		HWND _hWnd;
		HDC _hDC;

	public:
		int getWidth();
		int getHieght();
		HWND getHWND();
		HDC getHDC();

		std::string getClassName();

		void resizeWindow(int width, int hieght, bool show);
		void showWindow(bool show);

		static HRESULT CALLBACK WndProc(HWND hWnd, int msg, WPARAM wParam, LPARAM lParam);

	private:
		virtual HRESULT CALLBACK m_WndProc(HWND hWnd, int msg, WPARAM wParam, LPARAM lParam) = 0;
		virtual ATOM m_registerClass() = 0;
	};
}

#endif
