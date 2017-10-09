#include "stdafx.h"
#include "ClassButtonCloseWindow.h"

namespace explorer {

	ButtonClose::ButtonClose()
	{
		m_registerHendler(WM_LBUTTONDOWN, std::bind(&ButtonClose::closeHandler, this, (HWND)1, (WPARAM)2, (LPARAM)3));
	}

	LRESULT ButtonClose::closeHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		m_sendMessageForParent(WM_CLOSE, 0, 0);
		return 0;
	}

}