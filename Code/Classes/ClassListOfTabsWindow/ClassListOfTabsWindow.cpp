#include "stdafx.h"
#include "ClassListOfTabsWindow.h"

namespace explorer {

	TabbedWindow::TabbedWindow()
	{
		registerHendler(METHOD(&TabbedWindow::paintHandler));

		_listOfDirs.push_back(std::wstring(L"AzZAZaszas"));
		_listOfDirs.push_back(std::wstring(L"Krkrkkekekek"));
		_listOfDirs.push_back(std::wstring(L""));
	}

	void TabbedWindow::eventCreateWindow()
	{
		int width = getWidth();
		newTubButton.create(
			*this,
			width - 38,
			5,
			30,
			30,
			true
		);


	}

	void TabbedWindow::paintHandler(Gdiplus::Graphics& graphics)
	{
		Gdiplus::SolidBrush textBrush(Gdiplus::Color(254, 0, 0, 0));
		Gdiplus::Font textFont(&Gdiplus::FontFamily(L"Arial"), 12);
		Gdiplus::Pen penBottomLine(Gdiplus::Color(50, 0, 0, 0));

		Gdiplus::StringFormat stringFormat(Gdiplus::StringFormatFlags::StringFormatFlagsNoClip);
		stringFormat.SetLineAlignment(Gdiplus::StringAlignmentCenter);
		stringFormat.SetAlignment(Gdiplus::StringAlignmentNear);

		Gdiplus::RectF rect;
		rect.X = 10;
		rect.Y = headHeight;
		rect.Width = getWidth() - 20;
		rect.Height = 30;

		int widthLine = getWidth() - 20;
		penBottomLine.SetBrush(&Gdiplus::LinearGradientBrush(
			Gdiplus::Point(10 + widthLine, 0),
			Gdiplus::Point(10, 0),
			Gdiplus::Color(0, 0, 0, 0),
			Gdiplus::Color(32, 0, 0, 0)
		));

		for (auto& str : _listOfDirs) {
			graphics.DrawLine(&penBottomLine,
				Gdiplus::Point(10, rect.Y + rect.Height),
				Gdiplus::Point(10 + widthLine, rect.Y + rect.Height)
			);

			if (str.empty()) {
				str = L"Компьютер";
			}
			graphics.DrawString(
				str.c_str(),
				-1,
				&textFont,
				rect,
				&stringFormat,
				&textBrush
			);
			rect.Y += 30;
		}
	}

	void TabbedWindow::mouseMoveHandler(MouseEvent mouseEvent)
	{

	}

	void TabbedWindow::updateList(std::list <std::wstring> list)
	{

	}
}