#include "stdafx.h"
#include "ClassListOfFilesWindow.h"

namespace explorer {

	ListOfFiles::ListOfFiles()
	{
		m_registerHendler(METHOD(&ListOfFiles::paintHandler));
		m_registerHendler(METHOD(&ListOfFiles::mouseClickHandler));
		m_registerHendler(METHOD(&ListOfFiles::mouseMoveHandler));
	}

	void ListOfFiles::createWindow()
	{
		setDoubleBuffered(true);
	}

	void ListOfFiles::paintHandler(Gdiplus::Graphics& graphics)
	{

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
				MAIN_WINDOW_BUTTON_EXIT_POS_X(parentEvent.Width),
				MAIN_WINDOW_BUTTON_EXIT_POS_Y(1),
				MAIN_WINDOW_BUTTON_EXIT_WIDTH,
				MAIN_WINDOW_BUTTON_EXIT_HEIGHT,
				true
			);
		}
	}

}