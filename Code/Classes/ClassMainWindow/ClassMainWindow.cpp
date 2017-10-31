#include "stdafx.h"
#include "ClassMainWindow.h"

namespace explorer {
	MainWindow::MainWindow() : 
		buttonUp(&listOfFiles, ButtonReturn::BUTTON_RETURN_UP),
		buttonForward(&listOfFiles, ButtonReturn::BUTTON_RETURN_FORWARD),
		buttonBackward(&listOfFiles, ButtonReturn::BUTTON_RETURN_BACKWARD),
		buttonOptions(&listOfFiles)
	{
		m_registerHendler(METHOD(&MainWindow::paintHandler));
		m_registerHendler(METHOD(&MainWindow::mouseClickHandler));
		m_registerHendler(METHOD(&MainWindow::mouseMoveHandler));
		m_registerHendler(METHOD(&MainWindow::keyboardHandler));

		setHeader(true);
		setResizebleAll(true, true, true, true);

		//setBorderSize(3);
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
	
	}

	void MainWindow::createWindow()
	{
		setDoubleBuffered(true);
		buttonClose.create(
			std::wstring(L"exit"),
			*this,
			MAIN_WINDOW_BUTTON_EXIT_POS_X(this->getWidth()),
			MAIN_WINDOW_BUTTON_EXIT_POS_Y(1),
			MAIN_WINDOW_BUTTON_EXIT_WIDTH,
			MAIN_WINDOW_BUTTON_EXIT_HEIGHT,
			true);

		buttonMaximize.create(
			std::wstring(L"maximize"),
			*this,
			MAIN_WINDOW_BUTTON_MAXIMIZE_POS_X(this->getWidth()),
			MAIN_WINDOW_BUTTON_MAXIMIZE_POS_Y(1),
			MAIN_WINDOW_BUTTON_MAXIMIZE_WIDTH,
			MAIN_WINDOW_BUTTON_MAXIMIZE_HEIGHT,
			true);

		buttonMinimize.create(
			std::wstring(L"minimize"),
			*this,
			MAIN_WINDOW_BUTTON_MINIMIZE_POS_X(this->getWidth()),
			MAIN_WINDOW_BUTTON_MINIMIZE_POS_Y(1),
			MAIN_WINDOW_BUTTON_MINIMIZE_WIDTH,
			MAIN_WINDOW_BUTTON_MINIMIZE_HEIGHT,
			true);
		listOfFiles.create(
			std::wstring(L"ListOfFiles"),
			*this,
			LISTBOX_POS_X,
			LISTBOX_POS_Y,
			getWidth() - MAIN_WINDOW_BORDER_SIZE - LISTBOX_POS_X - 1,
			getHieght() - MAIN_WINDOW_BORDER_SIZE - LISTBOX_POS_Y - 1,
			true
		);
		buttonOptions.create(
			std::wstring(L"ButtonOptions"),
			*this,
			MAIN_WINDOW_BUTTON_OPTIONS_POS_X,
			MAIN_WINDOW_BUTTON_OPTIONS_POS_Y,
			MAIN_WINDOW_BUTTON_OPTIONS_WIDTH,
			MAIN_WINDOW_BUTTON_OPTIONS_HEIGHT,
			true
		);
		buttonUp.create(
			std::wstring(L"ButtonUp"),
			*this,
			MAIN_WINDOW_BUTTON_UP_POS_X,
			MAIN_WINDOW_BUTTON_UP_POS_Y,
			MAIN_WINDOW_BUTTON_UP_WIDTH,
			MAIN_WINDOW_BUTTON_UP_HEIGHT,
			true
		);
		buttonForward.create(
			std::wstring(L"ButtonForward"),
			*this,
			MAIN_WINDOW_BUTTON_FORWARD_POS_X,
			MAIN_WINDOW_BUTTON_FORWARD_POS_Y,
			MAIN_WINDOW_BUTTON_FORWARD_WIDTH,
			MAIN_WINDOW_BUTTON_FORWARD_HEIGHT,
			true
		);
		buttonBackward.create(
			std::wstring(L"ButtonBackward"),
			*this,
			MAIN_WINDOW_BUTTON_BACKWARD_POS_X,
			MAIN_WINDOW_BUTTON_BACKWARD_POS_Y,
			MAIN_WINDOW_BUTTON_BACKWARD_WIDTH,
			MAIN_WINDOW_BUTTON_BACKWARD_HEIGHT,
			true
		);
		//MessageBox(nullptr, (L"IT'S WORK!!! " + getWindowName()).c_str(), L"TEST", MB_OK);
	}

	void MainWindow::mouseClickHandler(const MouseEventClick& mouseEventClick)
	{
		// вычлинить двойной клик!

		if (mouseEventClick.Button == MOUSE_LEFT && mouseEventClick.Status == KEY_PRESSED && !buttonMaximize.isMaximized()) {
		}
		else if (mouseEventClick.Button == MOUSE_LEFT && mouseEventClick.Status == KEY_RELEASED) {
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
	}
}