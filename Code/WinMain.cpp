#include "stdafx.h"
#include "Includes\Ivents\Ivents.h"
#include "Classes\ClassMainWindow\ClassMainWindow.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR kek, int show)
{
	explorer::MainWindow window;
	window.create(std::wstring(L"Test Window Explorer"), 100, 100, 600, 600, true);

	/*
	explorer::Window window;
	explorer::Window child;
	window.setHeader(true);
	window.setBorderSize(5);
	window.setResizebleAll(true, true, true, true);

	bool clickParent = false;
	bool clickChild = false;
	bool& clickParentMask = clickParent;
	bool& clickChildMask = clickChild;

	auto paintHadler = [&clickParentMask](Gdiplus::Graphics& graphics) {
		graphics.Clear(Gdiplus::Color::BurlyWood);

		Gdiplus::SolidBrush brush(!clickParentMask ? Gdiplus::Color::Crimson : Gdiplus::Color::Fuchsia);
		Gdiplus::Font font(&Gdiplus::FontFamily(L"Arial"), 24);
		
		graphics.DrawString(L"Тест пройден!", -1, &font, Gdiplus::PointF(20, 20), &brush);
	};
	auto paintHadler_2 = [&clickChildMask](Gdiplus::Graphics& graphics) {
		graphics.Clear(Gdiplus::Color::Chartreuse);

		Gdiplus::SolidBrush brush(!clickChildMask ? Gdiplus::Color::Fuchsia : Gdiplus::Color::Crimson);

		graphics.FillEllipse(&brush, 0, 0, 99, 99);
		//graphics.DrawString(L"Тест пройден!", -1, &font, Gdiplus::PointF(20, 20), &brush);
	};

	auto clickHadler = [&clickChildMask, &child](const explorer::MouseEventClick& mouseEventClick) {
		if (mouseEventClick.Status == explorer::KeyStatus::KEY_PRESSED)
			clickChildMask = !clickChildMask;
		child.redrawWindow(false);
	};
	auto clickHadler_2 = [&clickParentMask, &window](const explorer::MouseEventClick& mouseEventClick) {
		if (mouseEventClick.Status == explorer::KeyStatus::KEY_PRESSED)
			clickParentMask = !clickParentMask;
		window.redrawWindow(false);
	};

	window.registerHendler(paintHadler);
	window.registerHendler(clickHadler);
	child.registerHendler(paintHadler_2);
	child.registerHendler(clickHadler_2);
	window.create(std::wstring(L"Test window!"), 20, 20, 800, 600, true);
	child.create(window, 100, 100, 100, 100, true);
	*/

	return explorer::Window::workWidthMessages();
}