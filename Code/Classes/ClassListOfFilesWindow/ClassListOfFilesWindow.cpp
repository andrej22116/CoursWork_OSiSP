#include "stdafx.h"
#include "ClassListOfFilesWindow.h"
#include "..\ClassMainWindow\ClassMainWindow.h"

namespace explorer {

	ListOfFiles::ListOfFiles() : _activeLine(-1), _selectedLine(-1)
	{
		registerHendler(METHOD(&ListOfFiles::paintHandler));
		registerHendler(METHOD(&ListOfFiles::mouseClickHandler));
		registerHendler(METHOD(&ListOfFiles::mouseMoveHandler));
		registerHendler(METHOD(&ListOfFiles::resizeParentHandler));

		_thisDirection = L"";
		_inDrive = false;
		setResizeWhenParentResizeing(true, true);
		activateVerticalScrollbarIfRenderBufferHeightMoreThanHeightWindow(true);

		setVerticalSckrollStepSize(30);
	}

	void ListOfFiles::eventCreateWindow()
	{
		//updateList();
	}
	void ListOfFiles::eventSizeWindow(int oldWidth, int oldHeight)
	{
		int verStatus = getVerticalSckrollStatus();
		int maxStatus = _thisCatalog.size() * LISTBOX_LINE_HEIGHT - getHieght();
		if (maxStatus <= 0) {
			verStatus = 0;
		}
		else if (verStatus > maxStatus) {
			verStatus = maxStatus;
		}
		setVerticalSckrollStatus(verStatus);

		setRenderBufferSize(getWidth(), _thisCatalog.size() * LISTBOX_LINE_HEIGHT);
	}

