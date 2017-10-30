#pragma once

#ifndef _CONSTANT_PARAMS_H_
#define _CONSTANT_PARAMS_H_

// Main window styles!
#define MAIN_WINDOW_HEADER_HEIGHT 16

#define MAIN_WINDOW_BORDER_SIZE 3
#define MAIN_WINDOW_COLOR_BACKGROUND Gdiplus::Color(32, 32, 32)
#define MAIN_WINDOW_COLOR_HEADER Gdiplus::Color(64, 64, 64)
#define MAIN_WINDOW_COLOR_HEADER_BUTTON_SELECTED Gdiplus::Color(96, 96, 96)
#define MAIN_WINDOW_TEXT_COLOR

#define MAIN_WINDOW_BUTTON_EXIT_POS_X(x) ((x) - 17)
#define MAIN_WINDOW_BUTTON_EXIT_POS_Y(y) ((y) - 0)
#define MAIN_WINDOW_BUTTON_EXIT_WIDTH 16
#define MAIN_WINDOW_BUTTON_EXIT_HEIGHT 16

#define MAIN_WINDOW_BUTTON_MAXIMIZE_POS_X(x) ((x) - 33)
#define MAIN_WINDOW_BUTTON_MAXIMIZE_POS_Y(y) ((y) - 0)
#define MAIN_WINDOW_BUTTON_MAXIMIZE_WIDTH 16
#define MAIN_WINDOW_BUTTON_MAXIMIZE_HEIGHT 16

#define MAIN_WINDOW_BUTTON_MINIMIZE_POS_X(x) ((x) - 49)
#define MAIN_WINDOW_BUTTON_MINIMIZE_POS_Y(y) ((y) - 0)
#define MAIN_WINDOW_BUTTON_MINIMIZE_WIDTH 16
#define MAIN_WINDOW_BUTTON_MINIMIZE_HEIGHT 16

#define MAIN_WINDOW_BUTTON_OPTIONS_POS_X 1
#define MAIN_WINDOW_BUTTON_OPTIONS_POS_Y 1
#define MAIN_WINDOW_BUTTON_OPTIONS_WIDTH 16
#define MAIN_WINDOW_BUTTON_OPTIONS_HEIGHT 16

#define MAIN_WINDOW_BUTTON_UP_POS_X 17
#define MAIN_WINDOW_BUTTON_UP_POS_Y 1
#define MAIN_WINDOW_BUTTON_UP_WIDTH 16
#define MAIN_WINDOW_BUTTON_UP_HEIGHT 16

#define MAIN_WINDOW_BUTTON_FORWARD_POS_X 49
#define MAIN_WINDOW_BUTTON_FORWARD_POS_Y 1
#define MAIN_WINDOW_BUTTON_FORWARD_WIDTH 16
#define MAIN_WINDOW_BUTTON_FORWARD_HEIGHT 16

#define MAIN_WINDOW_BUTTON_BACKWARD_POS_X 33
#define MAIN_WINDOW_BUTTON_BACKWARD_POS_Y 1
#define MAIN_WINDOW_BUTTON_BACKWARD_WIDTH 16
#define MAIN_WINDOW_BUTTON_BACKWARD_HEIGHT 16


// Listbox
#define LISTBOX_POS_X (MAIN_WINDOW_BORDER_SIZE + 1)
#define LISTBOX_POS_Y (MAIN_WINDOW_HEADER_HEIGHT + 1)
#define LISTBOX_LINE_HEIGHT 20

#define LISTBOX_TEXT_POS_X 20
#define LISTBOX_TEXT_COLOR Gdiplus::Color(255, 255, 255)

#define LISTBOX_COLOR_BACKGROUND (MAIN_WINDOW_COLOR_BACKGROUND)
#define LISTBOX_COLOR_BACKGROUND_SELECT Gdiplus::Color(96, 96, 96)
#define LISTBOX_COLOR_BACKGROUND_HOVER Gdiplus::Color(48, 48, 48)
#define LISTBOX_COLOR_BORDER_LINE Gdiplus::Color(64, 64, 64)

#endif