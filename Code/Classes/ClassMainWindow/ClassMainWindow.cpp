#include "stdafx.h"
#include "ClassMainWindow.h"

namespace explorer {
	MainWindow::MainWindow()
	{
		registerWindowHandlers();
	}


	void MainWindow::registerWindowHandlers()
	{
		m_registerHendler(WM_CREATE, METHOD(&MainWindow::createHandler));
		m_registerHendler(WM_PAINT, METHOD(&Window::paintWindow));
		m_registerHendler(WM_PAINT, METHOD(&MainWindow::paintHandler_2));
		m_registerHendler(WM_PAINT, METHOD(&MainWindow::paintHandler));
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