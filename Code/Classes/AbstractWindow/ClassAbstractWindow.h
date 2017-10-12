#pragma once

#include "..\Exceptions\ClassWindowException\ClassWindowException.h"
#include "..\Exceptions\ClassWindowClassException\ClassWindowClassException.h"

#ifndef _CLASS_WINDOW_H_
#define _CLASS_WINDOW_H_

#define METHOD(method) (std::bind((method), this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))

namespace explorer {
	class Window;

	typedef std::function<void(HWND, WPARAM, LPARAM)> Hendler;

	class Window {
	private:
		static std::map<HWND, Window*> s_windowsMap;
		static std::wstring _className;
		static ULONG_PTR _gdiplusToken;
		static const UINT TIMER_UPP_HOVER = 10000;

		Window* _parent;
		std::list<Window*> _childList;

		std::map<int, std::list<Hendler>> _handlersMap;

		int _width, _hieght;
		int _pos_x, _pos_y;
		int _g_pos_X, _g_pos_Y;
		HWND _hWnd;
		HDC _hDC;

		WNDCLASSEX _WndClass;
		std::wstring _windowName;

		bool _thisWindowIsCreated;
		bool _hoverStatus;

	protected:
		std::shared_ptr<Gdiplus::Graphics> _graphics;

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
		Window* getParent() const;

		int getPosX() const;
		int getPosY() const;
		int getGlobalPosX() const;
		int getGlobalPosY() const;
		
		std::wstring getClassName() const;
		std::wstring getWindowName() const;
		void minimizeWindow(bool hide);
		void setWindowName(std::wstring name);

		void moveWindowPos(int x, int y, bool repaint = false);
		void resizeWindow(int width, int hieght, bool show);
		void resizeWindow(int pos_x, int pos_y, int width, int hieght, bool show);
		void redrawWindow(bool erase);

		void showWindow(bool show);
		void setTimer(UINT timer_ID, UINT elapse);
		void killTimer(UINT timer_ID);

		void getHoverMessages(bool activate);

		/* Handlers */
		void closeWindow(HWND hWnd, WPARAM wParam, LPARAM lParam);
		void hoverWindow(HWND hWnd, WPARAM wParam, LPARAM lParam);

		/*
		 *	Send message to all windows!
		 */
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static UINT workWidthMessages();

	protected:
		/*
		 *	message, METHOD( & your_method );
		 */
		void m_registerHendler(UINT message, Hendler method);
		void m_sendMessageForParent(UINT message, WPARAM wParam, LPARAM lParam);
		void m_sendMessageForAllChildren(UINT message, WPARAM wParam, LPARAM lParam);
		void m_sendMessageForChildren(std::wstring name, UINT message, WPARAM wParam, LPARAM lParam);
		void m_sendMessageForChildren(Window* window, UINT message, WPARAM wParam, LPARAM lParam);
		void m_sendMessageForChildren(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	private:
		ATOM m_registerClass();
		bool m_create(Window* parent = nullptr, bool show = true);
		bool m_createWindow(Window* parent = nullptr);
		void m_addChildWindow(Window* child);
		void m_removeChildWindow(Window* child);
	};
}

#endif