#include "ClassMainWindow.h"

namespace explorer {
	MainWindow::MainWindow()
	{
		registerWindowHandlers();
	}



	void MainWindow::registerWindowHandlers()
	{
		m_registerHendler(WM_CREATE, std::bind(&MainWindow::createHandler, this, (HWND)1, (WPARAM)2, (LPARAM)3));
	}

	LRESULT MainWindow::createHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		MessageBox(nullptr, (L"IT'S WORK!!!" + getWindowName()).c_str(), L"TEST", MB_OK);
		return 0;
	}
}