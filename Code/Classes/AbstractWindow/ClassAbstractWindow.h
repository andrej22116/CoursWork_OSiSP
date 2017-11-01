#pragma once

#include <Dwmapi.h>

#include "..\Exceptions\ClassWindowException\ClassWindowException.h"
#include "..\Exceptions\ClassWindowClassException\ClassWindowClassException.h"

#include "..\..\Includes\Ivents\Ivents.h"
#include "..\..\Includes\DefaultParams\ConstantParams.h"

#include "..\Another\RenderBuffer\RenderBuffer.h"

#ifndef _CLASS_WINDOW_H_
#define _CLASS_WINDOW_H_

#define METHOD(method) (std::bind((method), this, std::placeholders::_1))

namespace explorer {
	class Window;

	typedef std::function<void(HWND, WPARAM, LPARAM)> Hendler;

	typedef std::function<void(Gdiplus::Graphics& graphics)> PaintHandler;
	typedef std::function<void(const MouseEventClick& mouseEventClick)> MouseClickHandler;
	typedef std::function<void(const MouseEventWheel& mouseEventWheel)> MouseWheelHandler;
	typedef std::function<void(MouseEvent& mouseEvent)> MouseMoveHandler;
	typedef std::function<void(const ParentEvent& parentEvent)> ParentHandler;
	typedef std::function<void(const KeyEvent& keyEvent)> KeyboardHandler;
	typedef std::function<void(const int& timer_ID)> TimerHandler;
	typedef std::function<void(bool status)> HoverHandler;


	class Window {
	private:
		static std::map<HWND, Window*> s_windowsMap;
		static std::wstring _className;
		static ULONG_PTR _gdiplusToken;
		static const UINT TIMER_UPP_HOVER = 10000;

		Window* _parent;
		std::list<Window*> _childList;

		std::list<MouseClickHandler> _mouseClickHandlers;
		std::list<MouseWheelHandler> _mouseWheelHandlers;
		std::list<MouseMoveHandler> _mouseMoveHandlers;
		std::list<KeyboardHandler> _keyboardHandlers;
		std::list<ParentHandler> _parentHandlers;
		std::list<PaintHandler> _paintHandlers;
		std::list<TimerHandler> _timerHandlers;
		std::list<HoverHandler> _hoverHandlers;


		int _width, _hieght, _oldWidth, _oldHieght;
		int _minWidth, _minHieght;
		int _maxWidth, _maxHieght;
		int _pos_x, _pos_y;
		int _g_pos_X, _g_pos_Y;
		int _borderSize;
		HWND _hWnd;

		WNDCLASSEX _WndClass;
		std::wstring _windowName;

		bool _thisWindowIsCreated;
		bool _hoverStatus;
		bool _doubleBuffer;
		bool _moveWhenParentResiz_X, _moveWhenParentResiz_Y;
		bool _resizeWhenParentResize_Width, _resizeWhenParentResize_Height;

		bool _canBeResize_top, _canBeResize_bottom;
		bool _canBeResize_left, _canBeResize_right;
		bool _haveHeader;

		bool _isLocked;

		std::shared_ptr<RenderBuffer> _renderBuffer;
		int _viewportWidth, _viewportHeight;
		int _bufferedWidth, _bufferedHeight;
		int _scrollStatus;
		int _scrollMaxStatus;
		int _scrollSections;

	public:
		Window();
		~Window();

		bool create(int pos_x, int pos_y, int width, int hieght, bool show = true);
		bool create(Window& parent, int pos_x, int pos_y, int width, int hieght, bool show = true);
		bool create(std::wstring& name, int pos_x, int pos_y, int width, int hieght, bool show = true);
		bool create(std::wstring& name, Window& parent, int pos_x, int pos_y, int width, int hieght, bool show = true);

		int getWidth() const;
		int getHieght() const;
		HWND getHWND() const;
		Window* getParent() const;

		int getPosX() const;
		int getPosY() const;
		int getGlobalPosX() const;
		int getGlobalPosY() const;
		
		std::wstring getClassName() const;
		std::wstring getWindowName() const;
		void minimizeWindow(bool hide);
		void setWindowName(std::wstring& name);
		void setDoubleBuffered(bool set);
		void setResizeWhenParentResizeing(bool resize_width = false, bool resize_height = false);
		void setMoveWhenParentResizeing(bool move_x = false, bool move_y = false);
		void setBorderSize(int size = 1);
		void setResizebleAll(bool left = false, bool right = false, bool top = false, bool bottom = false);
		void setResizebleTop(bool top = false);
		void setResizebleLeft(bool left = false);
		void setResizebleRight(bool right = false);
		void setResizebleBottom(bool bottom = false);
		void setMinSize(int width, int height);
		void setMaxSize(int width, int height);
		void setHeader(bool header);

		void setLock(bool lock);
		bool isLocked();


		void moveWindowPos(int x, int y, bool repaint = false);
		void resizeWindow(int width, int hieght, bool show);
		void resizeWindow(int pos_x, int pos_y, int width, int hieght, bool show);
		void redrawWindow(bool erase);

		void showWindow(bool show);
		void setTimer(UINT timer_ID, UINT elapse);
		void killTimer(UINT timer_ID);

		void getHoverMessages(bool activate);

		/* Handlers */
		// This method call when comes message WM_CREATE
		virtual void createWindow();
		void closeWindow();
		void timerCheckHoverWindow(const int& ID);

		/*
		 *	Send message to all windows!
		 */
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static UINT workWidthMessages();

	protected:
		/*
		 *	message, METHOD( & your_method );
		 */
		void m_registerHendler(PaintHandler method);
		void m_registerHendler(MouseClickHandler method);
		void m_registerHendler(MouseWheelHandler method);
		void m_registerHendler(MouseMoveHandler method);
		void m_registerHendler(KeyboardHandler method);
		void m_registerHendler(ParentHandler method);
		void m_registerHendler(HoverHandler method);
		void m_registerTimerHendler(TimerHandler method);

		void m_sendMessageForParent(UINT message, WPARAM wParam, LPARAM lParam);
		void m_sendMessageForAllChildren(UINT message, WPARAM wParam, LPARAM lParam);
		void m_sendMessageForChildren(std::wstring name, UINT message, WPARAM wParam, LPARAM lParam);
		void m_sendMessageForChildren(Window* window, UINT message, WPARAM wParam, LPARAM lParam);
		void m_sendMessageForChildren(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		void m_invalidateChilds();
	
	private:
		ATOM m_registerClass();
		bool m_create(Window* parent = nullptr, bool show = true);
		bool m_createWindow(Window* parent = nullptr);
		void m_addChildWindow(Window* child);
		void m_removeChildWindow(Window* child);

		void m_calculateNewPositionWindowIfParentResize();
		void m_calculateNewSizeWindowIfParentResize();
	};
}

#endif