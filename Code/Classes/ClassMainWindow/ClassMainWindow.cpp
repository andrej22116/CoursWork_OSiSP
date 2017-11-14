#include "stdafx.h"
#include "ClassMainWindow.h"

#include <dwmapi.h>
#pragma comment(lib, "Dwmapi.lib")
#include <stdio.h>

struct WINCOMPATTRDATA {
	DWORD attribute;
	PVOID pData;
	ULONG dataSize;
};
struct AccentPolicy {
	int AccentState;
	int AccentFlags;
	int GradientColor;
	int AnimationId;
};

typedef BOOL (WINAPI *SWCA)(HWND, WINCOMPATTRDATA*);

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
		m_registerTimerHendler(METHOD(&MainWindow::updateBatteryStatusTimerHandler));

		setHeader(true);
		setResizebleAll(true, true, true, true);
		setMinSize(20 * 4 + 3 * 24 + 2, MAIN_WINDOW_BORDER_SIZE * 2 + MAIN_WINDOW_HEADER_HEIGHT * 2 - 3);

		_batteryStatus = -1;
		//setBorderSize(3);
	}

	void MainWindow::paintHandler(Gdiplus::Graphics& graphics)
	{
		Gdiplus::SolidBrush brush_2(MAIN_WINDOW_COLOR_BACKGROUND);
		Gdiplus::Rect region_2(0, 0, this->getWidth(), this->getHieght());
		graphics.FillRectangle(&brush_2, region_2);

		if (_batteryFound) {
			Gdiplus::Pen batteryBorderPen(Gdiplus::Color(254, 200, 200, 200));
			Gdiplus::SolidBrush batteryStatus(
				_batteryStatus > 15 ?
				Gdiplus::Color(254, 200, 200, 200) :
				Gdiplus::Color(254, 255, 61, 0)
			);
			Gdiplus::SolidBrush battaryStatusNum(Gdiplus::Color(254, 200, 200, 200));
			Gdiplus::Font font(&Gdiplus::FontFamily(L"Arial"), 8, Gdiplus::FontStyleBold);
			Gdiplus::StringFormat stringFormat(Gdiplus::StringFormatFlags::StringFormatFlagsNoClip);
			stringFormat.SetLineAlignment(Gdiplus::StringAlignmentCenter);
			stringFormat.SetAlignment(Gdiplus::StringAlignmentFar);

			int width = getWidth();
			int height = getHieght();

			Gdiplus::RectF rect;
			rect.X = width - 20;
			rect.Y = height - MAIN_WINDOW_HEADER_HEIGHT + 4;
			rect.Width = 20 - MAIN_WINDOW_BORDER_SIZE - 2;
			rect.Height = MAIN_WINDOW_HEADER_HEIGHT - 10;

			graphics.DrawRectangle(&batteryBorderPen, rect);
			graphics.DrawLine(&batteryBorderPen,
				rect.X - 1, rect.Y + 3,
				rect.X - 1, rect.Y + rect.Height - 3
			);

			rect.X += 2;
			rect.Y += 2;
			rect.Width -= 3;
			rect.Height -= 3;

			Gdiplus::RectF rectText(rect);
			rectText.Y--;
			rectText.Width += 20;
			rectText.X -= rectText.Width + 4;
			float procent = rect.Width * float(_batteryStatus) / 100.0f;
			rect.X += rect.Width - procent;
			rect.Width = procent;

			graphics.FillRectangle(&batteryStatus, rect);
			graphics.DrawString(
				(std::to_wstring(_batteryStatus)+L" %").c_str(),
				-1,
				&font,
				rectText,
				&stringFormat,
				&battaryStatusNum
			);
		}	
	}

	void MainWindow::eventCreateWindow()
	{
		auto version = getSystemVersion();
		int major = version.first;
		int minor = version.second;

		if (major == 6 && minor <= 1) {
			DWM_BLURBEHIND lol;
			//HRGN rgn = CreateRectRgn(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
			HRGN rgn = CreateRectRgn(-1, -1, 0, 0);
			lol.dwFlags = DWM_BB_BLURREGION | DWM_BB_ENABLE;
			lol.hRgnBlur = rgn;
			lol.fEnable = true;
			lol.fTransitionOnMaximized = false;

			DWORD color = 0xFF123456;
			BOOL blend = true;
			if (DwmGetColorizationColor(&color, &blend) == S_OK) {
				DwmEnableBlurBehindWindow(getHWND(), &lol);
			}
			DeleteObject(rgn);
		}
		else if (major == 6 && minor > 1) {
			HINSTANCE le_module = LoadLibrary(L"user32.dll");
			if (le_module) {
				auto SetWindowCompositionAttribute = (SWCA)GetProcAddress(le_module, "SetWindowCompositionAttribute");
				if (SetWindowCompositionAttribute) {
					WINCOMPATTRDATA data;
					AccentPolicy policy = { 0, 0, 0, 229 };
					policy.AccentFlags = 2;
					policy.AccentState = 3;
					policy.GradientColor = 0x44ffffff;

					data.attribute = 19;
					data.pData = &policy;
					data.dataSize = sizeof(policy);

					SetWindowCompositionAttribute(getHWND(), &data);
				}
				FreeLibrary(le_module);
			}
		}
		redrawWindow(false);

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
			getHieght() - MAIN_WINDOW_HEADER_HEIGHT - LISTBOX_POS_Y - 1,
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
		windowOptions.create(
			std::wstring(L"windowoptions"),
			*this,
			0,
			MAIN_WINDOW_HEADER_HEIGHT+1,
			350,
			getHieght() - MAIN_WINDOW_HEADER_HEIGHT - 2,
			false
		);

		setTimer(100, 1000);
		/*windowOptions.show(false);*/
		//MessageBox(nullptr, (L"IT'S WORK!!! " + getWindowName()).c_str(), L"TEST", MB_OK);
	}

	void MainWindow::mouseClickHandler(const MouseEventClick& mouseEventClick)
	{
		// вычлинить двойной клик!

		if (mouseEventClick.Button == MOUSE_LEFT && mouseEventClick.Status == KEY_PRESSED && !buttonMaximize.isMaximized()) {
			if (windowOptions.isShow()) {
				windowOptions.show(false);
			}
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


	bool MainWindow::windowOptionsIsShow()
	{
		return windowOptions.isShow();
	}
	void MainWindow::showWindowOptions(bool show)
	{
		windowOptions.show(show);
	}

	void MainWindow::updateBatteryStatusTimerHandler(int timerID)
	{
		SYSTEM_POWER_STATUS sps;
		if (GetSystemPowerStatus(&sps)) {
			_batteryFound = true;
			if (sps.BatteryFlag == 255 || sps.BatteryFlag == 128) {
				killTimer(timerID);
				_batteryFound = false;
				return;
			}
			if (_batteryStatus == (int)sps.BatteryLifePercent) {
				return;
			}

			_isCharging = (bool)sps.ACLineStatus;
			_batteryStatus = (int)sps.BatteryLifePercent;

			int width = getWidth();
			int height = getHieght();

			RECT rect;
			rect.left = width - 50;
			rect.top = height - MAIN_WINDOW_HEADER_HEIGHT;
			rect.right = width - MAIN_WINDOW_BORDER_SIZE;
			rect.bottom = height;

			InvalidateRect(getHWND(), &rect, false);
		}
		else {
			killTimer(timerID);
			_batteryFound = false;
		}
	}
}