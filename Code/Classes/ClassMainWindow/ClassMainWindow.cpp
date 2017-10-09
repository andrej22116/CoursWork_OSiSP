#include "stdafx.h"
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
		buttonClose.create(L"Pizda", *this, 0, 0, 200, 200, true);
		//MessageBox(nullptr, (L"IT'S WORK!!! " + getWindowName()).c_str(), L"TEST", MB_OK);
		return 0;
	}
}