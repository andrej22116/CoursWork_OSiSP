#include <Windows.h>
#include "Classes\ClassMainWindow\ClassMainWindow.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR kek, int show)
{
	Explorer::MainWindow window;
	window.create(L"Suka", 100, 100, 300, 300, true);

	Explorer::MainWindow window_2;
	window_2.create(L"Pizda", window, 0, 0, 200, 200, true);


	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}