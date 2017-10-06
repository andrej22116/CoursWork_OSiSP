#include <Windows.h>
#include "Classes\ClassMainWindow\ClassMainWindow.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR kek, int show)
{
	Explorer::MainWindow window(0,0);
	Explorer::MainWindow window_2(L"Pizda", 100, 100, 200, 200, true);


	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}