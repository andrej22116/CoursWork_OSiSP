#include "stdafx.h"
#include "ClassMaximizeWindow.h"


namespace explorer {
	ButtonMaximize::ButtonMaximize()
	{
		m_registerHendler(METHOD(&ButtonMaximize::paintHandler));

		m_registerHendler(METHOD(&ButtonMaximize::hoverHandler));
		m_registerHendler(METHOD(&ButtonMaximize::resizeParentHandler));

		m_registerHendler(METHOD(&ButtonMaximize::maximizeHandler));
		setMoveWhenParentResizeing(true);

#ifdef _DEBUGU
		m_registerHendler(WM_RBUTTONDOWN, METHOD(&ButtonMaximize::testHandler));
#endif

		_maximized = false;
	}


	bool ButtonMaximize::isMaximized()
	{
		return _maximized;
	}

	void ButtonMaximize::paintHandler(Gdiplus::Graphics& graphics)
	{
		Gdiplus::Pen pen(Gdiplus::Color::White, 1);
		Gdiplus::SolidBrush brush((isHover()) ?
			(MAIN_WINDOW_COLOR_HEADER_BUTTON_SELECTED) :
			(MAIN_WINDOW_COLOR_HEADER));
		graphics.FillRectangle(&brush, -1, -1, getWidth() + 1, getHieght() + 1);


		Gdiplus::Rect rect_0(4, 4, getWidth() - 9, getHieght() - 9);

		graphics.DrawRectangle(&pen, rect_0);
	}

	void ButtonMaximize::maximizeHandler(const MouseEventClick& mouseEventClick)
	{
		//m_sendMessageForParent(WM_SIZE, 0, 0);
		if (mouseEventClick.Button == MOUSE_LEFT && mouseEventClick.Status == KEY_PRESSED) {
			if (getParent()) {
				if (!_maximized) {
					_oldWidth = getParent()->getWidth();
					_oldHieght = getParent()->getHieght();
					_oldPosX = getParent()->getPosX();
					_oldPosY = getParent()->getPosY();
					getParent()->resizeWindow(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), true);

					_maximized = true;
				}
				else {
					getParent()->resizeWindow(_oldPosX, _oldPosY, _oldWidth, _oldHieght, true);

					_maximized = false;
				}
			}
		}
		else if (mouseEventClick.Button == MOUSE_RIGHT) {
			POINT point;
			GetCursorPos(&point);
			std::wstring str =
				L"GposX: " + std::to_wstring(getGlobalPosX()) + L" \n"
				+ L"GposY: " + std::to_wstring(getGlobalPosY()) + L" \n"
				+ L"MousePosX: " + std::to_wstring(point.x) + L" \n"
				+ L"MousePosY: " + std::to_wstring(point.y);
			MessageBox(getHWND(), str.c_str(), L"TEST", MB_OK);
		}
	}

	void ButtonMaximize::resizeParentHandler(const ParentEvent& parentEvent)
	{
	}
#ifdef _DEBUG
	void ButtonMaximize::testHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		POINT point;
		GetCursorPos(&point);
		std::wstring str =
			L"GposX: " + std::to_wstring(getGlobalPosX()) + L" \n"
			+ L"GposY: " + std::to_wstring(getGlobalPosY()) + L" \n"
			+ L"MousePosX: " + std::to_wstring(point.x) + L" \n"
			+ L"MousePosY: " + std::to_wstring(point.y);
		MessageBox(hWnd, str.c_str(), L"TEST", MB_OK);
	}
#endif
}