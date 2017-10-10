#include "stdafx.h"
#include "ClassButtonCloseWindow.h"

namespace explorer {

	ButtonClose::ButtonClose()
	{
		m_registerHendler(WM_LBUTTONDOWN, std::bind(&ButtonClose::closeHandler, this, (HWND)1, (WPARAM)2, (LPARAM)3));
		m_registerHendler(WM_PAINT, std::bind(&ButtonClose::paintHandler, this, (HWND)1, (WPARAM)2, (LPARAM)3));
	}

	LRESULT ButtonClose::paintHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		//MessageBox(0, L"test", L"Pisos", MB_OK);
		Gdiplus::Pen pen(Gdiplus::Color::Red, 20);
		Gdiplus::Point pos_1(0, 0), pos_2(getWidth(), getHieght());
		Gdiplus::Point pos_3(getWidth(), 0), pos_4(0, getHieght());
		_graphics->DrawLine(&pen, pos_2, pos_1);
		_graphics->DrawLine(&pen, pos_3, pos_4);

		return 0;
	}

	LRESULT ButtonClose::closeHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		m_sendMessageForParent(WM_CLOSE, 0, 0);
		return 0;
	}

}