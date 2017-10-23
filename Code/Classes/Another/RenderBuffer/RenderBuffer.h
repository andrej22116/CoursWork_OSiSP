#pragma once

#include <Windows.h>

#ifndef _RENDER_BUFFER_H_
#define _RENDER_BUFFER_H_

namespace explorer {

	class RenderBuffer {
		HDC _hDC;
		HBITMAP _hBitmap;

	public:
		RenderBuffer(int width, int hieght);
		~RenderBuffer();


		HDC getDC();
		HBITMAP getBitmap();
		void resizeBuffer(int width, int hieght);

		void copyTo(RenderBuffer& buffer, int x, int y, int width, int hieght);
	};

}

#endif