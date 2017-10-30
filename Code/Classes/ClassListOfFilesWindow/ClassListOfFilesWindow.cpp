#include "stdafx.h"
#include "ClassListOfFilesWindow.h"

namespace explorer {

	ListOfFiles::ListOfFiles() : _activeLine(-1), _selectedLine(-1)
	{
		m_registerHendler(METHOD(&ListOfFiles::paintHandler));
		m_registerHendler(METHOD(&ListOfFiles::mouseClickHandler));
		m_registerHendler(METHOD(&ListOfFiles::mouseMoveHandler));
		m_registerHendler(METHOD(&ListOfFiles::resizeParentHandler));

		_thisDirection = L"";
		_inDrive = false;
		setResizeWhenParentResizeing(true, true);
	}

	void ListOfFiles::createWindow()
	{
		setDoubleBuffered(true);
		updateList();
	}

	void ListOfFiles::paintHandler(Gdiplus::Graphics& graphics)
	{
		Gdiplus::SolidBrush background(LISTBOX_COLOR_BACKGROUND);
		graphics.FillRectangle(&background, 0, 0, getWidth(), getHieght());

		Gdiplus::Font font(&Gdiplus::FontFamily(L"Arial"), 8);
		Gdiplus::SolidBrush textBrush(LISTBOX_TEXT_COLOR);

		Gdiplus::Pen borderPen(LISTBOX_COLOR_BORDER_LINE);
		Gdiplus::SolidBrush selectBackground(LISTBOX_COLOR_BACKGROUND_SELECT);
		Gdiplus::SolidBrush hoverBackground(LISTBOX_COLOR_BACKGROUND_HOVER);

		/*Тест выделения*/
		//graphics.FillRectangle(&selectBackground, 0, 0, getWidth() - 1, LISTBOX_LINE_HEIGHT - 1);
		//graphics.DrawRectangle(&borderPen, 0, 0, getWidth() - 1, LISTBOX_LINE_HEIGHT - 1);

		if (_activeLine >= 0 && _activeLine != _selectedLine) {
			graphics.FillRectangle(&hoverBackground,
				0, LISTBOX_LINE_HEIGHT * _activeLine,
				getWidth() - 1, LISTBOX_LINE_HEIGHT - 1
			);
			graphics.DrawRectangle(&borderPen,
				0, LISTBOX_LINE_HEIGHT * _activeLine,
				getWidth() - 1, LISTBOX_LINE_HEIGHT - 1
			);
		}
		if (_selectedLine >= 0) {
			graphics.FillRectangle(&selectBackground,
				0, LISTBOX_LINE_HEIGHT * _selectedLine,
				getWidth() - 1, LISTBOX_LINE_HEIGHT - 1
			);
			graphics.DrawRectangle(&borderPen,
				0, LISTBOX_LINE_HEIGHT * _selectedLine,
				getWidth() - 1, LISTBOX_LINE_HEIGHT - 1
			);
		}
		/*Тест выделения*/

		graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);

		int y_offset = 0;
		int textOffset = (LISTBOX_LINE_HEIGHT - font.GetSize()) / 4;

