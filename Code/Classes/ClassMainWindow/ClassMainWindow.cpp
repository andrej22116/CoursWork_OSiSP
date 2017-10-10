#include "stdafx.h"
#include "ClassMainWindow.h"

namespace explorer {
	MainWindow::MainWindow()
	{
		registerWindowHandlers();
	}


	void MainWindow::registerWindowHandlers()
	{
		m_registerHendler(WM_CREATE, std::bind(&MainWindow::createHandler, this, (HWND)1, (WPARAM)2, (LPARAM)3));
		m_registerHendler(WM_PAINT, std::bind(&MainWindow::paintHandler_2, this, (HWND)1, (WPARAM)2, (LPARAM)3));
		m_registerHendler(WM_PAINT, std::bind(&MainWindow::paintHandler, this, (HWND)1, (WPARAM)2, (LPARAM)3));
	}

	void MainWindow::paintHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		Gdiplus::SolidBrush brush(Gdiplus::Color(64, 64, 64));
		Gdiplus::Rect region(0, 0, this->getWidth(), 17);
		_graphics->FillRectangle(&brush, region);
	}

	void MainWindow::paintHandler_2(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		Gdiplus::SolidBrush brush(Gdiplus::Color(32, 32, 32));
		Gdiplus::Rect region(0, 0, this->getWidth(), this->getHieght());
		_graphics->FillRectangle(&brush, region);
	}

	void MainWindow::createHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		buttonClose.create(
			L"Pizda",
			*this,
			this->getWidth() - 16,
			1,
			15,
			15,
			true);
		//MessageBox(nullptr, (L"IT'S WORK!!! " + getWindowName()).c_str(), L"TEST", MB_OK);
	}
}