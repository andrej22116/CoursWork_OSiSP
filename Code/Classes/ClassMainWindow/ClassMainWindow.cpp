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
		Gdiplus::SolidBrush brush_2(MAIN_WINDOW_COLOR_BACKGROUND);
		Gdiplus::LinearGradientBrush lbrush(Gdiplus::Point(0, 0), Gdiplus::Point(50, 0), Gdiplus::Color(255, 190, 70), Gdiplus::Color(255, 250, 140));
		Gdiplus::Rect region_2(0, 0, this->getWidth(), this->getHieght());
		graphics.FillRectangle(&brush_2, region_2);

		Gdiplus::SolidBrush brush(MAIN_WINDOW_COLOR_HEADER);
		Gdiplus::Rect region(0, 0, this->getWidth(), 17);
		graphics.FillRectangle(&brush, region);


		Gdiplus::Font font(&Gdiplus::FontFamily(L"Arial"), 12);
		Gdiplus::SolidBrush textbrush(Gdiplus::Color(255, 255, 255));
		Gdiplus::Point point(3, 20);
		graphics.DrawString(L"Test я ем говно", -1, &font, Gdiplus::PointF(3, 20), &lbrush);

		setDoubleBuffered(true);
	}

	void MainWindow::createWindow()
	{
		buttonClose.create(
			L"exit",
			*this,
			MAIN_WINDOW_BUTTON_EXIT_POS_X(this->getWidth()),
			MAIN_WINDOW_BUTTON_EXIT_POS_Y(1),
			MAIN_WINDOW_BUTTON_EXIT_WIDTH,
			MAIN_WINDOW_BUTTON_EXIT_HEIGHT,
			true);

		buttonMaximize.create(
			L"maximize",
			*this,
			MAIN_WINDOW_BUTTON_MAXIMIZE_POS_X(this->getWidth()),
			MAIN_WINDOW_BUTTON_MAXIMIZE_POS_Y(1),
			MAIN_WINDOW_BUTTON_MAXIMIZE_WIDTH,
			MAIN_WINDOW_BUTTON_MAXIMIZE_HEIGHT,
			true);

		buttonMinimize.create(
			L"minimize",
			*this,
			MAIN_WINDOW_BUTTON_MINIMIZE_POS_X(this->getWidth()),
			MAIN_WINDOW_BUTTON_MINIMIZE_POS_Y(1),
			MAIN_WINDOW_BUTTON_MINIMIZE_WIDTH,
			MAIN_WINDOW_BUTTON_MINIMIZE_HEIGHT,
			true);
		listOfFiles.create(
			L"ListOfFiles",
			*this,
			LISTBOX_POS_X,
			LISTBOX_POS_Y,
			getWidth() - MAIN_WINDOW_BORDER_SIZE - LISTBOX_POS_X - 1,
			getHieght() - MAIN_WINDOW_BORDER_SIZE - LISTBOX_POS_Y - 1,
			true
		);
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
		//SendMessage(getHWND(), WM_VSCROLL, )
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
		bool inHorizontalBorder_left = mouseEvent.x >= 0 && mouseEvent.x < MAIN_WINDOW_BORDER_SIZE;
		bool inHorizontalBorder_right = mouseEvent.x > getWidth() - MAIN_WINDOW_BORDER_SIZE && mouseEvent.x <= getWidth();

		bool inVerticalBorder_top = mouseEvent.y >= 0 && mouseEvent.y < MAIN_WINDOW_BORDER_SIZE;
		bool inVerticalBorder_bot = mouseEvent.y > getHieght() - MAIN_WINDOW_BORDER_SIZE && mouseEvent.y <= getHieght();

		if ((inHorizontalBorder_left || inHorizontalBorder_right) && !buttonMaximize.isMaximized()) {
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
		else if ((inVerticalBorder_top || inVerticalBorder_bot) && !buttonMaximize.isMaximized()) {
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
				int width = getPosX() + getWidth() - mouseEvent.global_x;
				if (width >= 50) {
					//resizeWindow(getPosX(), getPosY(), width, getHieght(), true);
					resizeWindow(mouseEvent.global_x, getPosY(), width, getHieght(), true);
				}
			}
			else {
				int width = mouseEvent.global_x - getPosX();
				if (width >= 50) {
					resizeWindow(width, getHieght(), true);
				}
			}
		}
		else {
			if (_inBorder_y_top) {
				int hieght = getPosY() + getHieght() - mouseEvent.global_y;
				if (hieght >= 13) {
					resizeWindow(getPosX(), mouseEvent.global_y, getWidth(), hieght, true);
				}
			}
			else {
				int hieght = mouseEvent.global_y - getPosY();
				if (hieght >= 13) {
					resizeWindow(getWidth(), hieght, true);
				}
			}
		}
	}
}