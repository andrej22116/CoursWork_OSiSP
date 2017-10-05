#include "ClassAbstractWindow.h"

namespace Explorer {
	Window::Window(int pos_x, int pos_y) :
		_windowName(L"Window"),
		_width(800),
		_hieght(600)
	{
		m_create();
	}
	Window::Window(int pos_x, int pos_y, int width, int hieght, bool show = true) :
		_windowName(L"Window"),
		_width(width),
		_hieght(hieght)
	{
		m_create();
	}
	Window::Window(std::wstring name, int pos_x, int pos_y, int width, int hieght, bool show = true) :
		_windowName(name.c_str()),
		_width(width),
		_hieght(hieght)
	{
		m_create();
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


	HRESULT Window::closeWindow(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		s_windowsMap.erase(hWnd);
	}

	HRESULT CALLBACK Window::WndProc(HWND hWnd, int msg, WPARAM wParam, LPARAM lParam)
	{
		return s_windowsMap[hWnd]->_handlersMap[msg](hWnd, wParam, lParam);
	}

	void Window::registerHendler(int message, std::function<HRESULT(HWND, WPARAM, LPARAM)> handler)
	{
		_handlersMap.insert(std::pair<int, std::function<HRESULT(HWND, WPARAM, LPARAM)>>(message, handler));
	}

	bool Window::m_create()
	{
		try {
			m_registerClass();
			m_createWindow();
		}
		catch (WindowClassException ex) {
			ex.showMsg();
		}
		catch (WindowException ex) {
			ex.showMsg();
		}
	}

	bool Window::m_createWindow()
	{
		_hWnd = CreateWindow(
			_className.c_str(),
			_windowName.c_str(),
			WS_OVERLAPPEDWINDOW,
			_pos_x,
			_pos_y,
			_width,
			_hieght,
			nullptr,
			nullptr,
			GetModuleHandle(0),
			nullptr
		);

		if (!_hWnd) {
			throw WindowException(L"Create Window " + _windowName + L" error!");
		}
	}
}