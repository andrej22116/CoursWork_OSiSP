#include "stdafx.h"
#include "ClassButtonCloseWindow.h"

namespace explorer {

	ButtonClose::ButtonClose()
	{
		m_registerHendler(WM_LBUTTONDOWN, METHOD(&ButtonClose::closeHandler));
		m_registerHendler(WM_PAINT, METHOD(&ButtonClose::paintHandler));
		m_registerHendler(WM_CREATE, METHOD(&ButtonClose::createHandler));

		m_registerHendler(WM_MOUSEHOVER, METHOD(&ButtonClose::hoverHandler));
		m_registerHendler(WM_SIZE, METHOD(&ButtonClose::resizeParentHandler));

		_hover = false;
	}

	void ButtonClose::createHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		Gdiplus::Rect rect(-1, -1, 16, 16);
		Gdiplus::GraphicsPath path;
		path.AddEllipse(rect);

		_region.Intersect(&path);

		getHoverMessages(true);
	}

	void ButtonClose::hoverHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		_hover = wParam;
		redrawWindow(false);
	}

	void ButtonClose::paintHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{		
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hWnd, &ps);
		std::shared_ptr<Gdiplus::Graphics> graphics = std::make_shared<Gdiplus::Graphics>(hDC);

		graphics->SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);

		Gdiplus::Pen pen(Gdiplus::Color::White, 1.55);
		Gdiplus::SolidBrush brush((_hover) ? (Gdiplus::Color::Red) : (Gdiplus::Color(64,64,64)));
		graphics->FillRectangle(&brush, -1, -1, getWidth()+1, getHieght()+1);

		graphics->SetClip(&_region);
		Gdiplus::Point pos_1(0, 0), pos_2(getWidth(), getHieght());
		Gdiplus::Point pos_3(getWidth()-1, 0), pos_4(-1, getHieght());

		graphics->DrawLine(&pen, pos_2, pos_1);
		graphics->DrawLine(&pen, pos_3, pos_4);

		graphics->ExcludeClip(&_region);

		EndPaint(hWnd, &ps);
	}

	void ButtonClose::closeHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		m_sendMessageForParent(WM_CLOSE, 0, 0);
	}

	void ButtonClose::resizeParentHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		resizeWindow(getParent()->getWidth() - 16, 1, 15, 15, true);
	}
}