#pragma once

#include <Windows.h>
#include <map>
#include <set>
#include <string>
#include <memory>
#include <functional>

#include "..\Exceptions\ClassWindowException\ClassWindowException.h"
#include "..\Exceptions\ClassWindowClassException\ClassWindowClassException.h"

#ifndef _CLASS_WINDOW_H_
#define _CLASS_WINDOW_H_

namespace Explorer {

	class Window {
	private:
		static std::map<HWND, Window*> s_windowsMap;
		static std::wstring _className;

		std::map<int, std::function<LRESULT(HWND, WPARAM, LPARAM)>> _handlersMap;

		int _width, _hieght;
		int _pos_x, _pos_y;
		HWND _hWnd;
		HDC _hDC;

	protected:
		WNDCLASSEX _WndClass;
		std::wstring _windowName;

	public:
		Window(int pos_x, int pos_y);
		Window(int pos_x, int pos_y, int width, int hieght, bool show = true);
		Window(std::wstring name, int pos_x, int pos_y, int width, int hieght, bool show = true);

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


		LRESULT closeWindow(HWND hWnd, WPARAM wParam, LPARAM lParam);

		/*
		 *	Send message to all windows!
		 */
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	public:
		/*
		 *	Send std::bind(&YourWindow::hendler, this, ...);
		 *	"YourWindow "- child class Window;
		 *	"this" - your object;
		 *	"..." - params;
		 */
		void registerHendler(int message, std::function<LRESULT(HWND, WPARAM, LPARAM)>);
		/*
		 *	You should release this method in your class!
		 *	This method registering your window class.
		 */
		virtual ATOM m_registerClass();

	private:
		bool m_create();
		bool m_createWindow();
	};
}

#endif