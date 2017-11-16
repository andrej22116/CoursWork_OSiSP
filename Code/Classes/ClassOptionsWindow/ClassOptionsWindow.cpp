#include "stdafx.h"
#include "ClassOptionsWindow.h"

namespace explorer {
	OptionsWindow::OptionsWindow()
	{
		registerHendler(METHOD(&OptionsWindow::paintHandler));

		_listOfParams.push_back(L"Отображать расширения файлов");
		_listOfParams.push_back(L"Отображать скрытые файлы и папки");
		_listOfParams.push_back(L"Отображать размер файла");
		_listOfParams.push_back(L"Открывать каталоги в новой вкладке");
		_listOfParams.push_back(L"Востанавливать последние вкладки");
		_listOfParams.push_back(L"Отображать значки");
	}

	void OptionsWindow::eventCreateWindow()
	{
		int horizontalOffset = getWidth() - 34;

		int i = 0;
		_listOfcheckBoxes.resize(_listOfParams.size());
		for (auto item : _listOfParams) {
			_listOfcheckBoxes[i].create(
				std::wstring(L"option checkbox ") + std::to_wstring(i),
				*this,
				horizontalOffset,
				46 + i * 30,
				17,
				17,
				true
			);
			i++;
		}
	}

	void OptionsWindow::paintHandler(Gdiplus::Graphics& graphics)
	{
		//graphics.SetCompositingMode(Gdiplus::CompositingMode::CompositingModeSourceCopy);
		//graphics.Clear(Gdiplus::Color(200, 255, 255, 255));

		Gdiplus::StringFormat stringFormat(Gdiplus::StringFormatFlags::StringFormatFlagsNoClip);
		stringFormat.SetLineAlignment(Gdiplus::StringAlignmentCenter);
		stringFormat.SetAlignment(Gdiplus::StringAlignmentNear);

		Gdiplus::Font font(&Gdiplus::FontFamily(L"Arial"), 12);
		Gdiplus::SolidBrush brush(Gdiplus::Color(254, 0, 0, 0));
		Gdiplus::Pen penBottomLine(Gdiplus::Color(50, 0, 0, 0));

		int width = getWidth() - 52;
		Gdiplus::RectF rectForDraw(10, 40, width, 30);

		int widthLine = getWidth() - 20;
		int lineOffset = rectForDraw.GetBottom();
		
		penBottomLine.SetBrush(&Gdiplus::LinearGradientBrush(
			Gdiplus::Point(10 + widthLine, 0),
			Gdiplus::Point(10, 0),
			Gdiplus::Color(0, 0, 0, 0),
			Gdiplus::Color(32, 0, 0, 0)
		));
		for (auto item : _listOfParams) {
			graphics.DrawLine(&penBottomLine,
				Gdiplus::Point(10, lineOffset),
				Gdiplus::Point(10 + widthLine, lineOffset)
			);
			graphics.DrawString(
				item.c_str(),
				-1,
				&font,
				rectForDraw,
				&stringFormat,
				&brush
			);

			rectForDraw.Y += rectForDraw.GetBottom() - rectForDraw.GetTop();
			lineOffset = rectForDraw.GetBottom();
		}
	}
}