	void ListOfFiles::paintHandler(Gdiplus::Graphics& graphics)
	{
		int amountOfLines = _thisCatalog.size() * LISTBOX_LINE_HEIGHT;
		int HeightOfRectangleForFill = max(amountOfLines, this->getHieght());
		Gdiplus::SolidBrush background(LISTBOX_COLOR_BACKGROUND);

		graphics.Clear(LISTBOX_COLOR_BACKGROUND);
		//graphics.FillRectangle(&background, 0, 0, getWidth(), HeightOfRectangleForFill);

		Gdiplus::Font font(&Gdiplus::FontFamily(L"Arial"), 10, Gdiplus::FontStyleBold);
		Gdiplus::SolidBrush textBrush(Gdiplus::Color(254, 255, 255, 255));

		Gdiplus::Pen borderPen(LISTBOX_COLOR_BORDER_LINE);
		Gdiplus::Pen borderHoverPen(LISTBOX_COLOR_BORDER_HOVER_LINE);
		Gdiplus::SolidBrush selectBackground(LISTBOX_COLOR_BACKGROUND_SELECT);
		Gdiplus::SolidBrush hoverBackground(LISTBOX_COLOR_BACKGROUND_HOVER);

		graphics.DrawLine(&borderPen, 0, 0, 0, LISTBOX_LINE_HEIGHT * _thisCatalog.size() - 1);

		if (_selectedLine >= 0) {
			graphics.FillRectangle(&selectBackground,
				0, LISTBOX_LINE_HEIGHT * _selectedLine,
				getWidth(), LISTBOX_LINE_HEIGHT - 1
			);
			
			graphics.DrawLine(&borderPen,
				0, LISTBOX_LINE_HEIGHT * _selectedLine,
				getWidth() - 1, LISTBOX_LINE_HEIGHT * _selectedLine);
			graphics.DrawLine(&borderPen,
				0, LISTBOX_LINE_HEIGHT * _selectedLine + LISTBOX_LINE_HEIGHT - 1,
				getWidth() - 1, LISTBOX_LINE_HEIGHT * _selectedLine + LISTBOX_LINE_HEIGHT - 1);
			
			/*
			graphics.FillRectangle(&selectBackground,
				0, LISTBOX_LINE_HEIGHT * _selectedLine,
				getWidth() - 1, LISTBOX_LINE_HEIGHT - 1
			);
			graphics.DrawRectangle(&borderPen,
				0, LISTBOX_LINE_HEIGHT * _selectedLine,
				getWidth() - 1, LISTBOX_LINE_HEIGHT - 1
			);
			*/
		}

		//graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
		if (_activeLine >= 0) {
			if (_selectedLine != _activeLine) {
				graphics.DrawLine(&borderHoverPen,
					0, LISTBOX_LINE_HEIGHT * _activeLine,
					0, LISTBOX_LINE_HEIGHT * (_activeLine + 1) - 1);
			}
			graphics.DrawLine(&borderHoverPen,
				0, LISTBOX_LINE_HEIGHT * _activeLine,
				getWidth() - 1, LISTBOX_LINE_HEIGHT * _activeLine);
			graphics.DrawLine(&borderHoverPen,
				0, LISTBOX_LINE_HEIGHT * _activeLine + LISTBOX_LINE_HEIGHT - 1,
				getWidth() - 1, LISTBOX_LINE_HEIGHT * _activeLine + LISTBOX_LINE_HEIGHT - 1);
			/*
			graphics.FillRectangle(&hoverBackground,
			0, LISTBOX_LINE_HEIGHT * _activeLine,
			getWidth() - 1, LISTBOX_LINE_HEIGHT - 1
			);
			graphics.DrawRectangle(&borderPen,
			0, LISTBOX_LINE_HEIGHT * _activeLine,
			getWidth() - 1, LISTBOX_LINE_HEIGHT - 1
			);
			*/
		}
		/*Тест выделения*/

		//graphics.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
		graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
		//graphics.SetInterpolationMode(Gdiplus::InterpolationMode::InterpolationModeHighQualityBicubic);

		int y_offset = 0;
		int textOffset = (LISTBOX_LINE_HEIGHT - font.GetSize()) / 4;
		int scrollOffset = getVerticalSckrollStatus();
		int firstLineToOut = int(scrollOffset / LISTBOX_LINE_HEIGHT);
		int lastLineToOut = int((scrollOffset + getHieght()) / LISTBOX_LINE_HEIGHT);

		int line = 0;
		for (auto dir : _thisCatalog) {
			if (line >= firstLineToOut && line <= lastLineToOut) {
				if (dir.Icon) {
					graphics.DrawImage(&(*(dir.Icon)),
						3, y_offset + 2,
						LISTBOX_LINE_HEIGHT - 4, LISTBOX_LINE_HEIGHT - 4
					);
				}

				/*
				HDC hDC = graphics.GetHDC();
				if (0 == TextOut(hDC, LISTBOX_TEXT_POS_X, y_offset + textOffset - 1, dir.Name.c_str(), dir.Name.size())) {
					DWORD error = GetLastError();
					_RPT1(0, "Bad textout... error: %d\n", error);
				}
				graphics.ReleaseHDC(hDC);
				*/

				graphics.DrawString(
					dir.Name.c_str(),
					-1,
					&font,
					Gdiplus::PointF(LISTBOX_TEXT_POS_X, y_offset + textOffset),
					&textBrush
				);
				if (line == lastLineToOut) {
					break;
				}
			}
			
			y_offset += LISTBOX_LINE_HEIGHT;
			line++;
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

		int absolutPosY = mouseEvent.y + getVerticalSckrollStatus();

		if (absolutPosY <= (filesCount * LISTBOX_LINE_HEIGHT) - 1) {
			_activeLine = int(absolutPosY / LISTBOX_LINE_HEIGHT);
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
			oldLineRect.bottom = oldLineRect.top + LISTBOX_LINE_HEIGHT;

			newLineRect.top = _activeLine * LISTBOX_LINE_HEIGHT;
			newLineRect.bottom = newLineRect.top + LISTBOX_LINE_HEIGHT;

			//InvalidateRect(getHWND(), &oldLineRect, false);
			//if (_activeLine >= 0) {
			//	InvalidateRect(getHWND(), &newLineRect, false);
			//}
			redrawWindow(false);
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

	void ListOfFiles::updateList()
	{
		if (!_thisDirection.empty()) {
			File file(_thisDirection);
			_thisCatalog = file.list(L"*");
			_inDrive = true;
			_buttonUp->setLock(false);
			_buttonUp->redrawWindow(false);
		}
		else {
			_logicalDrives = File::getAllLogicalDrives();
			_inDrive = false;

			_thisCatalog.clear();
			for (auto drive : _logicalDrives) {
				_thisCatalog.push_back(File::FileInfo(drive.first, false, true, nullptr));
			}
			_buttonUp->setLock(true);
			_buttonUp->redrawWindow(false);
		}

		_activeLine = -1;
		_selectedLine = -1;

		setVerticalSckrollStatus(0);
		setHorizontalSckrollStatus(0);
		setRenderBufferSize(getWidth(), _thisCatalog.size() * LISTBOX_LINE_HEIGHT);

		redrawWindow(false);
	}
	void ListOfFiles::nextDirrectory(std::wstring& oldDirrectory)
	{
		while (!_forwardStack.empty()) {
			_forwardStack.pop();
		}

		_buttonForward->setLock(true);
		_buttonForward->redrawWindow(false);

		_backwardStack.push(oldDirrectory);
		if (_buttonBackward->isLocked()) {
			_buttonBackward->setLock(false);
			_buttonBackward->redrawWindow(false);
		}
	}

	void ListOfFiles::calcOneLeftClick(const MouseEventClick& mouseEventClick)
	{
		int filesCount = _thisCatalog.size();
		int oldLine = _selectedLine;

		int absolutPosY = mouseEventClick.y + getVerticalSckrollStatus();

		if (absolutPosY <= (filesCount * LISTBOX_LINE_HEIGHT) - 1) {
			_selectedLine = int(absolutPosY / LISTBOX_LINE_HEIGHT);
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

			redrawWindow(false);
		}
	}
	void ListOfFiles::calcDoubleLeftClick(const MouseEventClick& mouseEventClick)
	{
		int filesCount = _thisCatalog.size();
		int oldLine = _selectedLine;

		int absolutPosY = mouseEventClick.y + getVerticalSckrollStatus();

		if (absolutPosY <= (filesCount * LISTBOX_LINE_HEIGHT) - 1) {
			_selectedLine = int(absolutPosY / LISTBOX_LINE_HEIGHT);
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

			redrawWindow(false);
		}

		if (_selectedLine >= 0) {
			if (!_thisDirection.empty() && _thisDirection[_thisDirection.size() - 1] != '\\') {
				_thisDirection += '\\';
			}
			std::wstring newDirection = _thisDirection + _thisCatalog[_selectedLine].Name;
			File file(newDirection);
			if (file.isDirectory()) {
				nextDirrectory(_thisDirection);
				setCurrentDirectory(newDirection);
			}
		}

		//_thisDirection = _thisCatalog[_selectedLine];
		//updateList();
	}



	void ListOfFiles::setButtonBackward(ButtonReturn* button)
	{
		_buttonBackward = button;
		_buttonBackward->registerHendler(METHOD(&ListOfFiles::mouseClickButtonBackwardHandler));
	}
	void ListOfFiles::setButtonForward(ButtonReturn* button)
	{
		_buttonForward = button;
		_buttonForward->registerHendler(METHOD(&ListOfFiles::mouseClickButtonForwardHandler));
	}
	void ListOfFiles::setButtonUp(ButtonReturn* button)
	{
		_buttonUp = button;
		_buttonUp->registerHendler(METHOD(&ListOfFiles::mouseClickButtonUpHandler));
	}

	void ListOfFiles::mouseClickButtonBackwardHandler(const MouseEventClick& mouseEventClick)
	{
		if (mouseEventClick.Click == MOUSE_CLICK_ONE
			&& mouseEventClick.Button == MOUSE_LEFT
			&& mouseEventClick.Status == KEY_PRESSED
			&& !_buttonBackward->isLocked()) {
			if (!_backwardStack.empty()) {
				_forwardStack.push(_thisDirection);
				_thisDirection = _backwardStack.top();
				_backwardStack.pop();
				if (_backwardStack.empty()) {
					_buttonBackward->setLock(true);
					_buttonBackward->redrawWindow(false);
				}

				redrawWindow(false);
				_buttonForward->setLock(false);
				_buttonForward->redrawWindow(false);

				updateList();
			}
		}
	}
	void ListOfFiles::mouseClickButtonForwardHandler(const MouseEventClick& mouseEventClick)
	{
		if (mouseEventClick.Click == MOUSE_CLICK_ONE
			&& mouseEventClick.Button == MOUSE_LEFT
			&& mouseEventClick.Status == KEY_PRESSED
			&& !_buttonForward->isLocked()) {
			if (!_forwardStack.empty()) {
				_backwardStack.push(_thisDirection);
				_thisDirection = _forwardStack.top();
				_forwardStack.pop();

				if (_forwardStack.empty()) {
					_buttonForward->setLock(true);
					_buttonForward->redrawWindow(false);
				}

				redrawWindow(false);
				_buttonBackward->setLock(false);
				_buttonBackward->redrawWindow(false);

				updateList();
			}
		}
	}
	void ListOfFiles::mouseClickButtonUpHandler(const MouseEventClick& mouseEventClick)
	{
		if (mouseEventClick.Click == MOUSE_CLICK_ONE
			&& mouseEventClick.Button == MOUSE_LEFT
			&& mouseEventClick.Status == KEY_PRESSED
			&& !_buttonUp->isLocked()) {
			std::wstring currentDirection = _thisDirection;

			if (!currentDirection.empty()) {
				File file(currentDirection);
				std::wstring backPath = file.getPrevDirection();
				nextDirrectory(_thisDirection);
				_thisDirection = backPath;
				updateList();

				if (backPath.empty()) {
					setLock(true);
				}
				else {
					setLock(false);
				}

				updateList();
			}
		}
	}
}