#pragma once

#include <Windows.h>

#ifndef _RENDER_BUFFER_H_
#define _RENDER_BUFFER_H_

namespace explorer {

	class RenderBuffer {
		HDC _hDC_Device;
		HDC _hDC_Buffer;
		HBITMAP _hBitmap;

		int _width, _height;

	public:
		RenderBuffer(HDC hDC, int width, int hieght);
		~RenderBuffer();


		HDC getDC();
		HBITMAP getHBitmap();
		int getWidth();
		int getHeight();

		void resizeBuffer(int width, int hieght);

		void copyTo(RenderBuffer& buffer);
		void copyTo(RenderBuffer& buffer, int x, int y);
		void copyTo(RenderBuffer& buffer, int x, int y, int width, int hieght);
	};

}

#endif