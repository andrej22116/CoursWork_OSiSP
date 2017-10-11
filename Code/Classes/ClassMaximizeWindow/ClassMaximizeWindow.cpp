#include "stdafx.h"
#include "ClassMaximizeWindow.h"


namespace explorer {
	ButtonMaximizeWindow::ButtonMaximizeWindow()
	{
		m_registerHendler(WM_CREATE, METHOD(&ButtonMaximizeWindow::createHandler));
		m_registerHendler(WM_PAINT, METHOD(&ButtonMaximizeWindow::paintHandler));
		m_registerHendler(WM_MOUSEHOVER, METHOD(&ButtonMaximizeWindow::hoverHandler));
		m_registerHendler(WM_LBUTTONDOWN, METHOD(&ButtonMaximizeWindow::maximizeHandler));
		m_registerHendler(WM_SIZE, METHOD(&ButtonMaximizeWindow::resizeParentHandler));

#ifdef _DEBUG
		m_registerHendler(WM_RBUTTONDOWN, METHOD(&ButtonMaximizeWindow::testHandler));
#endif

		_maximized = false;
	}


	void ButtonMaximizeWindow::createHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		getHoverMessages(true);
	}

	void ButtonMaximizeWindow::paintHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hWnd, &ps);
		std::shared_ptr<Gdiplus::Graphics> graphics = std::make_shared<Gdiplus::Graphics>(hDC);

		//graphics->SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);

		Gdiplus::Pen pen(Gdiplus::Color::White, 1.6);
		Gdiplus::SolidBrush brush((_hover) ? (Gdiplus::Color(96, 96, 96)) : (Gdiplus::Color(64, 64, 64)));
		graphics->FillRectangle(&brush, -1, -1, getWidth() + 1, getHieght() + 1);


		Gdiplus::Rect rect_0(1, 1, 12, 12);
		Gdiplus::Rect rect_1(6, 2, 6, 6);
		Gdiplus::Rect rect_2(2, 6, 6, 6);

		if (_maximized) {
			graphics->DrawRectangle(&pen, rect_1);
			graphics->DrawLine(&pen, 6, 3, 13, 3);

			graphics->FillRectangle(&brush, rect_2);
			graphics->DrawRectangle(&pen, rect_2);
			graphics->DrawLine(&pen, 2, 7, 9, 7);
		}
		else {
			graphics->DrawRectangle(&pen, rect_0);
			graphics->DrawLine(&pen, 1, 2, 13, 2);
		}

		EndPaint(hWnd, &ps);
	}

	void ButtonMaximizeWindow::hoverHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		_hover = wParam;
		redrawWindow(false);
	}

	void ButtonMaximizeWindow::maximizeHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		//m_sendMessageForParent(WM_SIZE, 0, 0);
		if (getParent()) {
			if (!_maximized) {
				_oldWidth = getParent()->getWidth();
				_oldHieght = getParent()->getHieght();
				_oldPosX = getParent()->getPosX();
				_oldPosY = getParent()->getPosY();
				getParent()->resizeWindow(0, 0, GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN), true);

				_maximized = true;
			}
			else {
				getParent()->resizeWindow(_oldPosX, _oldPosY, _oldWidth, _oldHieght, true);

				_maximized = false;
			}
		}
	}

	void ButtonMaximizeWindow::resizeParentHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		resizeWindow(getParent()->getWidth() - 32, 1, 15, 15, true);
	}
#ifdef _DEBUG
	void ButtonMaximizeWindow::testHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
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