#include "stdafx.h"
#include "ClassListOfTabsWindow.h"

namespace explorer {

	TabbedWindow::TabbedWindow()
	{
		registerHendler(METHOD(&TabbedWindow::paintHandler));
		registerHendler(METHOD(&TabbedWindow::mouseMoveHandler));
		registerHendler(METHOD(&TabbedWindow::mouseClickHandler));

		_listOfDirs.push_back(std::wstring(L"AzZAZaszas"));
		_listOfDirs.push_back(std::wstring(L"Krkrkkekekek"));
		_listOfDirs.push_back(std::wstring(L""));

		_lineHeight = 30;
		_hoveredLine = -1;
		_selectedLine = -1;
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
		Gdiplus::LinearGradientBrush hoverBrush(
			Gdiplus::Point(0, 0),
			Gdiplus::Point(getWidth(), 0),
			Gdiplus::Color(32, 0, 0, 0),
			Gdiplus::Color(0, 0, 0, 0)
		);
		Gdiplus::SolidBrush selectedBrush(Gdiplus::Color(32, 0, 0, 0));
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
		rect.Height = _lineHeight;
		Gdiplus::RectF selectedRect;
		selectedRect.X = 10;
		selectedRect.Y = headHeight + _lineHeight * _selectedLine;
		selectedRect.Width = getWidth() - 10;
		selectedRect.Height = _lineHeight;

		int widthLine = getWidth() - 20;
		penBottomLine.SetBrush(&Gdiplus::LinearGradientBrush(
			Gdiplus::Point(10 + widthLine, 0),
			Gdiplus::Point(10, 0),
			Gdiplus::Color(0, 0, 0, 0),
			Gdiplus::Color(32, 0, 0, 0)
		));

		int line = 0;
		for (auto& str : _listOfDirs) {
			if (line == _selectedLine) {
				graphics.FillRectangle(&selectedBrush, selectedRect);
			}
			if (line == _hoveredLine) {
				graphics.FillRectangle(&hoverBrush, rect);
			}
			graphics.DrawLine(&penBottomLine,
				Gdiplus::Point(10, rect.Y + rect.Height - 1),
				Gdiplus::Point(10 + widthLine, rect.Y + rect.Height - 1)
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
			line++;
		}
	}

	void TabbedWindow::mouseMoveHandler(MouseEvent& mouseEvent)
	{
		int oldLine = _hoveredLine;

		if (mouseEvent.y < headHeight) {
			_hoveredLine = -1;
			if (oldLine != _hoveredLine) {
				redrawWindow(false);
			}
			return;
		}

		int linesCount = _listOfDirs.size();
		int line = int((mouseEvent.y - headHeight) / _lineHeight);

		if (line < linesCount) {
			_hoveredLine = line;
		}
		else {
			_hoveredLine = -1;
		}

		if (oldLine != _hoveredLine) {
			redrawWindow(false);
		}
	}

	void TabbedWindow::mouseClickHandler(const MouseEventClick& mouseEventClick)
	{
		if (mouseEventClick.Click == MouseKeyClick::MOUSE_CLICK_ONE
			&& mouseEventClick.Button == MouseKeyCodes::MOUSE_LEFT) {
			int oldLine = _selectedLine;

			if (mouseEventClick.y < headHeight) {
				_selectedLine = -1;
				if (oldLine != _selectedLine) {
					redrawWindow(false);
				}
				return;
			}

			int linesCount = _listOfDirs.size();
			int line = int((mouseEventClick.y - headHeight) / _lineHeight);

			if (line < linesCount) {
				_selectedLine = line;
			}
			else {
				_selectedLine = -1;
			}

			if (oldLine != _selectedLine) {
				redrawWindow(false);
			}
		}
	}

	void TabbedWindow::updateList(std::list <std::wstring> list)
	{

	}
}