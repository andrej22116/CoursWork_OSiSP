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

		std::map<int, std::wstring> map;
		map.insert(std::pair<int, std::wstring>(0, std::wstring(L"AzZAZaszas")));
		map.insert(std::pair<int, std::wstring>(1, std::wstring(L"Krkrkkekekek")));
		map.insert(std::pair<int, std::wstring>(2, std::wstring(L"")));
		updateTabsMap(map);
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
		for (auto&& tab : _listOfTabs) {
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

			graphics.DrawString(
				tab.second.first.c_str(),
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
			&& mouseEventClick.Button == MouseKeyCodes::MOUSE_LEFT
			&& mouseEventClick.Status == KeyStatus::KEY_PRESSED) {
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

			int i = 0;
			for (auto button : _listOfTabs) {
				if (i == oldLine) {
					button.second.second->setSelect(false);
				}
				if (i == _hoveredLine) {
					button.second.second->setSelect(true);
				}
				i++;
			}
		}
	}


	void TabbedWindow::registerUpdateHandler(UpdateTabsListHandler handler)
	{
		_listOfHandlers.push_back(handler);
	}
	void TabbedWindow::callAllHandlers(int tabKey, TabEvent tabEvent)
	{
		for (auto handler : _listOfHandlers) {
			handler(tabKey, tabEvent);
		}
	}


	void TabbedWindow::updateTabsMap(std::map<int, std::wstring> mapOfTabs)
	{
		typedef std::pair<int, std::pair<std::wstring, std::shared_ptr<CloseTabButton>>> LineInfo;
		_listOfTabs.erase(_listOfTabs.begin(), _listOfTabs.end());

		for (auto&& pair : mapOfTabs) {
			LineInfo info;
			info.first = pair.first;
			info.second.first = pair.second;
			if (info.second.first.empty()) {
				info.second.first = L"Компьютер";
			}
			info.second.second = std::make_shared<CloseTabButton>();
			_listOfTabs.insert(info);
		}

		int pos_x = getWidth() - 33;
		int pos_y = headHeight + int(_lineHeight / 2) - 10;
		for (auto&& pair : _listOfTabs) {
			pair.second.second->create(*this, pos_x, pos_y, 20, 20, true);
			pos_y += _lineHeight;
		}
		redrawWindow(false);
	}
	void TabbedWindow::updateOneTab(int tabKey, std::wstring newString)
	{
		if (_listOfTabs.find(tabKey) != _listOfTabs.end()) {
			_listOfTabs[tabKey].first = newString;
		}
		redrawWindow(false);
	}
	void TabbedWindow::deleteOneTab(int tabKey)
	{
		if (_listOfTabs.find(tabKey) != _listOfTabs.end()) {
			_listOfTabs[tabKey].second->destroy();
		}
	}

	void TabbedWindow::update()
	{
		redrawWindow(false);
		moveButtons();
	}

	void TabbedWindow::moveButtons()
	{
		int y = headHeight + int(_lineHeight / 2) - 10 - getVerticalSckrollStatus();
		for (auto&& tab : _listOfTabs) {
			int x = tab.second.second->getPosX();
			tab.second.second->moveWindowPos(x, y, false);
			y += _lineHeight;
		}
	}
}