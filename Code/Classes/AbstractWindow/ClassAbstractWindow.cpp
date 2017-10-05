#include "ClassAbstractWindow.h"

namespace Explorer {
	Window::Window()
	{

	}
	Window::Window(int width, int hieght, bool show = true)
	{

	}
	Window::Window(std::wstring name, int width, int hieght, bool show = true)
	{

	}

	int Window::getWidth() const { return _width; }
	int Window::getHieght() const { return _hieght; }
	HWND Window::getHWND() const { return _hWnd; }
	HDC Window::getHDC() const { return _hDC; }

	int Window::getPosX() const { return _pos_x; }
	int Window::getPosY() const { return _pos_y; }

	std::wstring Window::getClassName() const { return _className; }
	std::wstring Window::getWindowName() const { return _windowName; }
	void Window::setWindowName(std::wstring name)
	{
		_windowName = name;
	}

	void Window::resizeWindow(int width, int hieght, bool show)
	{
		MoveWindow(_hWnd, _pos_x, _pos_y, width, hieght, show);
	}
	void Window::resizeWindow(int pos_x, int pos_y, int width, int hieght, bool show)
	{
		MoveWindow(_hWnd, pos_x, pos_y, width, hieght, show);
	}
	void Window::showWindow(bool show)
	{
		ShowWindow(_hWnd, ((show) ? (SW_SHOW) : (SW_HIDE)));
	}

	HRESULT CALLBACK Window::WndProc(HWND hWnd, int msg, WPARAM wParam, LPARAM lParam)
	{
		return s_windowsMap[hWnd]->_handlersMap[msg](hWnd, wParam, lParam);
	}

	void Window::registerHendler(int message, std::function<HRESULT(HWND, WPARAM, LPARAM)> handler)
	{
		_handlersMap.insert(std::pair<int, std::function<HRESULT(HWND, WPARAM, LPARAM)>>(message, handler));
	}
}