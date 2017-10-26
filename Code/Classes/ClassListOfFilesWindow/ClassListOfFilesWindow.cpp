#include "stdafx.h"
#include "ClassListOfFilesWindow.h"

namespace explorer {

	ListOfFiles::ListOfFiles()
	{
		m_registerHendler(METHOD(&ListOfFiles::paintHandler));
		m_registerHendler(METHOD(&ListOfFiles::mouseClickHandler));
		m_registerHendler(METHOD(&ListOfFiles::mouseMoveHandler));
		m_registerHendler(METHOD(&ListOfFiles::resizeParentHandler));

		_thisDirection = L"E:\\Andrej\\Lern\\CoursWork_OSiSP\\CoursWork_OSiSP";
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
		graphics.FillRectangle(&selectBackground, 0, 0, getWidth() - 1, LISTBOX_LINE_HEIGHT - 1);
		graphics.DrawRectangle(&borderPen, 0, 0, getWidth() - 1, LISTBOX_LINE_HEIGHT - 1);

		graphics.FillRectangle(&hoverBackground, 0, LISTBOX_LINE_HEIGHT, getWidth() - 1, LISTBOX_LINE_HEIGHT - 1);
		graphics.DrawRectangle(&borderPen, 0, LISTBOX_LINE_HEIGHT, getWidth() - 1, LISTBOX_LINE_HEIGHT - 1);
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

	}

	void ListOfFiles::mouseMoveHandler(MouseEvent& mouseEvent)
	{

	}

	void ListOfFiles::resizeParentHandler(const ParentEvent& parentEvent)
	{
		if (parentEvent.Code == PARENT_RESIZE) {
			resizeWindow(
				LISTBOX_POS_X,
				LISTBOX_POS_Y,
				getParent()->getWidth() - MAIN_WINDOW_BORDER_SIZE - LISTBOX_POS_X - 1,
				getParent()->getHieght() - MAIN_WINDOW_BORDER_SIZE - LISTBOX_POS_Y - 1,
				true
			);
		}
	}



	void ListOfFiles::updateList()
	{
		File file(_thisDirection);
		_thisCatalog = file.list(L"*");
	}
}