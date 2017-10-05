#pragma once

#include <Windows.h>
#include <map>
#include <set>
#include <string>
#include <memory>
#include <functional>

#ifndef _CLASS_MAIN_WINDOW_H_
#define _CLASS_MAIN_WINDOW_H_

namespace Explorer {

	class Window {
	private:
		static std::map<HWND, std::shared_ptr<Window>> s_windowsMap;

		std::map<int, std::function<HRESULT(HWND, WPARAM, LPARAM)>> _handlersMap;

		WNDCLASSEX _WndClass;
		std::wstring _className;
		std::wstring _windowName;

		int _width, _hieght;
		int _pos_x, _pos_y;
		HWND _hWnd;
		HDC _hDC;

	public:
		Window();
		Window(int width, int hieght, bool show = true);
		Window(std::wstring name, int width, int hieght, bool show = true);

		int getWidth() const;
		int getHieght() const;
		HWND getHWND() const;
		HDC getHDC() const;

		int getPosX() const;
		int getPosY() const;
		
		std::wstring getClassName() const;
		std::wstring getWindowName() const;
		void setWindowName(std::wstring name);

		void resizeWindow(int width, int hieght, bool show);
		void resizeWindow(int pos_x, int pos_y, int width, int hieght, bool show);

		void showWindow(bool show);

		/*
		 *	Send message to all windows!
		 */
		static HRESULT CALLBACK WndProc(HWND hWnd, int msg, WPARAM wParam, LPARAM lParam);

	protected:
		/*
		 *	Send std::bind(&YourWindow::hendler, this, ...);
		 *	"YourWindow "- child class Window;
		 *	"this" - your object;
		 *	"..." - params;
		 */
		void registerHendler(int message, std::function<HRESULT(HWND, WPARAM, LPARAM)>);
		/*
		 *	You should release this method in your class!
		 *	This method registering your window class.
		 */
		virtual ATOM m_registerClass() = 0;
	};
}

#endif