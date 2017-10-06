#include "ClassAbstractWindow.h"

namespace Explorer {
	std::map<HWND, Window*> Window::s_windowsMap;
	std::wstring Window::_className = L"Explorer";

	Window::Window(int pos_x, int pos_y) :
		_pos_x(pos_x),
		_pos_y(pos_y),
		_width(800),
		_hieght(600)
	{
		_windowName = L"Window";
		registerHendler(WM_DESTROY, std::bind(&Window::closeWindow, this, (HWND)1, (WPARAM)2, (LPARAM)3));
		m_create();
		UpdateWindow(_hWnd);
		ShowWindow(_hWnd, SW_SHOW);
	}
	Window::Window(int pos_x, int pos_y, int width, int hieght, bool show) :
		_pos_x(pos_x),
		_pos_y(pos_y),
		_width(width),
		_hieght(hieght)
	{
		_windowName = L"Window";
		registerHendler(WM_DESTROY, std::bind(&Window::closeWindow, this, (HWND)1, (WPARAM)2, (LPARAM)3));
		m_create();
		UpdateWindow(_hWnd);
		ShowWindow(_hWnd, (show ? SW_SHOW : SW_HIDE));
	}
	Window::Window(std::wstring name, int pos_x, int pos_y, int width, int hieght, bool show) :
		_pos_x(pos_x),
		_pos_y(pos_y),
		_width(width),
		_hieght(hieght)
	{
		_windowName = name;
		registerHendler(WM_DESTROY, std::bind(&Window::closeWindow, this, (HWND)1, (WPARAM)2, (LPARAM)3));
		m_create();
		UpdateWindow(_hWnd);
		ShowWindow(_hWnd, (show ? SW_SHOW : SW_HIDE));
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


	LRESULT Window::closeWindow(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		s_windowsMap.erase(_hWnd);
		if (s_windowsMap.size() == 0) {
			PostQuitMessage(0);
		}
		return 0;
	}

	LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (s_windowsMap.find(hWnd) != s_windowsMap.end()) {
			if (s_windowsMap[hWnd]->_handlersMap.find(msg) != s_windowsMap[hWnd]->_handlersMap.end()) {
				return s_windowsMap[hWnd]->_handlersMap[msg](hWnd, wParam, lParam);
			}
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	void Window::registerHendler(int message, std::function<LRESULT(HWND, WPARAM, LPARAM)> handler)
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
			return false;
		}
		catch (WindowException ex) {
			ex.showMsg();
			return false;
		}
		catch (...) {

		}
		return true;
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

		s_windowsMap.insert(std::pair<HWND, Window*>(_hWnd, this));
		return true;
	}




	ATOM Window::m_registerClass() {
		WNDCLASS wndclass;
		if (GetClassInfo(GetModuleHandle(0), _className.c_str(), &wndclass)) {
			return 1;
		}

		_WndClass.cbSize = sizeof(_WndClass);
		_WndClass.style = 0;
		_WndClass.lpfnWndProc = WndProc;
		_WndClass.cbClsExtra = 0;
		_WndClass.cbWndExtra = 0;
		_WndClass.hInstance = GetModuleHandle(NULL);
		_WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		_WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		_WndClass.hbrBackground = (HBRUSH)GetStockObject(0);
		_WndClass.lpszMenuName = NULL;
		_WndClass.lpszClassName = _className.c_str();
		_WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		if (!RegisterClassEx(&_WndClass)) {
			throw WindowClassException();
		}
		return 1;
	}
}