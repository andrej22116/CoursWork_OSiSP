#include "stdafx.h"
#include "ClassMinimizeWindow.h"

namespace explorer {

	ButtonMinimize::ButtonMinimize()
	{
		m_registerHendler(WM_CREATE, METHOD(&ButtonMinimize::createHandler));
		m_registerHendler(WM_PAINT, METHOD(&ButtonMinimize::paintHandler));
		m_registerHendler(WM_MOUSEHOVER, METHOD(&ButtonMinimize::hoverHandler));
		m_registerHendler(WM_LBUTTONDOWN, METHOD(&ButtonMinimize::minimizeHandler));
		m_registerHendler(WM_SIZE, METHOD(&ButtonMinimize::resizeParentHandler));

		_hover = false;
	}

	void ButtonMinimize::createHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		getHoverMessages(true);
	}
	void ButtonMinimize::paintHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hWnd, &ps);
		std::shared_ptr<Gdiplus::Graphics> graphics = std::make_shared<Gdiplus::Graphics>(hDC);

		Gdiplus::Pen pen(Gdiplus::Color::White, 1.6);
		Gdiplus::SolidBrush brush((_hover) ? (Gdiplus::Color(96, 96, 96)) : (Gdiplus::Color(64, 64, 64)));
		graphics->FillRectangle(&brush, -1, -1, getWidth() + 1, getHieght() + 1);

		graphics->DrawRectangle(&pen, 2, getHieght()-3, getWidth()-5, 1);

		EndPaint(hWnd, &ps);
	}
	void ButtonMinimize::hoverHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		_hover = wParam;
		redrawWindow(false);
	}

	void ButtonMinimize::minimizeHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		getParent()->minimizeWindow(true);
	}

	void ButtonMinimize::resizeParentHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		resizeWindow(getParent()->getWidth() - 48, 1, 15, 15, true);
	}

}