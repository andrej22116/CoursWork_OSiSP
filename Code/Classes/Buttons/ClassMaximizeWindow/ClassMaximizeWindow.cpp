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


	void ButtonMaximize::createWindow()
	{
		getHoverMessages(true);
	}

	void ButtonMaximize::paintHandler(Gdiplus::Graphics& graphics)
	{
		Gdiplus::Pen pen(Gdiplus::Color::White, 1.6);
		Gdiplus::SolidBrush brush((_hover) ? (Gdiplus::Color(96, 96, 96)) : (Gdiplus::Color(64, 64, 64)));
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

	void ButtonMaximize::hoverHandler(bool status)
	{
		_hover = status;
		redrawWindow(false);
	}

	void ButtonMaximize::maximizeHandler(const MouseEventClick& mouseEventClick)
	{
		//m_sendMessageForParent(WM_SIZE, 0, 0);
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

	void ButtonMaximize::resizeParentHandler(const ParentEvent& parentEvent)
	{
		if (parentEvent.Code == PARENT_RESIZE) {
			resizeWindow(getParent()->getWidth() - 32, 1, 15, 15, true);
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