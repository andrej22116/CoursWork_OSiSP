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

	typedef std::function<void(HWND, WPARAM, LPARAM)> Hendler;

	typedef std::function<void(Gdiplus::Graphics& graphics)> PaintHandler;
	typedef std::function<void(const MouseEventClick& mouseEventClick)> MouseClickHandler;
	typedef std::function<void(const MouseEventWheel& mouseEventWheel)> MouseWheelHandler;
	typedef std::function<void(MouseEvent& mouseEvent)> MouseMoveHandler;
	typedef std::function<void(const ParentEvent& parentEvent)> ParentHandler;
	typedef std::function<void(const ChildEvent& childEvent)> ChildHandler;
	typedef std::function<void(const KeyEvent& keyEvent)> KeyboardHandler;
	typedef std::function<void(const int timer_ID)> TimerHandler;
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
		std::list<ChildHandler> _childHandlers;
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
		bool _moveWhenParentResiz_X, _moveWhenParentResiz_Y;
		bool _resizeWhenParentResize_Width, _resizeWhenParentResize_Height;

		bool _canBeResize_top, _canBeResize_bottom;
		bool _canBeResize_left, _canBeResize_right;
		bool _haveHeader;

		bool _isLocked;

		std::shared_ptr<RenderBuffer> _renderBuffer;
		int _scrollbarHorizontalStatus;
		int _scrollbarVerticalStatus;
		//int _scrollbarHorizontalMaxStatus;
		//int _scrollbarVerticalMaxStatus;
		int _scrollbarHorizontalStepSize;
		int _scrollbarVerticalStepSize;
		bool _scrollbarHorizontal_IsEnable;
		bool _scrollbarVertical_IsEnable;

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

		/* Scrolling */
		void setRenderBufferSize(int width, int height);
		void activateVerticalScrollbarIfRenderBufferHeightMoreThanHeightWindow(bool activate);
		void activateHorizontalScrollbarIfRenderBufferWidthMoreThanWidthWindow(bool activate);
		void setHorizontalSckrollStepSize(int horizontalStepSize);
		void setVerticalSckrollStepSize(int verticalStepSize);
		void setHorizontalSckrollStatus(int status);
		void setVerticalSckrollStatus(int status);
		int getHorizontalSckrollStatus();
		int getVerticalSckrollStatus();
		


		/* Handlers */
		// This method call when comes message WM_CREATE
		virtual void eventCreateWindow();
		void defaultCreateHandler();
		// This method call when comes message WM_MOVE
		virtual void eventMoveWindow(int oldPosX, int oldPosY);
		void defaultMoveHandler(int oldPosX, int oldPosY);
		// This method call when comes message WM_SIZE
		virtual void eventSizeWindow(int oldWidth, int oldHeight);
		void defaultSizeHandler(int oldWidth, int oldHeight);
		// This method call when comes message WM_DESTROY
		virtual void eventCloseWindow();
		void defaultCloseHandler();

		void timerCheckHoverWindow(const int& ID);
		void abstratcWindowScrollIventHandler(MouseEventWheel mouseEventWheel);

		/*
		 *	Send message to all windows!
		 */
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static UINT workWidthMessages();

		// return system MAJOR and system MINOR versions 
		static std::pair<int, int> getSystemVersion();

		/*
		 *	message, METHOD( & your_method );
		 */
		void m_registerHendler(PaintHandler method);
		void m_registerHendler(MouseClickHandler method);
		void m_registerHendler(MouseWheelHandler method);
		void m_registerHendler(MouseMoveHandler method);
		void m_registerHendler(KeyboardHandler method);
		void m_registerHendler(ParentHandler method);
		void m_registerHendler(ChildHandler method);
		void m_registerHendler(HoverHandler method);
		void m_registerTimerHendler(TimerHandler method);

	protected:
		/* Obsolete methods */
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

	private:
		static void m_WndProcHandler_GetMinMaxInfo(Window* wnd, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static void m_WndProcHandler_Sizing(Window* wnd, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static void m_WndProcHandler_Paint(Window* wnd, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static void m_WndProcHandler_Move(Window* wnd, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static void m_WndProcHandler_Size(Window* wnd, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static void m_WndProcHandler_MouseMove(Window* wnd, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static void m_WndProcHandler_MouseButtons(Window* wnd, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static void m_WndProcHandler_Keyboard(Window* wnd, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static void m_WndProcHandler_MouseHover(Window* wnd, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static void m_WndProcHandler_MouseWheel(Window* wnd, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static void m_WndProcHandler_Timer(Window* wnd, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static int m_WndProcHandler_NcCalcSize(Window* wnd, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static int m_WndProcHandler_NcHitTest(Window* wnd, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};
}

#endif