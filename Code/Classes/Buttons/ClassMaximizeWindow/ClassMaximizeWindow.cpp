#include "stdafx.h"
#include "ClassMaximizeWindow.h"


namespace explorer {
	ButtonMaximize::ButtonMaximize()
	{
		m_registerHendler(METHOD(&ButtonMaximize::paintHandler));

		m_registerHendler(METHOD(&ButtonMaximize::hoverHandler));
		m_registerHendler(METHOD(&ButtonMaximize::resizeParentHandler));

		m_registerHendler(METHOD(&ButtonMaximize::maximizeHandler));

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
		Gdiplus::Pen pen(Gdiplus::Color::White, 1.6);
		Gdiplus::SolidBrush brush((isHover()) ?
			(MAIN_WINDOW_COLOR_HEADER_BUTTON_SELECTED) :
			(MAIN_WINDOW_COLOR_HEADER));
		graphics.FillRectangle(&brush, -1, -1, getWidth() + 1, getHieght() + 1);


		Gdiplus::Rect rect_0(1, 1, 12, 12);
		Gdiplus::Rect rect_1(6, 2, 6, 6);
		Gdiplus::Rect rect_2(2, 6, 6, 6);

		if (_maximized) {
			graphics.DrawRectangle(&pen, rect_1);
			graphics.DrawLine(&pen, 6, 3, 13, 3);

			graphics.FillRectangle(&brush, rect_2);
			graphics.DrawRectangle(&pen, rect_2);
			graphics.DrawLine(&pen, 2, 7, 9, 7);
		}
		else {
			graphics.DrawRectangle(&pen, rect_0);
			graphics.DrawLine(&pen, 1, 2, 13, 2);
		}
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
		if (parentEvent.Code == PARENT_RESIZE) {
			resizeWindow(
				MAIN_WINDOW_BUTTON_MAXIMIZE_POS_X(parentEvent.Width),
				MAIN_WINDOW_BUTTON_MAXIMIZE_POS_Y(1),
				MAIN_WINDOW_BUTTON_MAXIMIZE_WIDTH,
				MAIN_WINDOW_BUTTON_MAXIMIZE_HEIGHT,
				true
			);
		}
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