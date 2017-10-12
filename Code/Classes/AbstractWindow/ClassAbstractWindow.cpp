#include "stdafx.h"
#include "ClassAbstractWindow.h"

namespace explorer {
	std::map<HWND, Window*> Window::s_windowsMap;
	std::wstring Window::_className = L"Explorer";
	ULONG_PTR Window::_gdiplusToken = 0;

	Window::Window() :
		_width(0), _hieght(0),
		_pos_x(0), _pos_y(0),
		_parent(nullptr),
		_thisWindowIsCreated(false)
	{
			Gdiplus::GdiplusStartupInput gdiplusStartupInput;
			Gdiplus::GdiplusStartup(&_gdiplusToken, &gdiplusStartupInput, NULL);

			m_registerHendler(WM_DESTROY, METHOD(&Window::closeWindow));
			//m_registerHendler(WM_PAINT, METHOD(&Window::paintWindow));
			m_registerHendler(WM_TIMER, METHOD(&Window::hoverWindow));
	}
	Window::~Window()
	{
		_graphics.~shared_ptr();

		s_windowsMap.erase(_hWnd);
		ReleaseDC(_hWnd, _hDC);
		DestroyWindow(_hWnd);

		if (_parent) {
			_parent->m_removeChildWindow(this);
		}

		if (s_windowsMap.size() == 0) {
			Gdiplus::GdiplusShutdown(_gdiplusToken);
			PostQuitMessage(0);
		}
	}

	int Window::getWidth() const { return _width; }
	int Window::getHieght() const { return _hieght; }
	HWND Window::getHWND() const { return _hWnd; }
	HDC Window::getHDC() const { return _hDC; }
	Window* Window::getParent() const { return _parent;  }

	int Window::getPosX() const { return _pos_x; }
	int Window::getPosY() const { return _pos_y; }
	int Window::getGlobalPosX() const
	{
		RECT rect;
		GetWindowRect(_hWnd, &rect);

		return rect.left;
	}
	int Window::getGlobalPosY() const
	{
		RECT rect;
		GetWindowRect(_hWnd, &rect);

		return rect.top;
	}

	std::wstring Window::getClassName() const { return _className; }
	std::wstring Window::getWindowName() const { return _windowName; }
	void Window::setWindowName(std::wstring name)
	{
		_windowName = name;
	}

	void Window::moveWindowPos(int x, int y, bool repaint)
	{
		MoveWindow(_hWnd, x, y, _width, _hieght, repaint);
	}
	void Window::resizeWindow(int width, int hieght, bool show)
	{
		resizeWindow(_pos_x, _pos_y, width, hieght, show);
	}
	void Window::resizeWindow(int pos_x, int pos_y, int width, int hieght, bool show)
	{
		//MessageBox(nullptr, std::wstring(L"Width: " + std::to_wstring(width) + L", Hieght: " + std::to_wstring(hieght)).c_str(), L"test", MB_OK);
		MoveWindow(_hWnd, pos_x, pos_y, width, hieght, show);
		_pos_x = pos_x;
		_pos_y = pos_y;
		_width = width;
		_hieght = hieght;

		_g_pos_X = getGlobalPosX();
		_g_pos_Y = getGlobalPosY();
		
		m_sendMessageForAllChildren(WM_SIZE, 0, 0);
	}
	void Window::minimizeWindow(bool hide)
	{
		ShowWindow(_hWnd, (hide) ? (SW_MINIMIZE) : (SW_SHOW));
	}
	void Window::redrawWindow(bool erase)
	{
		InvalidateRect(_hWnd, nullptr, erase);
		SendMessage(_hWnd, WM_PAINT, 0, 0);
	}

	void Window::showWindow(bool show)
	{
		ShowWindow(_hWnd, ((show) ? (SW_SHOW) : (SW_HIDE)));
	}
	void Window::setTimer(UINT timer_ID, UINT elapse)
	{
		SetTimer(_hWnd, timer_ID, elapse, nullptr);
	}
	void Window::killTimer(UINT timer_ID)
	{
		KillTimer(_hWnd, timer_ID);
	}

	void Window::getHoverMessages(bool activate)
	{
		if (activate) {
			killTimer(TIMER_UPP_HOVER);
			setTimer(TIMER_UPP_HOVER, 1);
		}
		else {
			killTimer(TIMER_UPP_HOVER);
		}
	}


