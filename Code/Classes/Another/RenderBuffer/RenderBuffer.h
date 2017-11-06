#pragma once

#include <Windows.h>

#ifndef _RENDER_BUFFER_H_
#define _RENDER_BUFFER_H_

namespace explorer {

	class RenderBuffer {
		HWND _hWnd;

		HDC _hDC_Device;
		HDC _hDC_Buffer;
		HBITMAP _hBitmap;

		int _width, _height;

	public:
		RenderBuffer(HWND hWnd, int width, int hieght);
		~RenderBuffer();


		HDC getDC();
		HBITMAP getHBitmap();
		int getWidth();
		int getHeight();

		void resizeBuffer(int width, int hieght);

		void copyTo(RenderBuffer& buffer);
		void copyTo(RenderBuffer& buffer, int toX, int toY);
		void copyTo(RenderBuffer& buffer, int toX, int toY, int width, int hieght);
		void copyTo(RenderBuffer& buffer, int fromX, int fromY, int toX, int toY, int width, int height);

		void swap(HDC hDC);

	private:
		void m_copyTo(RenderBuffer& buffer, int fromX, int fromY, int toX, int toY, int width, int height);
	};

}

#endif