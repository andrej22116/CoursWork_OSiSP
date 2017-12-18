#include "stdafx.h"
#include "ClassAbstractWindow.h"

namespace explorer {
	std::map<HWND, Window*> Window::s_windowsMap;
	std::wstring Window::_className = L"Explorer";
	ULONG_PTR Window::_gdiplusToken = 0;

	Window::Window() :
		_width(0), _hieght(0), _oldWidth(0), _oldHieght(0),
		_minWidth(50), _minHieght(15),
		_pos_x(0), _pos_y(0),
		_borderSize(3),
		_parent(nullptr),
		_thisWindowIsCreated(false),
		_moveWhenParentResiz_X(false), _moveWhenParentResiz_Y(false),
		_resizeWhenParentResize_Width(false), _resizeWhenParentResize_Height(false),
		_canBeResize_top(false), _canBeResize_bottom(false),
		_canBeResize_left(false), _canBeResize_right(false),

		_resizing(false),
		_redrawWhereResizing(true),

		_scrollbarHorizontalStatus(0),
		_scrollbarVerticalStatus(0),
		_scrollbarHorizontalStepSize(0),
		_scrollbarVerticalStepSize(0),

		_haveHeader(false)
	{
			Gdiplus::GdiplusStartupInput gdiplusStartupInput;
			Gdiplus::GdiplusStartup(&_gdiplusToken, &gdiplusStartupInput, NULL);
			m_registerTimerHendler(METHOD(&Window::timerCheckHoverWindow));
			registerHendler(METHOD(&Window::abstratcWindowScrollIventHandler));
	}
	Window::~Window()
	{
		s_windowsMap.erase(_hWnd);
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
	void Window::setWindowName(std::wstring& name)
	{
		_windowName = name;
		SetWindowText(_hWnd, _windowName.c_str());
	}
	void Window::setResizeWhenParentResizeing(bool resize_width, bool resize_height)
	{
		_resizeWhenParentResize_Width = resize_width;
		_resizeWhenParentResize_Height = resize_height;
	}
	void Window::setMoveWhenParentResizeing(bool move_x, bool move_y)
	{
		_moveWhenParentResiz_X = move_x;
		_moveWhenParentResiz_Y = move_y;
	}
	void Window::setBorderSize(int size)
	{
		if (size < 0) {
			return;
		}
		_borderSize = size;
	}
	void Window::setResizebleAll(bool left, bool right, bool top, bool bottom)
	{
		_canBeResize_top = top;
		_canBeResize_left = left;
		_canBeResize_right = right;
		_canBeResize_bottom = bottom;
	}
	void Window::setResizebleTop(bool top)
	{
		_canBeResize_top = top;
	}
	void Window::setResizebleLeft(bool left)
	{
		_canBeResize_left = left;
	}
	void Window::setResizebleRight(bool right)
	{
		_canBeResize_right = right;
	}
	void Window::setResizebleBottom(bool bottom)
	{
		_canBeResize_bottom = bottom;
	}
	void Window::setMinSize(int width, int height)
	{
		_minWidth = width;
		_minHieght = height;
	}
	void Window::setMaxSize(int width, int height)
	{
		_maxWidth = width;
		_maxHieght = height;
	}
	void Window::setHeader(bool header)
	{
		_haveHeader = header;
	}

	void Window::setLock(bool lock)
	{
		_isLocked = lock;
	}
	bool Window::isLocked()
	{
		return _isLocked;
	}


	void Window::moveWindowPos(int x, int y, bool repaint)
	{
		_pos_x = x;
		_pos_y = y;

		MoveWindow(_hWnd, x, y, _width, _hieght, repaint);
		//m_sendMessageForAllChildren(WM_SIZE, 0, 0);
	}
	void Window::resizeWindow(int width, int hieght, bool show)
	{
		resizeWindow(_pos_x, _pos_y, width, hieght, show);
	}
	void Window::resizeWindow(int pos_x, int pos_y, int width, int hieght, bool show)
	{
		//MessageBox(nullptr, std::wstring(L"Width: " + std::to_wstring(width) + L", Hieght: " + std::to_wstring(hieght)).c_str(), L"test", MB_OK);
		_oldWidth = _width;
		_oldHieght = _hieght;

		_pos_x = pos_x;
		_pos_y = pos_y;
		_width = width;
		_hieght = hieght;

		_g_pos_X = getGlobalPosX();
		_g_pos_Y = getGlobalPosY();
		
		m_calculateNewPositionWindowIfParentResize();
		m_calculateNewSizeWindowIfParentResize();
		MoveWindow(_hWnd, pos_x, pos_y, width, hieght, show);
		//SetWindowPos(_hWnd, (HWND)1, pos_x, pos_y, width, hieght, SWP_SHOWWINDOW);
		redrawWindow(false);
		//m_sendMessageForAllChildren(WM_SIZE, 0, 0);
	}
	void Window::minimizeWindow(bool hide)
	{
		ShowWindow(_hWnd, (hide) ? (SW_MINIMIZE) : (SW_SHOW));
	}
	void Window::redrawWindow(bool erase)
	{
		RedrawWindow(_hWnd, NULL, NULL, 
			RDW_INVALIDATE 
			| (erase ? RDW_ERASE : RDW_NOERASE)
			| RDW_INTERNALPAINT 
			| RDW_UPDATENOW 
			| RDW_ALLCHILDREN);
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

	void Window::setRenderBufferSize(int width, int height)
	{
		if (width < _width) {
			width = _width;
		}
		if (height < _hieght) {
			height = _hieght;
		}
		_renderBuffer->resizeBuffer(width, height);
	}
	void Window::activateVerticalScrollbarIfRenderBufferHeightMoreThanHeightWindow(bool activate)
	{
		_scrollbarVertical_IsEnable = activate;
	}
	void Window::activateHorizontalScrollbarIfRenderBufferWidthMoreThanWidthWindow(bool activate)
	{
		_scrollbarHorizontal_IsEnable = activate;
	}
	void Window::setHorizontalSckrollStepSize(int horizontalStepSize)
	{
		_scrollbarHorizontalStepSize = horizontalStepSize;
	}
	void Window::setVerticalSckrollStepSize(int verticalStepSize)
	{
		_scrollbarVerticalStepSize = verticalStepSize;
	}
	void Window::setHorizontalSckrollStatus(int status)
	{
		_scrollbarHorizontalStatus = status;
	}
	void Window::setVerticalSckrollStatus(int status)
	{
		_scrollbarVerticalStatus = status;
	}
	int Window::getHorizontalSckrollStatus()
	{
		return _scrollbarHorizontalStatus;
	}
	int Window::getVerticalSckrollStatus()
	{
		return _scrollbarVerticalStatus;
	}


	bool Window::create(int pos_x, int pos_y, int width, int hieght, bool show)
	{
		return create(std::wstring(L"Window"), pos_x, pos_y, width, hieght, show);
	}
	bool Window::create(Window& parent, int pos_x, int pos_y, int width, int hieght, bool show )
	{
		return create(std::wstring(L"Window"), parent, pos_x, pos_y, width, hieght, show);
	}
	bool Window::create(std::wstring& name, int pos_x, int pos_y, int width, int hieght, bool show)
	{
		if (_thisWindowIsCreated) {
			return false;
		}

		_windowName = name;
		_pos_x = pos_x;
		_pos_y = pos_y;
		_oldWidth = _width = width;
		_oldHieght = _hieght = hieght;

		if (!m_create(nullptr, true)) {
			return false;
		}

		_parent = nullptr;

		_thisWindowIsCreated = true;
		return true;
	}
	bool Window::create(std::wstring& name, Window& parent, int pos_x, int pos_y, int width, int hieght, bool show)
	{
		if (_thisWindowIsCreated) {
			return false;
		}

		_windowName = name;
		_pos_x = pos_x;
		_pos_y = pos_y;
		_oldWidth = _width = width;
		_oldHieght = _hieght = hieght;

		if (!m_create(&parent, show)) {
			return false;
		}

		_parent = &parent;
		parent.m_addChildWindow(this);

		_thisWindowIsCreated = true;
		return true;
	}

	void Window::destroy()
	{
		if (_thisWindowIsCreated) {
			SendMessage(_hWnd, WM_CLOSE, 0, 0);
			_thisWindowIsCreated = false;
			s_windowsMap.erase(_hWnd);
		}
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
			Window* window = s_windowsMap[hWnd];
			switch (msg) {
			case WM_CREATE: { 
				window->eventCreateWindow();

				System::s_updateSystemColor();
			} break;
			case WM_GETMINMAXINFO: {
				m_WndProcHandler_GetMinMaxInfo(window, hWnd, msg, wParam, lParam);
			} break;
			case WM_SIZING: {
				m_WndProcHandler_Sizing(window, hWnd, msg, wParam, lParam);
				return DefWindowProc(hWnd, msg, wParam, lParam);
			} break;
			case WM_ERASEBKGND: {} break;
			case WM_PAINT: {
				m_WndProcHandler_Paint(window, hWnd, msg, wParam, lParam);
			} break;
			case WM_MOVE: {
				m_WndProcHandler_Move(window, hWnd, msg, wParam, lParam);
			} break;
			case WM_SIZE: {
				m_WndProcHandler_Size(window, hWnd, msg, wParam, lParam);
			} break;
			case WM_MOUSEMOVE: {
				m_WndProcHandler_MouseMove(window, hWnd, msg, wParam, lParam);
			} break;
			case WM_LBUTTONDOWN: case WM_LBUTTONUP: case WM_LBUTTONDBLCLK:
			case WM_RBUTTONDOWN: case WM_RBUTTONUP: case WM_RBUTTONDBLCLK:
			case WM_MBUTTONDOWN: case WM_MBUTTONUP: case WM_MBUTTONDBLCLK: {
				m_WndProcHandler_MouseButtons(window, hWnd, msg, wParam, lParam);
			} break;
			case WM_KEYDOWN: case WM_KEYUP: case WM_CHAR: {
				m_WndProcHandler_Keyboard(window, hWnd, msg, wParam, lParam);
			} break;
			case WM_MOUSEHOVER: {
				m_WndProcHandler_MouseHover(window, hWnd, msg, wParam, lParam);
			} break;
			case WM_MOUSEWHEEL: {
				m_WndProcHandler_MouseWheel(window, hWnd, msg, wParam, lParam);
			} break;
			case WM_TIMER: {
				m_WndProcHandler_Timer(window, hWnd, msg, wParam, lParam);
			} break;
			case WM_DESTROY: { window->eventCloseWindow(); } break;
			case WM_NCCALCSIZE: {		
				return m_WndProcHandler_NcCalcSize(window, hWnd, msg, wParam, lParam);
			} break;
			case WM_NCHITTEST: {
				return m_WndProcHandler_NcHitTest(window, hWnd, msg, wParam, lParam);
			} break;
			case WM_NCLBUTTONDOWN: {
				window->_resizing = true;
				return DefWindowProc(hWnd, msg, wParam, lParam);
			} break;
			case WM_NCLBUTTONUP: {
				window->_resizing = false;
				return DefWindowProc(hWnd, msg, wParam, lParam);
			} break;

			case WM_VSCROLL: {
				SCROLLINFO vscroll;
				vscroll.cbSize = sizeof(SCROLLINFO);
				vscroll.fMask = SIF_RANGE | SIF_POS | SIF_TRACKPOS;
				GetScrollInfo(hWnd, SB_VERT, &vscroll);

				RECT rc;
				GetClientRect(hWnd, &rc);

				int verticalScroll = 0;
				switch (LOWORD(wParam))
				{
				case SB_LINEDOWN: case SB_PAGEDOWN: {
					int k = (LOWORD(wParam) == SB_LINEDOWN) ? 10 : rc.bottom;
					verticalScroll = vscroll.nMax - vscroll.nPos;
					if (verticalScroll > k) {
						verticalScroll = k;
					}
					vscroll.nPos = vscroll.nPos + verticalScroll;
				} break;

				case SB_LINEUP: case SB_PAGEUP: {
					int k = (LOWORD(wParam) == SB_LINEUP) ? 10 : rc.bottom;
					verticalScroll = vscroll.nPos - vscroll.nMin;
					if (verticalScroll > k) {
						verticalScroll = k;
					}
					verticalScroll = -verticalScroll;
					vscroll.nPos = vscroll.nPos + verticalScroll;
				} break;
				case SB_THUMBTRACK: {
					verticalScroll = vscroll.nTrackPos - vscroll.nPos;
					vscroll.nPos = vscroll.nTrackPos;
				} break;
				}
				vscroll.cbSize = sizeof(SCROLLINFO);
				vscroll.fMask = SIF_POS;

				ScrollWindowEx(hWnd, 0, -verticalScroll, NULL, NULL, NULL, NULL, SW_ERASE);
				if (verticalScroll > 0) {
					rc.top = rc.bottom - verticalScroll;
				}
				else {
					rc.bottom = rc.top - verticalScroll;
				}
				SetScrollInfo(hWnd, SB_VERT, &vscroll, TRUE);
				InvalidateRect(hWnd, &rc, FALSE);
			} break;
			case WM_DWMCOLORIZATIONCOLORCHANGED: {
				System::s_updateSystemColor();

				for (auto wnd : s_windowsMap) {
					wnd.second->redrawWindow(false);
				}
			} break;


			default: return DefWindowProc(hWnd, msg, wParam, lParam);
			}
			return 0;
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


	void Window::registerHendler(PaintHandler method)
	{
		_paintHandlers.push_back(method);
	}
	void Window::registerHendler(MouseClickHandler method)
	{
		_mouseClickHandlers.push_back(method);
	}
	void Window::registerHendler(MouseWheelHandler method)
	{
		_mouseWheelHandlers.push_back(method);
	}
	void Window::registerHendler(MouseMoveHandler method)
	{
		_mouseMoveHandlers.push_back(method);
	}
	void Window::registerHendler(KeyboardHandler method)
	{
		_keyboardHandlers.push_back(method);
	}
	void Window::registerHendler(ParentHandler method)
	{
		_parentHandlers.push_back(method);
	}
	void Window::registerHendler(HoverHandler method)
	{
		_hoverHandlers.push_back(method);
	}
	void Window::m_registerTimerHendler(TimerHandler method)
	{
		_timerHandlers.push_back(method);
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

		_g_pos_X = getGlobalPosX();
		_g_pos_Y = getGlobalPosY();

		SetWindowPos(_hWnd, 0, 0, 0, 0, 0, 
			SWP_NOSIZE 
			| SWP_NOMOVE 
			| SWP_FRAMECHANGED 
			| (show ? SWP_SHOWWINDOW : SWP_HIDEWINDOW));
		//RedrawWindow(_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_NOERASE | RDW_INTERNALPAINT | RDW_UPDATENOW | RDW_ALLCHILDREN);
		return true;
	}
	bool Window::m_createWindow(Window* parent)
	{
		long int style = ((parent) ? (WS_CHILD | WS_CLIPSIBLINGS) : (WS_POPUP | WS_BORDER)) | WS_CLIPCHILDREN | WS_VISIBLE;

		_hWnd = CreateWindowExW(
			0,
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
		_renderBuffer = std::make_shared<RenderBuffer>(_hWnd, _width, _hieght);
		SendMessage(_hWnd, WM_CREATE, 0, 0);
		return true;
	}
	ATOM Window::m_registerClass() {
		WNDCLASS wndclass;
		if (GetClassInfo(GetModuleHandle(0), _className.c_str(), &wndclass)) {
			return 1;
		}

		_WndClass.cbSize = sizeof(_WndClass);
		_WndClass.style = CS_DBLCLKS | CS_SAVEBITS;
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


	void Window::eventCreateWindow()
	{
		this->defaultCreateHandler();
	}
	void Window::defaultCreateHandler()
	{

	}
	void Window::eventMoveWindow(int oldPosX, int oldPosY)
	{
		this->defaultMoveHandler(oldPosX, oldPosY);
	}
	void Window::defaultMoveHandler(int oldPosX, int oldPosY)
	{

	}
	void Window::eventSizeWindow(int oldWidth, int oldHeight)
	{
		this->defaultSizeHandler(oldWidth, oldHeight);
	}
	void Window::defaultSizeHandler(int oldWidth, int oldHeight)
	{
		setRenderBufferSize(_width, _hieght);
	}
	void Window::eventCloseWindow()
	{
		this->defaultCloseHandler();
	}
	void Window::defaultCloseHandler()
	{
		s_windowsMap.erase(_hWnd);
		if (s_windowsMap.size() == 0) {
			PostQuitMessage(0);
		}
	}


	void Window::timerCheckHoverWindow(const int& ID)
	{
		if (ID == TIMER_UPP_HOVER) {
			//bool windowStatus = _hWnd == GetForegroundWindow();

			POINT point;
			GetCursorPos(&point);
			_g_pos_X = getGlobalPosX();
			_g_pos_Y = getGlobalPosY();

			if ((point.x >= _g_pos_X && point.x <= _g_pos_X + getWidth() - 1)
				&& (point.y >= _g_pos_Y && point.y <= _g_pos_Y + getHieght() - 1)) {
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
	void Window::abstratcWindowScrollIventHandler(MouseEventWheel mouseEventWheel)
	{
		if (mouseEventWheel.Wheel == MOUSE_WHEEL_BOT && _scrollbarVertical_IsEnable) {
			_scrollbarVerticalStatus += _scrollbarVerticalStepSize;
			int max_status = _renderBuffer->getHeight() - _hieght;

			if (max_status < 0) {
				_scrollbarVerticalStatus = 0;
			}
			else if (max_status < _scrollbarVerticalStatus){
				_scrollbarVerticalStatus = max_status;
			}
		}
		else if (mouseEventWheel.Wheel == MOUSE_WHEEL_TOP && _scrollbarVertical_IsEnable) {
			_scrollbarVerticalStatus -= _scrollbarVerticalStepSize;
			if (_scrollbarVerticalStatus < 0) {
				_scrollbarVerticalStatus = 0;
			}
		}
	}


	void Window::m_invalidateChilds()
	{
		for (Window* child : _childList) {
			InvalidateRect(child->getHWND(), nullptr, false);
		}
	}

	void Window::m_calculateNewPositionWindowIfParentResize()
	{
		for (Window* window : _childList) {
			if (window->_moveWhenParentResiz_X || window->_moveWhenParentResiz_Y) {
				int childPos_x = window->_pos_x;
				int childPos_y = window->_pos_y;

				int newChildPos_x = (window->_moveWhenParentResiz_X) ? 
					(_width - (_oldWidth - childPos_x)) :
					(childPos_x);
				int newChildPos_y = (window->_moveWhenParentResiz_Y) ?
					(_hieght - (_oldHieght - childPos_y)) : 
					(childPos_y);

				window->moveWindowPos(newChildPos_x, newChildPos_y, false);
			}
		}
	}
	void Window::m_calculateNewSizeWindowIfParentResize()
	{
		for (Window* window : _childList) {
			if (window->_resizeWhenParentResize_Width || window->_resizeWhenParentResize_Height) {
				int childWidth = window->_width;
				int childHeight = window->_hieght;

				int newChildWidth = (window->_resizeWhenParentResize_Width) ? 
					(childWidth + _width - _oldWidth) : 
					(childWidth);
				int newChildHeight = (window->_resizeWhenParentResize_Height) ? 
					(childHeight + _hieght - _oldHieght) : 
					(childHeight);

				window->resizeWindow(newChildWidth, newChildHeight, true);
			}
		}
	}



	void Window::m_WndProcHandler_GetMinMaxInfo(Window* wnd, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		MINMAXINFO *min_max = reinterpret_cast<MINMAXINFO *>(lParam);

		min_max->ptMinTrackSize.x = wnd->_minWidth;
		min_max->ptMinTrackSize.y = wnd->_minHieght;
		min_max->ptMaxTrackSize.x = GetSystemMetrics(SM_CXMAXTRACK);
		min_max->ptMaxTrackSize.y = GetSystemMetrics(SM_CYMAXTRACK);
	}
	void Window::m_WndProcHandler_Sizing(Window* wnd, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		RECT* rect = reinterpret_cast<RECT*>(lParam);

		wnd->_oldWidth = wnd->_width;
		wnd->_oldHieght = wnd->_hieght;
		wnd->_width = rect->right - rect->left;
		wnd->_hieght = rect->bottom - rect->top;

		wnd->m_calculateNewPositionWindowIfParentResize();
		wnd->m_calculateNewSizeWindowIfParentResize();
		//RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_NOERASE | RDW_INTERNALPAINT | RDW_UPDATENOW | RDW_ALLCHILDREN);
	}
	void Window::m_WndProcHandler_Paint(Window* wnd, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(wnd->_hWnd, &ps);
		HDC hDC_Buffer = wnd->_renderBuffer->getDC();

		_RPTF4(0, "Drawing rect: ? - %d, ? - %d, ? - %d, ? - %d\n", ps.rcPaint.top, ps.rcPaint.bottom, ps.rcPaint.right, ps.rcPaint.left);

		Gdiplus::Graphics graphics(hDC_Buffer);

		for (auto handler : wnd->_paintHandlers) {
			handler(graphics);
		}

		wnd->_renderBuffer->copyTo(
			hDC,
			wnd->_scrollbarHorizontalStatus, wnd->_scrollbarVerticalStatus,
			0, 0,
			wnd->_width, wnd->_hieght
		);

		EndPaint(wnd->_hWnd, &ps);
	}
	void Window::m_WndProcHandler_Move(Window* wnd, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		ParentEvent parentEvent;
		parentEvent.Code = PARENT_MOVE;
		parentEvent.Pos_X = wnd->_pos_x;
		parentEvent.Pos_Y = wnd->_pos_y;
		parentEvent.Width = wnd->_width;
		parentEvent.Height = wnd->_hieght;

		for (auto child : wnd->_childList) {
			for (auto handler : child->_parentHandlers) {
				handler(parentEvent);
			}
		}
	}
	void Window::m_WndProcHandler_Size(Window* wnd, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		ParentEvent parentEvent;
		parentEvent.Code = PARENT_RESIZE;
		parentEvent.Pos_X = wnd->_pos_x;
		parentEvent.Pos_Y = wnd->_pos_y;
		parentEvent.Width = wnd->_width;
		parentEvent.Height = wnd->_hieght;

		//wnd->setRenderBufferSize(wnd->_width, wnd->_hieght);

		for (auto child : wnd->_childList) {
			for (auto handler : child->_parentHandlers) {
				handler(parentEvent);
			}
		}

		wnd->eventSizeWindow(wnd->_oldWidth, wnd->_oldHieght);
		if (wnd->_redrawWhereResizing || !wnd->_resizing) {
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_NOERASE | RDW_INTERNALPAINT | RDW_UPDATENOW | RDW_ALLCHILDREN);
		}
		//RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_NOERASE | RDW_INTERNALPAINT);
	}
	void Window::m_WndProcHandler_MouseMove(Window* wnd, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		POINT cursorPoint;
		GetCursorPos(&cursorPoint);

		MouseEvent mouseEvent(LOWORD(lParam), HIWORD(lParam), cursorPoint.x, cursorPoint.y);

		for (auto handler : wnd->_mouseMoveHandlers) {
			handler(mouseEvent);
		}
	}
	void Window::m_WndProcHandler_MouseButtons(Window* wnd, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		POINT cursorPoint;
		GetCursorPos(&cursorPoint);

		MouseKeyCodes keyCode;
		MouseKeyClick keyClick;
		KeyStatus keyStatus;

		switch (msg) {
		case WM_LBUTTONUP: case WM_RBUTTONUP: case WM_MBUTTONUP: { keyStatus = KEY_RELEASED; } break;
		default: { keyStatus = KEY_PRESSED; } break;
		}

		switch (msg) {
		case WM_LBUTTONDOWN: case WM_LBUTTONUP: case WM_LBUTTONDBLCLK: {
			keyCode = MOUSE_LEFT;
		} break;
		case WM_RBUTTONDOWN: case WM_RBUTTONUP: case WM_RBUTTONDBLCLK: {
			keyCode = MOUSE_RIGHT;
		} break;
		case WM_MBUTTONDOWN: case WM_MBUTTONUP: case WM_MBUTTONDBLCLK: {
			keyCode = MOUSE_MIDDLE;
		} break;
		}

		switch (msg) {
		case WM_LBUTTONDBLCLK: case WM_RBUTTONDBLCLK: case WM_MBUTTONDBLCLK: {
			keyClick = MOUSE_CLICK_DOUBLE;
		} break;
		default: {
			keyClick = MOUSE_CLICK_ONE;
		} break;
		}

		MouseEventClick mouseEventClick(
			keyCode, keyClick, keyStatus,
			LOWORD(lParam), HIWORD(lParam),
			cursorPoint.x, cursorPoint.y
		);

		for (auto handler : wnd->_mouseClickHandlers) {
			handler(mouseEventClick);
		}

	}
	void Window::m_WndProcHandler_Keyboard(Window* wnd, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		static KeyStatus keyStatus;
		if (msg == WM_KEYDOWN || msg == WM_KEYUP) {
			if (msg == WM_KEYDOWN) { keyStatus = KEY_PRESSED; }
			else if (msg == WM_KEYUP) { keyStatus = KEY_RELEASED; }

			if (GetAsyncKeyState(VK_CONTROL)) {
				static wchar_t symbol;

				if (GetAsyncKeyState(VK_LCONTROL)) {
					symbol = KEY_LCONTROL;
				}
				if (GetAsyncKeyState(VK_RCONTROL)) {
					symbol = KEY_RCONTROL;
				}

				KeyEvent keyEvent(symbol, (KeyCodes)wParam, keyStatus);
				for (auto handler : wnd->_keyboardHandlers) {
					handler(keyEvent);
				}
			}
			if (GetAsyncKeyState(VK_SHIFT)) {
				static wchar_t symbol;

				if (GetAsyncKeyState(VK_LSHIFT)) {
					symbol = KEY_LSHIFT;
				}
				if (GetAsyncKeyState(VK_RSHIFT)) {
					symbol = KEY_RSHIFT;
				}

				KeyEvent keyEvent(symbol, (KeyCodes)wParam, keyStatus);
				for (auto handler : wnd->_keyboardHandlers) {
					handler(keyEvent);
				}
			}
		}
		if (msg == WM_KEYUP || msg == WM_CHAR) {
			static wchar_t symbol;

			if (GetAsyncKeyState(VK_CONTROL)) {
				if (GetAsyncKeyState(VK_LCONTROL)) {
					symbol = KEY_LCONTROL;
				}
				if (GetAsyncKeyState(VK_RCONTROL)) {
					symbol = KEY_RCONTROL;
				}
			} else if (msg == WM_CHAR) {
				symbol = wParam;
			}

			_RPTF1(0, "Symbol: %d\n", symbol);
			
			KeyEvent keyEvent(symbol, (KeyCodes)wParam, keyStatus);
			for (auto handler : wnd->_keyboardHandlers) {
				handler(keyEvent);
			}
		}
	}
	void Window::m_WndProcHandler_MouseHover(Window* wnd, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		for (auto handler : wnd->_hoverHandlers) {
			handler(wParam);
		}
	}
	void Window::m_WndProcHandler_MouseWheel(Window* wnd, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		HWND hWnd_pos = WindowFromPoint(POINT{ LOWORD(lParam), HIWORD(lParam) });
		if (!hWnd_pos) {
			return;
		}

		short value = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
		MouseWheelCodes mouseWheelCodes;
		if (value > 0) {
			mouseWheelCodes = MOUSE_WHEEL_TOP;
		}
		else if (value < 0) {
			mouseWheelCodes = MOUSE_WHEEL_BOT;
		}

		MouseEventWheel mouseEventWheel(mouseWheelCodes, LOWORD(lParam), HIWORD(lParam), LOWORD(lParam), HIWORD(lParam));
		
		if (s_windowsMap.find(hWnd_pos) != s_windowsMap.end()) {
			for (auto handler : s_windowsMap[hWnd_pos]->_mouseWheelHandlers) {
				handler(mouseEventWheel);
			}
			s_windowsMap[hWnd_pos]->redrawWindow(false);
		}

		if (value > 0) {
			PostMessage(hWnd, WM_VSCROLL, SB_LINEUP, NULL);
		}
		else {
			PostMessage(hWnd, WM_VSCROLL, SB_LINEDOWN, NULL);
		}
	}
	void Window::m_WndProcHandler_Timer(Window* wnd, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		for (auto handler : wnd->_timerHandlers) {
			handler(wParam);
		}
	}
	int Window::m_WndProcHandler_NcCalcSize(Window* wnd, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (wParam) {
			NCCALCSIZE_PARAMS* Params = reinterpret_cast<NCCALCSIZE_PARAMS *>(lParam);
			Params->rgrc[0].bottom += wnd->_borderSize;
			Params->rgrc[0].right += wnd->_borderSize;
			Params->rgrc[1].bottom += wnd->_borderSize;
			Params->rgrc[1].right += wnd->_borderSize;
			Params->rgrc[2].bottom += wnd->_borderSize;
			Params->rgrc[2].right += wnd->_borderSize;
			return 0;
		}
		DefWindowProc(hWnd, msg, wParam, lParam);
	}
	int Window::m_WndProcHandler_NcHitTest(Window* wnd, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		POINT pos;
		GetCursorPos(&pos);
		RECT WindowRect;
		GetWindowRect(hWnd, &WindowRect);

		int x = pos.x - WindowRect.left;
		int y = pos.y - WindowRect.top;

		if (x >= wnd->_borderSize && x <= wnd->_width - wnd->_borderSize
			&& y >= wnd->_borderSize && y <= MAIN_WINDOW_HEADER_HEIGHT
			&& wnd->_haveHeader)
			return HTCAPTION;
		else if (x <= wnd->_borderSize && wnd->_canBeResize_left)
			return HTLEFT;
		else if (y <= wnd->_borderSize && wnd->_canBeResize_top)
			return HTTOP;
		else if (x >= wnd->_width - wnd->_borderSize - 1 && wnd->_canBeResize_right)
			return HTRIGHT;
		else if (y >= wnd->_hieght - wnd->_borderSize - 1 && wnd->_canBeResize_bottom)
			return HTBOTTOM;
		else
			return HTCLIENT;
	}
}