	bool Window::create(int pos_x, int pos_y, int width, int hieght, bool show)
	{
		return create(L"Window", pos_x, pos_y, width, hieght, show);
	}
	bool Window::create(Window& parent, int pos_x, int pos_y, int width, int hieght, bool show )
	{
		return create(L"Window", parent, pos_x, pos_y, width, hieght, show);
	}
	bool Window::create(std::wstring name, int pos_x, int pos_y, int width, int hieght, bool show)
	{
		if (_thisWindowIsCreated) {
			return false;
		}

		_windowName = name;
		_pos_x = pos_x;
		_pos_y = pos_y;
		_width = width;
		_hieght = hieght;

		if (!m_create(nullptr, true)) {
			return false;
		}

		_parent = nullptr;

		_thisWindowIsCreated = true;
		return true;
	}
	bool Window::create(std::wstring name, Window& parent, int pos_x, int pos_y, int width, int hieght, bool show)
	{
		if (_thisWindowIsCreated) {
			return false;
		}

		_windowName = name;
		_pos_x = pos_x;
		_pos_y = pos_y;
		_width = width;
		_hieght = hieght;

		if (!m_create(&parent, show)) {
			return false;
		}

		_parent = &parent;
		parent.m_addChildWindow(this);

		_thisWindowIsCreated = true;
		return true;
	}

	void Window::m_addChildWindow(Window* child)
	{
		_childList.push_back(child);
	}
	void Window::m_removeChildWindow(Window* child)
	{
		_childList.remove(child);
	}


	LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (s_windowsMap.find(hWnd) != s_windowsMap.end()) {
			if (s_windowsMap[hWnd]->_handlersMap.find(msg) != s_windowsMap[hWnd]->_handlersMap.end()) {
				for (auto function : s_windowsMap[hWnd]->_handlersMap[msg]) {
					function(hWnd, wParam, lParam);
				}
				return 0;
			}
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	UINT Window::workWidthMessages()
	{
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return msg.wParam;
	}

	void Window::m_registerHendler(UINT message, Hendler method)
	{
		if (_handlersMap.find(message) == _handlersMap.end()) {
			_handlersMap.insert(std::pair<int, std::list<Hendler>>(message, std::list<Hendler>()));
		}
		_handlersMap[message].push_back(method);
	}
	void Window::m_sendMessageForParent(UINT message, WPARAM wParam, LPARAM lParam)
	{
		SendMessage(_parent->getHWND(), message, wParam, lParam);
	}
	void Window::m_sendMessageForAllChildren(UINT message, WPARAM wParam, LPARAM lParam)
	{
		for (Window* child : _childList) {
			SendMessage(child->getHWND(), message, wParam, lParam);
		}
	}
	void Window::m_sendMessageForChildren(std::wstring name, UINT message, WPARAM wParam, LPARAM lParam)
	{
		for (Window* child : _childList) {
			if (child->getWindowName() == name) {
				SendMessage(child->getHWND(), message, wParam, lParam);
			}
		}
	}
	void Window::m_sendMessageForChildren(Window* window, UINT message, WPARAM wParam, LPARAM lParam)
	{
		for (Window* child : _childList) {
			if (child == window) {
				SendMessage(child->getHWND(), message, wParam, lParam);
				break;
			}
		}
	}
	void Window::m_sendMessageForChildren(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		for (Window* child : _childList) {
			if (child->getHWND() == hWnd) {
				SendMessage(child->getHWND(), message, wParam, lParam);
				break;
			}
		}
	}

	bool Window::m_create(Window* parent, bool show)
	{
		try {
			m_registerClass();
			m_createWindow(parent);
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
			return false;
		}

		UpdateWindow(_hWnd);
		ShowWindow(_hWnd, (show ? SW_SHOW : SW_HIDE));

		_hDC = GetDC(_hWnd);
		_graphics = std::make_shared<Gdiplus::Graphics>(_hDC);

		_g_pos_X = getGlobalPosX();
		_g_pos_Y = getGlobalPosY();
		return true;
	}
	bool Window::m_createWindow(Window* parent)
	{
		long int style = (parent) ? (WS_CHILD) : (WS_POPUP);

		_hWnd = CreateWindow(
			_className.c_str(),
			_windowName.c_str(),
			style,
			_pos_x,
			_pos_y,
			_width,
			_hieght,
			((parent) ? (parent->getHWND()) : (nullptr)),
			nullptr,
			GetModuleHandle(0),
			nullptr
		);

		if (!_hWnd) {
			throw WindowException(L"Create Window " + _windowName + L" error!");
		}

		s_windowsMap.insert(std::pair<HWND, Window*>(_hWnd, this));
		SendMessage(_hWnd, WM_CREATE, 0, 0);
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


	
	void Window::closeWindow(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		s_windowsMap.erase(_hWnd);
		if (s_windowsMap.size() == 0) {
			PostQuitMessage(0);
		}
	}
	void Window::hoverWindow(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		if (wParam == TIMER_UPP_HOVER) {
			//bool windowStatus = _hWnd == GetForegroundWindow();

			POINT point;
			GetCursorPos(&point);

			if ((point.x >= _g_pos_X && point.x <= _g_pos_X + getWidth())
				&& (point.y >= _g_pos_Y && point.y <= _g_pos_Y + getHieght())) {
				if (!_hoverStatus) {
					_hoverStatus = true;
					SendMessage(_hWnd, WM_MOUSEHOVER, 1, 0);
				}
			}
			else if (_hoverStatus) {
				_hoverStatus = false;
				SendMessage(_hWnd, WM_MOUSEHOVER, 0, 0);
			}
		}
	}
}