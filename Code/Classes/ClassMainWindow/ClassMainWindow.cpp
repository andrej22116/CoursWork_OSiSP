#include "ClassMainWindow.h"

namespace Explorer {
	MainWindow::MainWindow(int pos_x, int pos_y) :
		Window(
			L"Window",
			pos_x,
			pos_y,
			800,
			600
		)
	{
		registerWindowHandlers();
	}
	MainWindow::MainWindow(int pos_x, int pos_y, int width, int hieght, bool show) :
		Window(
			L"Window",
			pos_x,
			pos_y,
			width,
			hieght
		)
	{
		registerWindowHandlers();
	}
	MainWindow::MainWindow(std::wstring name, int pos_x, int pos_y, int width, int hieght, bool show) :
		Window(
			name,
			pos_x,
			pos_y,
			width,
			hieght
		)
	{
		registerWindowHandlers();
	}



	void MainWindow::registerWindowHandlers()
	{
		registerHendler(WM_LBUTTONDOWN, std::bind(&MainWindow::createHandler, this, (HWND)1, (WPARAM)2, (LPARAM)3));
	}

	LRESULT MainWindow::createHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		MessageBox(nullptr, L"IT'S WORK!!!", L"TEST", MB_OK);
		return 0;
	}
}