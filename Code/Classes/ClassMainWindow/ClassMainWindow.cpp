#include "stdafx.h"
#include "ClassMainWindow.h"

namespace explorer {
	MainWindow::MainWindow()
	{
		m_registerHendler(METHOD(&MainWindow::paintHandler));
		m_registerHendler(METHOD(&MainWindow::mouseClickHandler));
		m_registerHendler(METHOD(&MainWindow::mouseMoveHandler));
		m_registerHendler(METHOD(&MainWindow::keyboardHandler));

		_oldCursorPosX = 0;
		_oldCursorPosY = 0;
		_moving = false;
	}

	void MainWindow::paintHandler(Gdiplus::Graphics& graphics)
	{
		Gdiplus::SolidBrush brush_2(Gdiplus::Color(32, 32, 32));
		Gdiplus::Rect region_2(0, 0, this->getWidth(), this->getHieght());
		graphics.FillRectangle(&brush_2, region_2);

		Gdiplus::SolidBrush brush(Gdiplus::Color(64, 64, 64));
		Gdiplus::Rect region(0, 0, this->getWidth(), 17);
		graphics.FillRectangle(&brush, region);
	}

	void MainWindow::createWindow()
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

	void MainWindow::mouseClickHandler(const MouseEventClick& mouseEventClick)
	{
		// вычлинить двойной клик!

		if (mouseEventClick.Button == MOUSE_LEFT && mouseEventClick.Status == KEY_PRESSED) {
			if ((mouseEventClick.global_x >= getPosX() && mouseEventClick.global_x <= getPosX() + getWidth())
				&& (mouseEventClick.global_y >= getPosY() && mouseEventClick.global_y <= getPosY() + 16)) {
				_oldCursorPosX = mouseEventClick.global_x;
				_oldCursorPosY = mouseEventClick.global_y;

				SetCapture(getHWND());
				_moving = true;
			}
		}
		else if (mouseEventClick.Button == MOUSE_LEFT && mouseEventClick.Status == KEY_RELEASED) {
			if (_moving) {
				ReleaseCapture();
				_moving = false;
			}
		}
	}

	void MainWindow::keyboardHandler(const KeyEvent& keyEvent)
	{
		std::wstring str = L"This symbol: ";
		str += keyEvent.Sumbol;
		MessageBox(getHWND(), str.c_str(), L"Test", MB_OK);
	}

	void MainWindow::mouseMoveHandler(MouseEvent& mouseEvent)
	{
		if (_moving) {
			int newPosX = mouseEvent.global_x - _oldCursorPosX + getPosX();
			int newPosY = mouseEvent.global_y - _oldCursorPosY + getPosY();
			_oldCursorPosX = mouseEvent.global_x;
			_oldCursorPosY = mouseEvent.global_y;
			moveWindowPos(newPosX, newPosY);
		}
	}
}