		for (auto name : _thisCatalog) {
			graphics.DrawString(
				name.c_str(),
				-1,
				&font,
				Gdiplus::PointF(LISTBOX_TEXT_POS_X, y_offset + textOffset),
				&textBrush
			);
			y_offset += LISTBOX_LINE_HEIGHT;
		}

	}

	void ListOfFiles::mouseClickHandler(const MouseEventClick& mouseEventClick)
	{
		if (mouseEventClick.Click == MOUSE_CLICK_ONE 
			&& mouseEventClick.Button == MOUSE_LEFT
			&& mouseEventClick.Status == KEY_PRESSED) {
			calcOneLeftClick(mouseEventClick);
		}
		else if (mouseEventClick.Click == MOUSE_CLICK_DOUBLE
			&& mouseEventClick.Button == MOUSE_LEFT) {
			calcDoubleLeftClick(mouseEventClick);
		}
	}

	void ListOfFiles::mouseMoveHandler(MouseEvent& mouseEvent)
	{
		int filesCount = _thisCatalog.size();
		int oldLine = _activeLine;
		if (mouseEvent.y <= (filesCount * LISTBOX_LINE_HEIGHT) - 1) {
			_activeLine = int(mouseEvent.y / LISTBOX_LINE_HEIGHT);
		}
		else {
			_activeLine = -1;
		}

		if (oldLine != _activeLine) {
			RECT oldLineRect;
			RECT newLineRect;
			oldLineRect.left = newLineRect.left = 0;
			oldLineRect.right = newLineRect.right = getWidth();

			oldLineRect.top = oldLine * LISTBOX_LINE_HEIGHT;
			oldLineRect.bottom = oldLine * LISTBOX_LINE_HEIGHT + LISTBOX_LINE_HEIGHT;

			newLineRect.top = _activeLine * LISTBOX_LINE_HEIGHT;
			newLineRect.bottom = _activeLine * LISTBOX_LINE_HEIGHT + LISTBOX_LINE_HEIGHT;

			InvalidateRect(getHWND(), &oldLineRect, false);
			if (_activeLine >= 0) {
				InvalidateRect(getHWND(), &newLineRect, false);
			}
		}
	}

	void ListOfFiles::resizeParentHandler(const ParentEvent& parentEvent)
	{
	}

	
	std::wstring ListOfFiles::getCurrentDirectory()
	{
		return _thisDirection;
	}
	void ListOfFiles::setCurrentDirectory(std::wstring& directory)
	{
		_thisDirection = directory;
		updateList();
	}

	void ListOfFiles::updateButtonUP(bool lock)
	{
		ButtonReturn::buttons[ButtonReturn::BUTTON_RETURN_UP]->setLock(lock);
		ButtonReturn::buttons[ButtonReturn::BUTTON_RETURN_UP]->redrawWindow(false);
	}


	void ListOfFiles::updateList()
	{
		if (!_thisDirection.empty()) {
			File file(_thisDirection);
			_thisCatalog = file.list(L"*");
			_inDrive = true;
			updateButtonUP(false);
		}
		else {
			_logicalDrives = File::getAllLogicalDrives();
			_inDrive = false;

			_thisCatalog.clear();
			for (auto drive : _logicalDrives) {
				_thisCatalog.push_back(drive.first);
			}
			updateButtonUP(true);
		}
		redrawWindow(false);
		_activeLine = -1;
		_selectedLine = -1;
	}

	void ListOfFiles::calcOneLeftClick(const MouseEventClick& mouseEventClick)
	{
		int filesCount = _thisCatalog.size();
		int oldLine = _selectedLine;
		if (mouseEventClick.y <= (filesCount * LISTBOX_LINE_HEIGHT) - 1) {
			_selectedLine = int(mouseEventClick.y / LISTBOX_LINE_HEIGHT);
		}
		else {
			_selectedLine = -1;
		}

		if (oldLine != _selectedLine) {
			RECT oldLineRect;
			RECT newLineRect;
			oldLineRect.left = newLineRect.left = 0;
			oldLineRect.right = newLineRect.right = getWidth();

			oldLineRect.top = oldLine * LISTBOX_LINE_HEIGHT;
			oldLineRect.bottom = oldLine * LISTBOX_LINE_HEIGHT + LISTBOX_LINE_HEIGHT;

			newLineRect.top = _activeLine * LISTBOX_LINE_HEIGHT;
			newLineRect.bottom = _activeLine * LISTBOX_LINE_HEIGHT + LISTBOX_LINE_HEIGHT;

			InvalidateRect(getHWND(), &oldLineRect, false);
			if (_selectedLine >= 0) {
				InvalidateRect(getHWND(), &newLineRect, false);
			}
		}
	}
	void ListOfFiles::calcDoubleLeftClick(const MouseEventClick& mouseEventClick)
	{
		int filesCount = _thisCatalog.size();
		int oldLine = _selectedLine;
		if (mouseEventClick.y <= (filesCount * LISTBOX_LINE_HEIGHT) - 1) {
			_selectedLine = int(mouseEventClick.y / LISTBOX_LINE_HEIGHT);
		}
		else {
			_selectedLine = -1;
		}

		if (oldLine != _selectedLine) {
			RECT oldLineRect;
			RECT newLineRect;
			oldLineRect.left = newLineRect.left = 0;
			oldLineRect.right = newLineRect.right = getWidth();

			oldLineRect.top = oldLine * LISTBOX_LINE_HEIGHT;
			oldLineRect.bottom = oldLine * LISTBOX_LINE_HEIGHT + LISTBOX_LINE_HEIGHT;

			newLineRect.top = _activeLine * LISTBOX_LINE_HEIGHT;
			newLineRect.bottom = _activeLine * LISTBOX_LINE_HEIGHT + LISTBOX_LINE_HEIGHT;

			InvalidateRect(getHWND(), &oldLineRect, false);
			if (_selectedLine >= 0) {
				InvalidateRect(getHWND(), &newLineRect, false);
			}
		}

		if (_selectedLine >= 0) {
			if (!_thisDirection.empty() && _thisDirection[_thisDirection.size() - 1] != '\\') {
				_thisDirection += '\\';
			}
			std::wstring newDirection = _thisDirection + _thisCatalog[_selectedLine];
			File file(newDirection);
			if (file.isDirectory()) {
				ButtonReturn::nextDirrectory(_thisDirection);
				setCurrentDirectory(newDirection);
			}
		}

		//_thisDirection = _thisCatalog[_selectedLine];
		//updateList();
	}
}