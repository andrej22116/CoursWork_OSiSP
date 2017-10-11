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

		graphics->SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);

		Gdiplus::Pen pen(Gdiplus::Color::White, 1.6);
		Gdiplus::SolidBrush brush((_hover) ? (Gdiplus::Color(96, 96, 96)) : (Gdiplus::Color(64, 64, 64)));
		graphics->FillRectangle(&brush, -1, -1, getWidth() + 1, getHieght() + 1);


		Gdiplus::Rect rect_1(6, 2, 6, 6);
		Gdiplus::Rect rect_2(2, 6, 6, 6);

		graphics->DrawRectangle(&pen, rect_1);
		graphics->FillRectangle(&brush, rect_2);
		graphics->DrawRectangle(&pen, rect_2);

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
			getParent()->resizeWindow(0, 0, GetSystemMetrics(SM_CXMAXIMIZED), GetSystemMetrics(SM_CYMAXIMIZED), true);
		}
	}

	void ButtonMaximizeWindow::resizeParentHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		resizeWindow(getParent()->getWidth() - 48, 1, 15, 15, true);
	}
}