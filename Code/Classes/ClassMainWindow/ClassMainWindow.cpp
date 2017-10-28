#include "stdafx.h"
#include "ClassMainWindow.h"

namespace explorer {
	MainWindow::MainWindow()
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


		Gdiplus::Font font(&Gdiplus::FontFamily(L"Arial"), 12);
		Gdiplus::SolidBrush textbrush(Gdiplus::Color(255, 255, 255));
		Gdiplus::Point point(3, 20);
		graphics.DrawString(L"Test � �� �����", -1, &font, Gdiplus::PointF(3, 20), &lbrush);
	
	}

	void MainWindow::createWindow()
	{
		setDoubleBuffered(true);
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
		// ��������� ������� ����!

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