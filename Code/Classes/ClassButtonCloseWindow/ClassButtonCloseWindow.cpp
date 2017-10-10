#include "stdafx.h"
#include "ClassButtonCloseWindow.h"

namespace explorer {

	ButtonClose::ButtonClose()
	{
		m_registerHendler(WM_LBUTTONDOWN, std::bind(&ButtonClose::closeHandler, this, (HWND)1, (WPARAM)2, (LPARAM)3));
		m_registerHendler(WM_PAINT, std::bind(&ButtonClose::paintHandler, this, (HWND)1, (WPARAM)2, (LPARAM)3));
		m_registerHendler(WM_CREATE, std::bind(&ButtonClose::createHandler, this, (HWND)1, (WPARAM)2, (LPARAM)3));
	}

	void ButtonClose::createHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		Gdiplus::Rect rect(-1, -1, 16, 16);
		Gdiplus::GraphicsPath path;
		path.AddEllipse(rect);

		_region.Intersect(&path);
	}

	void ButtonClose::paintHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		//MessageBox(0, L"test", L"Pisos", MB_OK);/*
		//_graphics->SetClip(G);
		
		_graphics->SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);

		Gdiplus::Pen pen(Gdiplus::Color::White, 2);
		Gdiplus::SolidBrush brush(Gdiplus::Color::Red);
		_graphics->FillRectangle(&brush, -1, -1, getWidth()+1, getHieght()+1);

		_graphics->SetClip(&_region);
		Gdiplus::Point pos_1(0, 0), pos_2(getWidth(), getHieght());
		Gdiplus::Point pos_3(getWidth()-1, 0), pos_4(-1, getHieght());

		_graphics->DrawLine(&pen, pos_2, pos_1);
		_graphics->DrawLine(&pen, pos_3, pos_4);

		_graphics->ExcludeClip(&_region);
	}

	void ButtonClose::closeHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		m_sendMessageForParent(WM_CLOSE, 0, 0);
	}

}