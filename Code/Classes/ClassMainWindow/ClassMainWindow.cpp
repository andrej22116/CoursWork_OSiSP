#include "stdafx.h"
#include "ClassMainWindow.h"

namespace explorer {
	MainWindow::MainWindow()
	{
		m_registerHendler(WM_CREATE, METHOD(&MainWindow::createHandler));
		m_registerHendler(WM_PAINT, METHOD(&MainWindow::paintHandler));
		m_registerHendler(WM_LBUTTONDOWN, METHOD(&MainWindow::leftButtonDownHandler));
		m_registerHendler(WM_LBUTTONUP, METHOD(&MainWindow::leftButtonUpHandler));
		m_registerHendler(WM_MOUSEMOVE, METHOD(&MainWindow::moveHandler));

		_oldCursorPosX = 0;
		_oldCursorPosY = 0;
		_moving = false;
	}

	void MainWindow::paintHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hWnd, &ps);
		Gdiplus::Graphics graphics(hDC);

		Gdiplus::SolidBrush brush_2(Gdiplus::Color(32, 32, 32));
		Gdiplus::Rect region_2(0, 0, this->getWidth(), this->getHieght());
		graphics.FillRectangle(&brush_2, region_2);

		Gdiplus::SolidBrush brush(Gdiplus::Color(64, 64, 64));
		Gdiplus::Rect region(0, 0, this->getWidth(), 17);
		graphics.FillRectangle(&brush, region);

		EndPaint(hWnd, &ps);
	}

	void MainWindow::createHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		buttonClose.create(
			L"exit",
			*this,
			this->getWidth() - 16,
			1,
			15,
			15,
			true);

		buttonMaximize.create(
			L"maximize",
			*this,
			this->getWidth() - 32,
			1,
			15,
			15,
			true);

		buttonMinimize.create(
			L"minimize",
			*this,
			this->getWidth() - 48,
			1,
			15,
			15,
			true);
		//MessageBox(nullptr, (L"IT'S WORK!!! " + getWindowName()).c_str(), L"TEST", MB_OK);
	}

	void MainWindow::leftButtonDownHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		POINT point;
		GetCursorPos(&point);
		if ((point.x >= getPosX() && point.x <= getPosX() + getWidth())
			&& (point.y >= getPosY() && point.y <= getPosY() + 16)) {
			_oldCursorPosX = point.x;
			_oldCursorPosY = point.y;

			SetCapture(getHWND());
			_moving = true;
		}
	}
	void MainWindow::leftButtonUpHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		if (_moving) {
			ReleaseCapture();
			_moving = false;
		}
	}
	void MainWindow::moveHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		if (_moving) {
			POINT point;
			GetCursorPos(&point);

			int newPosX = point.x - _oldCursorPosX + getPosX();
			int newPosY = point.y - _oldCursorPosY + getPosY();
			_oldCursorPosX = point.x;
			_oldCursorPosY = point.y;
			moveWindowPos(newPosX, newPosY);
		}
	}
}