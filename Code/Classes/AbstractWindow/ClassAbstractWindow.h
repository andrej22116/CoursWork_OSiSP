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

		std::map<int, std::function<LRESULT(HWND, WPARAM, LPARAM)>> _handlersMap;

		int _width, _hieght;
		int _pos_x, _pos_y;
		HWND _hWnd;
		HDC _hDC;

	protected:
		WNDCLASSEX _WndClass;
		std::wstring _windowName;

		Window* _parent;
		std::list<Window*> _childList;

	public:
		Window(int pos_x, int pos_y);
		Window(int pos_x, int pos_y, int width, int hieght, bool show = true);
		Window(std::wstring name, int pos_x, int pos_y, int width, int hieght, bool show = true);
		~Window();

		bool create(int pos_x, int pos_y, int width, int hieght, bool show = true);
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

	protected:
		/*
		 *	Send std::bind(&YourWindow::hendler, this, ...);
		 *	"YourWindow "- child class Window;
		 *	"this" - your object;
		 *	"..." - params;
		 */
		void registerHendler(int message, std::function<LRESULT(HWND, WPARAM, LPARAM)>);
		void addChildWindow(Window* child);
		void removeChildWindow(Window* child);
	
	private:
		ATOM m_registerClass();
		bool m_create(Window* parent = nullptr);
		bool m_createWindow(Window* parent = nullptr);
	};
}

#endif