#include "ClassMainWindow.h"

namespace Explorer {
	MainWindow::MainWindow()
	{
		registerWindowHandlers();
	}



	void MainWindow::registerWindowHandlers()
	{
		m_registerHendler(WM_LBUTTONDOWN, std::bind(&MainWindow::createHandler, this, (HWND)1, (WPARAM)2, (LPARAM)3));
	}

	LRESULT MainWindow::createHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		MessageBox(nullptr, L"IT'S WORK!!!", L"TEST", MB_OK);
		return 0;
	}
}