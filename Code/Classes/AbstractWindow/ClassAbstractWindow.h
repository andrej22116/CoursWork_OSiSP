#pragma once

#include <Windows.h>
#include <map>
#include <list>
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

		Window* _parent;
		std::list<Window*> _childList;

		std::map<int, std::list<std::function<LRESULT(HWND, WPARAM, LPARAM)>>> _handlersMap;

		int _width, _hieght;
		int _pos_x, _pos_y;
		HWND _hWnd;
		HDC _hDC;

		WNDCLASSEX _WndClass;
		std::wstring _windowName;

		bool _thisWindowIsCreated;

	public:
		Window();
		~Window();

		bool create(int pos_x, int pos_y, int width, int hieght, bool show = true);
		bool create(Window& parent, int pos_x, int pos_y, int width, int hieght, bool show = true);
		bool create(std::wstring name, int pos_x, int pos_y, int width, int hieght, bool show = true);
		bool create(std::wstring name, Window& parent, int pos_x, int pos_y, int width, int hieght, bool show = true);

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
		static UINT workWidthMessages();

	protected:
		/*
		 *	Send std::bind(&YourWindow::hendler, this, ...);
		 *	"YourWindow "- child class Window;
		 *	"this" - your object;
		 *	"..." - params;
		 */
		void m_registerHendler(int message, std::function<LRESULT(HWND, WPARAM, LPARAM)>);
	
	private:
		ATOM m_registerClass();
		bool m_create(Window* parent = nullptr, bool show = true);
		bool m_createWindow(Window* parent = nullptr);
		void m_addChildWindow(Window* child);
		void m_removeChildWindow(Window* child);
	};
}

#endif