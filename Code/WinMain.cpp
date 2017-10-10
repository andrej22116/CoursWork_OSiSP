#include "stdafx.h"
#include "Classes\ClassMainWindow\ClassMainWindow.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR kek, int show)
{
	explorer::MainWindow window;
	window.create(L"Suka", 100, 100, 300, 300, true);

	return explorer::Window::workWidthMessages();
}