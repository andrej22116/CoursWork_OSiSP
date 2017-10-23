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
		_resize_x = false;
		_resize_y = false;

		_inBorder_x_left = false;
		_inBorder_x_right = false;
		_inBorder_y_top = false;
		_inBorder_y_bot = false;
		_inHeader = false;
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

		if (mouseEventClick.Button == MOUSE_LEFT && mouseEventClick.Status == KEY_PRESSED && !buttonMaximize.isMaximized()) {
			if (_inHeader) {
				_oldCursorPosX = mouseEventClick.global_x;
				_oldCursorPosY = mouseEventClick.global_y;

				SetCapture(getHWND());
				_moving = true;
			}
			else if (_inBorder_x_left || _inBorder_x_right) {
				SetCapture(getHWND());
				_resize_x = true;
			}
			else if (_inBorder_y_top || _inBorder_y_bot) {
				SetCapture(getHWND());
				_resize_y = true;
			}
		}
		else if (mouseEventClick.Button == MOUSE_LEFT && mouseEventClick.Status == KEY_RELEASED) {
			if (_moving) {
				ReleaseCapture();
				_moving = false;
			}
			else if (_inBorder_x_left || _inBorder_x_right || _inBorder_y_top || _inBorder_y_bot) {
				ReleaseCapture();
				_resize_x = false;
				_resize_y = false;
				m_invalidateChilds();
			}
		}
	}

	void MainWindow::keyboardHandler(const KeyEvent& keyEvent)
	{
		/*
		if (keyEvent.Status == KEY_RELEASED) {
			std::wstring str = L"This symbol: ";
			str += keyEvent.Sumbol;
			MessageBox(getHWND(), str.c_str(), L"Test", MB_OK);
		}
		*/
	}

	void MainWindow::mouseMoveHandler(MouseEvent& mouseEvent)
	{
		if (_moving) {
			move(mouseEvent);
			return;
		}
		if (_resize_x || _resize_y) {
			resize(mouseEvent);
			return;
		}

		checkCursorPosInBorder(mouseEvent);
		checkCursorPosInHeader(mouseEvent);
	}


	void MainWindow::checkCursorPosInBorder(MouseEvent& mouseEvent)
	{
		bool inHorizontalBorder_left = mouseEvent.x >= 0 && mouseEvent.x <= 2;
		bool inHorizontalBorder_right = mouseEvent.x >= getWidth() - 2 && mouseEvent.x <= getWidth();

		bool inVerticalBorder_top = mouseEvent.y >= 0 && mouseEvent.y <= 2;
		bool inVerticalBorder_bot = mouseEvent.y >= getHieght() - 2 && mouseEvent.y <= getHieght();

		if (inHorizontalBorder_left || inHorizontalBorder_right) {
			SetCursor(LoadCursor(0, IDC_SIZEWE));

			_inBorder_x_left = false;
			_inBorder_x_right = false;

			if (inHorizontalBorder_left) {
				_inBorder_x_left = true;
			}
			else {
				_inBorder_x_right = true;
			}
		}
		else if (inVerticalBorder_top || inVerticalBorder_bot) {
			SetCursor(LoadCursor(0, IDC_SIZENS));

			_inBorder_y_top = false;
			_inBorder_y_bot = false;

			if (inVerticalBorder_top) {
				_inBorder_y_top = true;
			}
			else {
				_inBorder_y_bot = true;
			}
		}
		else {
			_inBorder_x_left = false;
			_inBorder_x_right = false;
			_inBorder_y_top = false;
			_inBorder_y_bot = false;

			SetCursor(LoadCursor(0, IDC_ARROW));
		}
	}
	void MainWindow::checkCursorPosInHeader(MouseEvent& mouseEvent)
	{
		bool mouse_pos_x = mouseEvent.x > 2 && mouseEvent.x < getWidth() - 2;
		bool mouse_pos_y = mouseEvent.y > 2 && mouseEvent.y <= 16;

		if (mouse_pos_x && mouse_pos_y) {
			_inHeader = true;
		}
		else {
			_inHeader = false;
		}
	}

	void MainWindow::move(MouseEvent& mouseEvent)
	{
		int newPosX = mouseEvent.global_x - _oldCursorPosX + getPosX();
		int newPosY = mouseEvent.global_y - _oldCursorPosY + getPosY();
		_oldCursorPosX = mouseEvent.global_x;
		_oldCursorPosY = mouseEvent.global_y;
		moveWindowPos(newPosX, newPosY);
	}

	void MainWindow::resize(MouseEvent& mouseEvent)
	{
		if (_resize_x) {
			if (_inBorder_x_left) {
				int width = getWidth() + getPosX() - mouseEvent.global_x;
				resizeWindow(mouseEvent.global_x, getPosY(), width, getHieght(), true);
			}
			else {
				int width = mouseEvent.global_x - getPosX();
				resizeWindow(width, getHieght(), true);
			}
		}
		else {
			if (_inBorder_y_top) {
				int hight = getHieght() + getPosY() - mouseEvent.global_y;
				resizeWindow(getPosX(), mouseEvent.global_y, getWidth(), hight, true);
			}
			else {
				int hight = mouseEvent.global_y - getPosY();
				resizeWindow(getWidth(), hight, true);
			}
		}
	}
}